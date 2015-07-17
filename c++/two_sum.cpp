// Given an array of integers, find two numbers such that they add up to a specific target number.

// The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.

// You may assume that each input would have exactly one solution.

// Input: numbers={2, 7, 11, 15}, target=9
// Output: index1=1, index2=2

// @param {Integer[]} nums
// @param {Integer} target
// @return {Integer[]}

#include <vector>
#include <map>
#include <iostream>
using std::vector;
using std::map;
using std::cout;
using std::endl;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int, int> imap;
        vector<int> v;

        for (int i = 0; i <  nums.size(); ++i)
        {
        	if (imap.find(target - nums[i]) != imap.end())
        	{
      			v.push_back(imap[target - nums[i]] + 1);
      			v.push_back(i + 1);
        		return v;
        	}

        	imap[nums[i]] = i;
        }
    }
};

int main()
{
	vector<int> v1, v2;
	Solution s;
	v1.push_back(7);
	v1.push_back(2);
	v1.push_back(11);
	v1.push_back(15);

	v2 = s.twoSum(v1, 9);

	for (std::vector<int>::iterator v_it = v2.begin(); v_it != v2.end() ; ++v_it)
	{
		cout << *v_it << " ";
	}
	cout << endl;
}