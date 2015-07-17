# Given an array of integers, find two numbers such that they add up to a specific target number.

# The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.

# You may assume that each input would have exactly one solution.

# Input: numbers={2, 7, 11, 15}, target=9
# Output: index1=1, index2=2

# @param {Integer[]} nums
# @param {Integer} target
# @return {Integer[]}

def two_sum(nums, target)
	hash = {}

	nums.each_with_index do |x, index|
		return [hash[target - x] + 1, index + 1] if hash.has_key? target - x
		hash[x] = index;
	end

	[]
end

describe :two_sum do
	target = 9

	it 'exist one solution' do
		numbers = [2, 7, 11, 15]
		expect(two_sum numbers, target).to eq [1, 2]
	end

	it 'exist one solution with unorder' do
		numbers = [7, 11, 15, 2]
		expect(two_sum numbers, target).to eq [1, 4]
	end

	it 'solution not found' do
		numbers = [7, 11, 15, 3]
		expect(two_sum numbers, target).to be_empty
	end

	it 'empty nums' do
		numbers = []
		expect(two_sum numbers, target).to be_empty
	end
end
