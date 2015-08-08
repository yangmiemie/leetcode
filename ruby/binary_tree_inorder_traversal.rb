# Given a binary tree, return the inorder traversal of its nodes' values.

# For example:
# Given binary tree {1,#,2,3},
#    1
#     \
#      2
#     /
#    3
# return [1,3,2].

# Definition for a binary tree node.
# class TreeNode
#     attr_accessor :val, :left, :right
#     def initialize(val)
#         @val = val
#         @left, @right = nil, nil
#     end
# end

# @param {TreeNode} root
# @return {Integer[]}

require_relative 'src/tree.rb'

class TreeNode
    attr_accessor :val, :left, :right
    def initialize(val)
        @val = val
        @left, @right = nil, nil
    end
end

def inorder_traversal(root)
	stack = []
	inorder_list = []

	while root || stack.size != 0
		if root
			stack << root
			root = root.left
		else
			root = stack.pop
			inorder_list << root.val

			if root.right
				root = root.right
			else
				root = nil
			end
		end
	end

	inorder_list
end