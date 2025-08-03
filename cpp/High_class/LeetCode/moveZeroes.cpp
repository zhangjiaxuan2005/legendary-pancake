//
// Created by 17246 on 2025/8/2.
// LeetCode 49
//

#include <iostream>
#include <vector>
using namespace std;

void moveZeroes(vector<int>& nums)
{
    int left = 0;
    for (int right = 0; right < nums.size(); right++)
    {
        if (nums[right] != 0)
        {
            swap(nums[left], nums[right]);
            left++;
        }
    }
}

int main()
{
    vector nums = {0, 1, 0, 3, 12};
    moveZeroes(nums);
    for (int num : nums)
    {
        cout << num << ", ";
    }
}
