/**
 * @file test_network.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "entry.hpp"

extern "C"
{
    #include "mongoose.h"
}

#include "boost/beast/core.hpp"
#include "boost/beast/http.hpp"
#include "boost/beast/version.hpp"
#include "boost/beast/version.hpp"
#include "boost/asio/ip/tcp.hpp"
#include "boost/config.hpp"

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;   // from <boost/asio/ip/tcp.hpp>

int httplib_server()
{
    httplib::Server svr;

    svr.Get("/", [](const httplib::Request& req, httplib::Response& res) {
        res.set_content("hello world", "text/plain");
    });

    return 1;
}

int beast_http_server_sync(Message& message)
{
    std::string address = "0.0.0.0";
    unsigned int port = 13000;
    std::string doc_root = ".";

    net::io_context ioc{1};
    tcp::acceptor acceptor{ioc, tcp::endpoint(net::ip::address_v4::from_string(address), port)};
    acceptor.listen();
    for (;;)
    {
        // This will receive the new connection
        tcp::socket socket{ioc};

        // Block until we get a connect
        acceptor.accept(socket);
        try 
        {
            beast::flat_buffer buffer;
            http::request<http::string_body> request;

            http::read(socket, buffer, request);

            http::response<http::string_body> response{http::status::ok, request.version()};
            response.set(http::field::server, "Boost HTTP Server");
            response.body() = "Hello, World!";
            response.prepare_payload();

            http::write(socket, response);
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 1;
}

int beast_http_client_sync(Message& message)
{
    try 
    {
        std::string address = "192.169.4.16";
        unsigned int port = 13000;
        std::string target = "/hello";
        int version = 10;
        net::io_context ioc;
        beast::tcp_stream stream(ioc);

        stream.connect(tcp::endpoint(net::ip::address_v4::from_string(address), port));
        http::request<http::string_body> req{http::verb::get, target, version};
        req.set(http::field::host, address);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        // Send the HTTP request to the remote host
        http::write(stream, req);

        // This buffer is used for reading and must be persisted
        beast::flat_buffer buffer;

        // Declare a container to hold the response
        http::response<http::dynamic_body> res;

        // Receive the HTTP response
        http::read(stream, buffer, res);

        // Write the message to standard out
        LOG(INFO) << "Full response: \n" << res << std::endl;
        LOG(INFO) << "response's body: " << beast::buffers_to_string(res.body().data()) << std::endl;

        // Gracefully close the socket
        beast::error_code ec;
        stream.socket().shutdown(tcp::socket::shutdown_both, ec);

        // not_connected happens sometimes
        // so don't bother reporting it.
        if (ec && ec != beast::errc::not_connected)
        {
            throw ec;
        }
    }
    catch (std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 0;
    }

    return 1;
}

static void handle_request(const http::request<http::string_body>& req, http::response<http::string_body>& res)
{
    if (req.method() == http::verb::get && req.target() == "/hello")
    {
        res.result(http::status::ok);
        res.set(http::field::server, "AsyncBoostServer");
        res.set(http::field::content_type, "text/plain");
        res.keep_alive(req.keep_alive());
        res.body() = "Hello, Boost.Beast";
        res.prepare_payload();
    }
    else 
    {
        res.result(http::status::not_found);
        res.keep_alive(req.keep_alive());
        res.body() = "Not Found";
        res.prepare_payload();
    }
}

static void do_session(tcp::socket& socket)
{
    beast::error_code ec;
    beast::flat_buffer buffer;

    http::request<http::string_body> req;
    http::read(socket, buffer, req, ec);
    if (ec == http::error::end_of_stream)
    {
        LOG(WARNING) << "ec is end_of_stream\n";
        socket.shutdown(tcp::socket::shutdown_send, ec);
        return;
    }
    else if (ec)
    {
        LOG(ERROR) << "Error reading HTTP request: " << ec.message() << std::endl;
        return;
    }
    LOG(INFO) << "request's target: " << req.target() << "\n";

    http::response<http::string_body> res;
    handle_request(req, res);

    http::write(socket, res, ec);
    if (ec)
    {
        LOG(ERROR) << "Error writing HTTP response: " << ec.message() << std::endl;
        return;
    }
}

int beast_http_server_async(Message& message)
{
    std::string address = "0.0.0.0";
    unsigned int port = 13000;
    net::io_context io_context;

    try 
    {
        tcp::acceptor acceptor(io_context, tcp::endpoint(net::ip::address_v4::from_string(address), port));
        acceptor.listen();
        for (;;)
        {
            tcp::socket socket(io_context);
            acceptor.async_accept(socket, [&](const beast::error_code& ec){
                if (!ec)
                {
                    do_session(socket);
                }
            });

            io_context.run();
        }
    }
    catch (std::exception& e)
    {
        LOG(ERROR) << "Exception: " << e.what() << std::endl;
        return 0;
    }
    
    return 1;
}

static void handle_event(mg_connection *connect, int ev, void *ev_data, void *fn_data)
{
    struct mg_http_message* hm = (struct mg_http_message*)ev_data;
    LOG(INFO) << "ev: " << ev << "\n";
    switch (ev)
    {
        case MG_EV_HTTP_MSG:
            mg_http_reply(connect, 200, "text/plain", "hello, mongoose");
            connect->is_draining = 1;
            break;
        default:
            break;
    }
}

int mongoose_http_server(Message& message)
{
    struct mg_mgr mgr;
    struct mg_connection *connect;
    mg_event_handler_t func = handle_event;

    mg_mgr_init(&mgr);

    connect = mg_http_listen(&mgr, "0.0.0.0:13000", func, nullptr);

    for (;;)
    {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return 1;
}

void EventHandler(mg_connection* connect, struct mg_http_message* ev_data)
{
    mg_http_reply(connect, 200, "text/plain", "hello mongoose");
    connect->is_draining = 1;

    return;
}

int mongoose_http_server_sync(Message& message)
{
    struct mg_mgr mgr;
    struct mg_connection *connect;
    mg_event_handler_t func = [](mg_connection *connect, int ev, void *ev_data, void *fn_data)
    {
        struct mg_http_message* hm = (struct mg_http_message*)ev_data;
        LOG(INFO) << "ev: " << ev << "\n";
        switch (ev)
        {
            case MG_EV_HTTP_MSG:
            {
                EventHandler(connect, hm);
                break;
            }
            default:
                break;
        }
    };

    mg_mgr_init(&mgr);

    connect = mg_http_listen(&mgr, "0.0.0.0:13000", func, nullptr);

    for (;;)
    {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return 1;
}

int mongoose_http_server_async(Message& message)
{
    struct mg_mgr mgr;
    struct mg_connection *connect;
    mg_event_handler_t func = [](mg_connection *connect, int ev, void *ev_data, void *fn_data)
    {
        struct mg_http_message* hm = (struct mg_http_message*)ev_data;
        LOG(INFO) << "ev: " << ev << "\n";
        switch (ev)
        {
            case MG_EV_HTTP_MSG:
            {
                std::thread tmp(EventHandler, connect, hm);
                tmp.detach();
                break;
            }
            default:
                break;
        }
    };

    mg_mgr_init(&mgr);

    connect = mg_http_listen(&mgr, "0.0.0.0:13000", func, nullptr);

    for (;;)
    {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return 1;
}

int mongoose_http_client(Message& message)
{
    bool done = false;
    struct mg_mgr mgr;
    struct mg_connection* connect = NULL;
    mg_event_handler_t func = [](mg_connection *connect, int ev, void *ev_data, void *fn_data)
    {
        LOG(INFO) << "ev: " << ev << "\n";
        switch (ev)
        {
            case MG_EV_CONNECT:
            {
                struct mg_str host = mg_url_host("http://192.169.4.16:13000/api/");
                mg_printf(connect, "GET %s HTTP/1.0 \r\nContent-Type:text/plain\r\n\r\n", mg_url_uri("http://192.169.4.16:13000/api/"));
                mg_printf(connect, "Hello, mongoose server\r\n");
                break;
            }
            case MG_EV_HTTP_MSG:
            {
                struct mg_http_message* hm = static_cast<struct mg_http_message*>(ev_data);
                printf("%.*s", (int)hm->message.len, hm->message.ptr);
                *(bool *)fn_data = true;
                break;
            }
            default:
                break;
        }
    };

    mg_mgr_init(&mgr);

    for (;;)
    {
        // if (done)
        // {
        //     break;
        // }
        mg_http_connect(&mgr, "http://192.169.4.16:13000/api/", func, &done);
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return 1;
}

int test_network(Message& message)
{
    LOG(INFO) << "----test network begin----\n";

    std::map<std::string, std::function<int(Message&)>>cmd_map = {
        {"beast-http-server-sync", beast_http_server_sync},
        {"beast-http-server-async", beast_http_server_async},
        {"beast-http-client-sync", beast_http_client_sync},
        {"mongoose-http-server", mongoose_http_server},
        {"mongoose-http-server-async", mongoose_http_server_async},
        {"mongoose-http-server-sync", mongoose_http_server_sync},
        {"mongoose-http-client", mongoose_http_client}
    };

    std::string cmd = message.message_pool.at(2);
    auto it = cmd_map.find(cmd);
    if (it != cmd_map.end())
    {
        it->second(message);
        return 1;
    }
    else 
    {
        LOG(ERROR) << "invalid command: " << cmd << std::endl;
    }

    LOG(INFO) << "----test network end----\n";

    return 1;
}