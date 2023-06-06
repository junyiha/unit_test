#include "ConsumerIndex.hpp"

int main()
{
    int ret {ConsumerIndex::RET_ERR};
    std::size_t idx {};
    std::string consumer_file {};
    ConsumerIndex ci;

    ci.GetFileName(consumer_file);
    ret = ci.Open();
    if (ret == ConsumerIndex::RET_OK)
    {
        ret = ci.ReadIndex(idx);
        if (ret == ConsumerIndex::RET_OK)
        {
            std::cerr << "consumer index is : " << idx << std::endl;
        }
        std::cerr << "input index: " << std::endl;
        std::cin >> idx;
        ret = ci.WriteIndex(idx);
        if (ret == ConsumerIndex::RET_OK)
        {
            std::cerr << "Success to write index:" << idx << " to consumer file: " << consumer_file << std::endl;
        }
    }

    return 0;
}