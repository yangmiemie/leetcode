# Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

# For example:
# Given binary tree {3,9,20,#,#,15,7},
#     3
#    / \
#   9  20
#     /  \
#    15   7
# return its level order traversal as:
# [
#   [3],
#   [9,20],
#   [15,7]
# ]

# Definition for a binary tree node.
# class TreeNode
#     attr_accessor :val, :left, :right
#     def initialize(val)
#         @val = val
#         @left, @right = nil, nil
#     end
# end

# @param {TreeNode} root
# @return {Integer[][]}

require_relative 'src/tree'
require 'byebug'

class TreeNode
  attr_accessor :val, :left, :right
  def initialize(val)
      @val = val
      @left, @right = nil, nil
  end
end

class TreeNode
	attr_accessor :level
end 


def level_order(root)
	stack = []
	level_order_list = []

	return [] if root.nil?
	(root.level = 0) && (stack << root)

	while stack[0]
		root = stack.shift
		
		if level_order_list.empty?
			level_order_list << [root.val]
		else
			level_order_list.last << root.val
		end
		
		(root.left.level = root.level + 1) && (stack << root.left) unless root.left.nil?
		(root.right.level = root.level + 1) && (stack << root.right) unless root.right.nil?

		level_order_list << [] if stack[0] && root.level < stack.first.level
	end

	level_order_list
end