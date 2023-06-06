#include <iostream>
#include <thread>   

class Request 
{
public:
    void SetId(int id)
    {
        m_id = id;
    }

    void Process()
    {
        std::cerr << "Processing request id: " << m_id << std::endl;
    }

private:
    int m_id;
};

int main()
{
    Request q;
    std::thread t {&Request::Process, &q};

    t.join();

    return 0;
}