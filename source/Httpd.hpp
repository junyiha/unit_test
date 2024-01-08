/**
 * @file Httpd.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

extern "C"
{
    #include <sys/socket.h>
    #include <sys/poll.h>
    #include <arpa/inet.h>
    #include <string.h>
    #include <unistd.h>
}

#include <algorithm>
#include <iostream>
#include <sstream>
#include <thread>
#include <atomic>
#include <vector>
#include <mutex>
#include <map>

class Httpd
{
public:
    enum class httpd_ret : unsigned int
    {
        SUCCESS = 1,
        FAIL
    };

    struct Request_t 
    {
        struct pollfd fds;
        std::string method;
        std::string path;
        std::string protocol;
        std::map<std::string, std::string> header_map;
        std::vector<std::string> header_arr;
        std::string body;
    };

    struct Response_t
    {   
        struct pollfd fds;
        std::string protocol;
        size_t code;
        std::string status;
        std::map<std::string, std::string> header_map;
        std::vector<std::string> header_arr;
        std::string body;
    };  

private:
    size_t m_port;
    size_t m_buffer_size;
    struct sockaddr_in m_server_addr;
    int m_server_socket;
    std::thread m_event_tread;
    std::atomic<bool> m_flag;
    std::vector<struct pollfd> m_fds;
    std::vector<struct pollfd> m_client_fds;
    std::mutex m_mutex;

public:
    Httpd(int max_connections)
    {
        m_server_socket = -1;
        m_fds.resize(max_connections);
        m_flag.store(true);
        m_port = 8080;
        m_buffer_size = 1024 * 1024 * 10;  // 10MB
    }
    ~Httpd()
    {
        m_server_socket = -1;
        if (m_event_tread.joinable())
        {
            m_event_tread.join();
        }
    }

public:
    httpd_ret Listen()
    {
        m_server_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (m_server_socket == -1)
        {
            std::cerr << "socket creation failed\n" << std::endl;
            return httpd_ret::FAIL;
        }

        m_server_addr.sin_family = AF_INET;
        m_server_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
        m_server_addr.sin_port = htons(m_port);

        int opt = 1;
        int res = setsockopt(m_server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
        if (res < 0)
        {
            std::cout << "setsockopt failed\n" << std::endl;
            return httpd_ret::FAIL;
        }

        res = bind(m_server_socket, (struct sockaddr *)&m_server_addr, sizeof(m_server_addr));
        if (res < 0)
        {
            std::cout << "socket listen failed, port: " << m_port << "\n" << std::endl;
            return httpd_ret::FAIL;
        }

        res = listen(m_server_socket, 10);
        if (res == -1)
        {
            std::cout << "listen failed\n" << std::endl;
            return httpd_ret::FAIL;
        }

        m_fds[0].fd = m_server_socket;
        m_fds[0].events = POLLIN;

        return httpd_ret::SUCCESS;
    }

    httpd_ret Start()
    {
        auto tmp = [](Httpd* this_p)
        {
            while (this_p->m_flag.load())
            {
                int activity = poll(this_p->m_fds.data(), this_p->m_fds.size(), 0);
                if (activity < 0)
                {
                    std::cerr << "poll error \n" << std::endl;
                    return httpd_ret::FAIL;
                }
                if (this_p->m_fds[0].revents & POLLIN)
                {
                    struct sockaddr_in client_addr;
                    memset(&client_addr, 0, sizeof(client_addr));
                    socklen_t len = sizeof(client_addr);
                    int new_socket = accept(this_p->m_fds[0].fd, (struct sockaddr *)&client_addr, &len);
                    if (new_socket < 0)
                    {
                        std::cerr << "accept failed \n" << std::endl;
                        return httpd_ret::FAIL;
                    }
                    struct pollfd fds;
                    fds.fd = new_socket;
                    fds.revents = POLLIN;
                    this_p->m_mutex.lock();
                    this_p->m_client_fds.push_back(fds);
                    this_p->m_mutex.unlock();
                }
            }
        };

        m_event_tread = std::thread(tmp, this);

        return httpd_ret::SUCCESS;
    }

    void Stop()
    {
        m_flag.store(false);
    }

    httpd_ret PopEvent(std::vector<struct pollfd>& out)
    {
        if (m_client_fds.empty())
        {
            return httpd_ret::FAIL;
        }

        out = m_client_fds;
        m_mutex.lock();
        m_client_fds.clear();
        m_mutex.unlock();

        return httpd_ret::SUCCESS;
    }

    httpd_ret HTTPRequest(struct pollfd& out_fds, std::string& request_body)
    {
        if (m_client_fds.empty())
        {
            return httpd_ret::FAIL;
        }

        auto it = std::find_if(m_client_fds.begin(), m_client_fds.end(), [](struct pollfd& tmp){
            return tmp.revents & POLLIN;
        });

        if (it == m_client_fds.end())
        {
            return httpd_ret::FAIL;
        }
        std::vector<char> recv_buf(m_buffer_size);
        int valread = read(it->fd, recv_buf.data(), recv_buf.size());
        out_fds = *it;
        m_mutex.lock();
        m_client_fds.erase(it);
        m_mutex.unlock();
        if (valread <= 0)
        {
            return httpd_ret::FAIL;
        }

        request_body = std::string(recv_buf.data(), valread);

        return httpd_ret::SUCCESS;
    }

    httpd_ret HTTPRequest(Request_t &request)
    {
        if (m_client_fds.empty())
        {
            return httpd_ret::FAIL;
        }

        auto it = std::find_if(m_client_fds.begin(), m_client_fds.end(), [](struct pollfd& tmp){
            return tmp.revents & POLLIN;
        });

        if (it == m_client_fds.end())
        {
            return httpd_ret::FAIL;
        }
        std::vector<char> recv_buf(m_buffer_size);
        int valread = read(it->fd, recv_buf.data(), recv_buf.size());
        request.fds = *it;
        m_mutex.lock();
        m_client_fds.erase(it);
        m_mutex.unlock();
        if (valread <= 0)
        {
            return httpd_ret::FAIL;
        }

        std::string request_string = std::string(recv_buf.data(), valread);
        parseHTTPRequest(request_string, request);

        return httpd_ret::SUCCESS;
    }

    httpd_ret HTTPResponse(struct pollfd fds,std::string version, std::string response_header, std::string response_body)
    {
        std::stringstream os_out;
        
        os_out << version << "\n"
               << response_header << "\n\n"
               << response_body << "\n";
        std::string data = os_out.str();
        std::cerr << "response data: \n" << data << "\n";
        int res = write(fds.fd, data.c_str(), data.size());
        close(fds.fd);
        if (res < 0)
        {
            std::cerr << "write data failed\n";
            return httpd_ret::FAIL;
        }

        return httpd_ret::SUCCESS;
    }

    httpd_ret HTTPResponse(Response_t response)
    {
        std::stringstream os_out;
        
        os_out << response.protocol << " "
               << response.code << " "
               << response.status << "\n";
        for (auto& header : response.header_arr)
        {
            os_out << header << "\n";
        }
        os_out << "\n"
               << response.body << "\n";

        std::string data = os_out.str();
        std::cerr << "response data: \n" << data << "\n";
        int res = write(response.fds.fd, data.c_str(), data.size());
        close(response.fds.fd);
        if (res < 0)
        {
            std::cerr << "write data failed\n";
            return httpd_ret::FAIL;
        }

        return httpd_ret::SUCCESS;
    }

private:
    void parseHTTPRequest(const std::string& httpRequest, Request_t &out) 
    {
        std::istringstream requestStream(httpRequest);
        std::string requestLine;
        std::getline(requestStream, requestLine);

        // 解析请求行
        std::istringstream requestLineStream(requestLine);
        std::string method, path, protocol;
        requestLineStream >> method >> path >> protocol;

        // 输出请求行信息
        std::cout << "Method: " << method << std::endl;
        std::cout << "Path: " << path << std::endl;
        std::cout << "Protocol: " << protocol << std::endl;
        out.method = method;
        out.path = path;
        out.protocol = protocol;

        // 解析请求头部
        std::string headerLine;
        while (std::getline(requestStream, headerLine) && headerLine != "\r") {
            std::cout << "Header: " << headerLine << std::endl;
            // 在此处可以进一步解析头部信息并存储
            out.header_arr.push_back(headerLine);
        }

        // 解析请求数据（主体）
        std::string requestBody;
        std::getline(requestStream, requestBody, '\0'); // 读取请求主体
        std::cout << "Request Body: " << requestBody << std::endl;
        out.body = requestBody;
    }
};