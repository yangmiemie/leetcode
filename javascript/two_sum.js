/**
 * @param {number[]} nums
 * @param {number} target
 * @return {number[]}
 */
var twoSum = function(nums, target) {
    hash = {}

    for (var i = 0; i < nums.length; ++i)
    {
    	if (target - nums[i] in hash)
    	{
    		return [hash[target - nums[i]] + 1, i + 1];
    	}

    	hash[nums[i]] = i;
    }
};

numbers = [2, 7, 11, 15];
console.log(twoSum(numbers, 9));