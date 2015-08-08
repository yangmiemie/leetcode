# Given a binary tree, return the postorder traversal of its nodes' values.

# For example:
# Given binary tree {1,#,2,3},
#    1
#     \
#      2
#     /
#    3
# return [3,2,1].

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

require_relative 'src/tree'

class TreeNode
    attr_accessor :val, :left, :right
    def initialize(val)
        @val = val
        @left, @right = nil, nil
    end
end

def postorder_traversal(root)
	postorder_list = []
	stack = []
	last_visited = nil

	while root || stack.size != 0
		if root
			stack << root
			root = root.left
		else
			root = stack.pop

			if root.right.nil? || root.right == last_visited
				postorder_list << root.val
				last_visited = root
				root = nil
			else
				stack << root
				root = root.right
			end
		end
	end

	postorder_list
end
