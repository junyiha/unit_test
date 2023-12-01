/**
 * @file test_asio.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "entry.hpp"
#include "asio.hpp"
#include "boost/bind/bind.hpp"

int asio_timer_hello()
{
    asio::io_context io;

    asio::steady_timer t(io, asio::chrono::seconds(5));

    t.wait();

    LOG(INFO) << "hello world" << "\n";
    LOG(INFO) << "test asio end..." << "\n";

    return 1;
}

void Print(const asio::error_code& e)
{
    LOG(INFO) << "Hello, World" << "\n";

    return;
}

int asio_timer_asychronous()
{
    asio::io_context io;

    asio::steady_timer t(io, asio::chrono::seconds(5));
    t.async_wait(&Print);

    io.run();

    return 1;
}

void PrintV2(asio::steady_timer* t, int* count)
{
    if (*count < 5)
    {
        LOG(INFO) << *count << "\n";
        ++(*count);

        t->expires_at(t->expiry() + asio::chrono::seconds(1));
        t->async_wait(boost::bind(PrintV2, t, count));
    }
}

int asio_timer_bind_argument()
{
    asio::io_context io;

    int count = 0;
    asio::steady_timer t(io, asio::chrono::seconds(1));
    t.async_wait(boost::bind(PrintV2, &t, &count));

    io.run();
    LOG(INFO) << "Final count is : " << count << std::endl;

    return 1;
}

class printer
{
public:
    printer(asio::io_context& io)
        : timer_(io, asio::chrono::seconds(1)), count_(0)
    {
        timer_.async_wait(boost::bind(&printer::print, this));
    }
    ~printer()
    {
        LOG(INFO) << "Final count is: " << count_ << "\n";
    }

    void print()
    {
        if (count_ < 5)
        {
            LOG(INFO) << count_ << "\n";
            ++count_;
            timer_.expires_at(timer_.expiry() + asio::chrono::seconds(1));
            timer_.async_wait(boost::bind(&printer::print, this));
        }
    }

private:
    asio::steady_timer timer_;
    int count_;
};

int asio_timer_bind_member_function()
{
    asio::io_context io;
    printer p(io);
    io.run();

    return 1;
}

class printer2
{
public:
  printer2(asio::io_context& io)
    : strand_(asio::make_strand(io)),
      timer1_(io, asio::chrono::seconds(1)),
      timer2_(io, asio::chrono::seconds(1)),
      count_(0)
  {
    timer1_.async_wait(asio::bind_executor(strand_,
          boost::bind(&printer2::print1, this)));

    timer2_.async_wait(asio::bind_executor(strand_,
          boost::bind(&printer2::print2, this)));
  }

  ~printer2()
  {
    std::cout << "Final count is " << count_ << std::endl;
  }

  void print1()
  {
    if (count_ < 10)
    {
      std::cout << "Timer 1: " << count_ << std::endl;
      ++count_;

      timer1_.expires_at(timer1_.expiry() + asio::chrono::seconds(1));

      timer1_.async_wait(asio::bind_executor(strand_,
            boost::bind(&printer2::print1, this)));
    }
  }

  void print2()
  {
    if (count_ < 10)
    {
      std::cout << "Timer 2: " << count_ << std::endl;
      ++count_;

      timer2_.expires_at(timer2_.expiry() + asio::chrono::seconds(1));

      timer2_.async_wait(asio::bind_executor(strand_,
            boost::bind(&printer2::print2, this)));
    }
  }

private:
  asio::strand<asio::io_context::executor_type> strand_;
  asio::steady_timer timer1_;
  asio::steady_timer timer2_;
  int count_;
};

int asio_timer_multi_thread()
{
    asio::io_context io;
    printer2 p(io);
    asio::thread t(boost::bind(&asio::io_context::run, &io));
    io.run();
    t.join();

    return 1;
}

int asio_chrono_seconds()
{
    asio::io_context io;
    asio::steady_timer timer(io, asio::chrono::seconds(5));

    LOG(INFO) << "Timer will expire after 5 seconds." << "\n";

    return 1;
}

int asio_chrono_make_strand()
{
    asio::io_context io;
    
    auto strand = asio::make_strand(io);

    asio::post(strand, [](){
        LOG(INFO) << "Task 1 executed in strand!" << "\n";
    });

    asio::post(strand, [](){
        LOG(INFO) << "Task 2 executed in strand!" << "\n";
    });

    io.run();

    return 1;
}

int test_asio(Message& message)
{
    LOG(INFO) << "test asio begin..." << "\n";

    std::map<std::string, std::function<int()>> cmd_map = {
        {"asio-timer-hello", asio_timer_hello},
        {"asio-timer-asychronous", asio_timer_asychronous},
        {"asio-timer-bind-argument", asio_timer_bind_argument},
        {"asio-timer-bind-member-function", asio_timer_bind_member_function},
        {"asio-timer-multi-thread", asio_timer_multi_thread},
        {"asio-chrono-seconds", asio_chrono_seconds},
        {"asio-chrono-make-strand", asio_chrono_make_strand}
    };

    std::string cmd = message.message_pool[2];

    auto it = cmd_map.find(cmd);
    if (it != cmd_map.end())
    {
        it->second();
        return 1;
    }

    LOG(ERROR) << "invalid command: " << cmd << "\n";
    LOG(INFO) << "test asio end..." << "\n";

    return 0;
}
