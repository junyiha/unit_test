/**
 * @file test_leetcode.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "entry.hpp"

int test_2859(Message& message)
{
    LOG(INFO) << "test 2859 : 计算 K 置位下标对应元素的和 \n";

    std::string demo = R"(
        输入：nums = [5,10,1,5,2], k = 1
        输出：13
        解释：下标的二进制表示是： 
        0 = 000
        1 = 001
        2 = 010
        3 = 011
        4 = 100 
        下标 1、2 和 4 在其二进制表示中都存在 k = 1 个置位。
        因此，答案为 nums[1] + nums[2] + nums[4] = 13 。
    )";
    LOG(INFO) << "demo: \n" << demo << "\n";

    int k = 1;
    std::vector<int> nums{5,10,1,5,2};
    std::vector<std::bitset<32>> binary_array;

    // 十进制 -> 二进制
    for (int i = 0; i < nums.size(); i++)
    {
        std::bitset<32> tmp(i);
        binary_array.push_back(tmp);
    }

    int sum{0};
    for (auto& it : binary_array)
    {
        LOG(INFO) << "decimal index: " << it.to_ulong() << "\n"
                  << "binary index: " << it.to_string() << "\n"
                  << "k = 1's counter: " << it.count() << "\n";
        if (it.count() == k)
        {
            sum += nums.at(it.to_ulong());
        }
    }

    LOG(INFO) << "sum: " << sum << "\n";

    return 1;
}

int test_88(Message& message)
{
    LOG(INFO) << "test 88: 合并两个有序数组\n";

    std::string demo = R"(
        给你两个按 非递减顺序 排列的整数数组 nums1 和 nums2，另有两个整数 m 和 n ，分别表示 nums1 和 nums2 中的元素数目。

        请你 合并 nums2 到 nums1 中，使合并后的数组同样按 非递减顺序 排列。

        注意：最终，合并后数组不应由函数返回，而是存储在数组 nums1 中。为了应对这种情况，nums1 的初始长度为 m + n，其中前 m 个元素表示应合并的元素，后 n 个元素为 0 ，应忽略。nums2 的长度为 n 。
        
        示例 1：
        输入：nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
        输出：[1,2,2,3,5,6]
        解释：需要合并 [1,2,3] 和 [2,5,6] 。
        合并结果是 [1,2,2,3,5,6] ，其中斜体加粗标注的为 nums1 中的元素。
    )";

    LOG(INFO) << "demo: \n" << demo << "\n";
    std::vector<int> nums1{1,2,3,0,0,0};
    int m = 3;
    std::vector<int> nums2{2,5,6};
    int n = 3;

    std::vector<int> tmp;
    for (int i = 0; i < m; i++)
    {
        tmp.push_back(nums1.at(i));
    }
    for (int i = 0; i < n; i++)
    {
        tmp.push_back(nums2.at(i));
    }
    std::sort(tmp.begin(), tmp.end());
    std::swap(nums1, tmp);

    for (auto& it : nums1)
    {
        LOG(INFO) << "value: " << it << ", ";
    }

    return 1;
}

int test_27(Message& message)
{
    LOG(INFO) << "test 27: 移除元素\n";
    std::string demo = R"(
        给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。

        不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。

        元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。

        说明:

        为什么返回数值是整数，但输出的答案是数组呢?

        请注意，输入数组是以「引用」方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。

        你可以想象内部操作如下:

        // nums 是以“引用”方式传递的。也就是说，不对实参作任何拷贝
        int len = removeElement(nums, val);

        // 在函数里修改输入数组对于调用者是可见的。
        // 根据你的函数返回的长度, 它会打印出数组中 该长度范围内 的所有元素。
        for (int i = 0; i < len; i++) {
            print(nums[i]);
        }
        
        示例 1：
        输入：nums = [3,2,2,3], val = 3
        输出：2, nums = [2,2]
        解释：函数应该返回新的长度 2, 并且 nums 中的前两个元素均为 2。你不需要考虑数组中超出新长度后面的元素。例如，函数返回的新长度为 2 ，而 nums = [2,2,3,3] 或 nums = [2,2,0,0]，也会被视作正确答案。
    )";

    LOG(INFO) << "demo: \n" << demo << "\n";

    int val{3};
    std::vector<int> nums{3,2,2,3};

    // 不满足条件 : 原地移除 std::remove()将元素移动到末尾
    // int counter = std::count(nums.begin(), nums.end(), val);
    // for (int i = 0; i < counter; i++)
    // {
    //     nums.erase(std::remove(nums.begin(), nums.end(), val));
    // }

    while (true)
    {
        auto it = std::find(nums.begin(), nums.end(), val);
        if (it == nums.end())
        {
            break;
        }
        nums.erase(it);
    }

    LOG(INFO) << "array's size: " << nums.size() << "\n";
    for (auto& it : nums)
    {
        LOG(INFO) << "value: " << it << "\n";
    }

    return 1;
}

int test_26(Message& message)
{
    LOG(INFO) << "test 26: 删除有序数组中的重复项\n";
    std::string demo = R"(
        给你一个 非严格递增排列 的数组 nums ，请你 原地 删除重复出现的元素，使每个元素 只出现一次 ，返回删除后数组的新长度。元素的 相对顺序 应该保持 一致 。然后返回 nums 中唯一元素的个数。

        考虑 nums 的唯一元素的数量为 k ，你需要做以下事情确保你的题解可以被通过：

        更改数组 nums ，使 nums 的前 k 个元素包含唯一元素，并按照它们最初在 nums 中出现的顺序排列。nums 的其余元素与 nums 的大小不重要。
        返回 k 。
        判题标准:

        系统会用下面的代码来测试你的题解:

        int[] nums = [...]; // 输入数组
        int[] expectedNums = [...]; // 长度正确的期望答案

        int k = removeDuplicates(nums); // 调用

        assert k == expectedNums.length;
        for (int i = 0; i < k; i++) {
            assert nums[i] == expectedNums[i];
        }
        如果所有断言都通过，那么您的题解将被 通过。

        示例 1：

        输入：nums = [1,1,2]
        输出：2, nums = [1,2,_]
        解释：函数应该返回新的长度 2 ，并且原数组 nums 的前两个元素被修改为 1, 2 。不需要考虑数组中超出新长度后面的元素。
    )";
    LOG(INFO) << "demo: \n" << demo << "\n";

    std::vector<int> nums{1,1,2};

    // std::vector<int> tmp;
    // for (int i = 0; i < nums.size() - 1; i++)
    // {
    //     if (nums.at(i) == nums.at(i + 1))
    //     {
    //         tmp.push_back(i + 1);
    //         i++;
    //     }
    // }
    // for (auto& it : tmp)
    // {
    //     nums.erase(nums.begin() + it);
    // }

    auto it = std::unique(nums.begin(), nums.end());
    nums.erase(it, nums.end());

    LOG(INFO) << "nums' size: " << nums.size() << "\n";
    for (auto& it : nums)
    {
        LOG(INFO) << "value: " << it << "\n";
    }

    return 1;
}

int test_171(Message& message)
{
    LOG(INFO) << "test 171: Excel 表列序号\n";
    std::string demo = R"(
        给你一个字符串 columnTitle ，表示 Excel 表格中的列名称。返回 该列名称对应的列序号 。

        例如：

        A -> 1
        B -> 2
        C -> 3
        ...
        Z -> 26
        AA -> 27
        AB -> 28 
        ...
        

        示例 1:

        输入: columnTitle = "A"
        输出: 1
    )";
    LOG(INFO) << "demo: \n" << demo << "\n";

    std::string columnTitle{"AB"};

    const int change = 'A' - 1;
    int sum{0};
    for (auto& alt : columnTitle)
    {
        sum *= 26;
        sum += alt - change;
    }

    LOG(INFO) << "sum: " << sum << "\n";

    return 1;
}

int test_leetcode(Message& message)
{
    LOG(INFO) << "----test leetcode begin----\n";

    std::map<std::string, std::function<int(Message&)>>cmd_map = {
        {"test-2859", test_2859},
        {"test-88", test_88},
        {"test-27", test_27},
        {"test-26", test_26},
        {"test-171", test_171}
    };

    std::string cmd = message.second_layer;
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

    LOG(INFO) << "----test leetcode end----\n";

    return 1;
}