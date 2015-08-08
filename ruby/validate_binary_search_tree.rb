# Given a binary tree, determine if it is a valid binary search tree (BST).

# Assume a BST is defined as follows:

# The left subtree of a node contains only nodes with keys less than the node's key.
# The right subtree of a node contains only nodes with keys greater than the node's key.
# Both the left and right subtrees must also be binary search trees.

# Definition for a binary tree node.
# class TreeNode
#     attr_accessor :val, :left, :right
#     def initialize(val)
#         @val = val
#         @left, @right = nil, nil
#     end
# end

# @param {TreeNode} root
# @return {Boolean}

require_relative 'src/tree.rb'

class TreeNode
	attr_accessor :val, :left, :right
	def initialize(val)
		@val = val
		@left, @right = nil, nil
	end
end

def is_valid_bst(root)
	stack = []
	inorder_list = []

	while root || stack.size != 0
		if root
			stack << root
			root = root.left
		else
			root = stack.pop
			return false if inorder_list[0] && root.val <= inorder_list.last
			inorder_list << root.val

			if root.right
				root = root.right
			else
				root = nil
			end
		end
	end

	true
end

