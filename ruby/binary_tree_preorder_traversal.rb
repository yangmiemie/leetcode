# Given a binary tree, return the preorder traversal of its nodes' values.

# For example:
# Given binary tree {1,#,2,3},
#    1
#     \
#      2
#     /
#    3
# return [1,2,3].

# Definition for a binary tree node.
# class TreeNode
#     attr_accessor :val, :left, :right
#     def initialize(val)
#         @val = val
#         @left, @right = nil, nil
#     end
# end

require_relative 'src/tree'

class TreeNode
    attr_accessor :val, :left, :right
    def initialize(val)
        @val = val
        @left, @right = nil, nil
    end
end

# @param {TreeNode} root
# @return {Integer[]}
def preorder_traversal(root)
	preorder_list = []
	stack = []

	return [] if root.nil?
	stack << root

	while stack.size != 0
		root = stack.pop
		preorder_list << root.val
		stack << root.right if root.right
		stack << root.left if root.left
	end

	preorder_list
end