# Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

# Definition for singly-linked list.
# class ListNode
#     attr_accessor :val, :next
#     def initialize(val)
#         @val = val
#         @next = nil
#     end
# end

# Definition for a binary tree node.
# class TreeNode
#     attr_accessor :val, :left, :right
#     def initialize(val)
#         @val = val
#         @left, @right = nil, nil
#     end
# end

# @param {ListNode} head
# @return {TreeNode}

require_relative 'src/list.rb'
require_relative 'src/tree.rb'

def convert_list_to_array(head)
	nodes = []
	until head.nil?
		nodes << head.val
		head = head.next
	end

	nodes
end

def convert_array_to_bst(array, size)
	return nil if size == 0 || array.nil?
	return TreeNode.new array[0] if size == 1

	root = TreeNode.new array[size / 2]
	root.left = convert_array_to_bst array, size / 2
	root.right = convert_array_to_bst array[(size / 2 + 1)..-1], size - size / 2 - 1
	root
end

def sorted_list_to_bst(head)
	return nil if head.nil?

	list_array = convert_list_to_array head
	convert_array_to_bst list_array, list_array.size
end

list = create_list(10)
print_list list

head = sorted_list_to_bst nil
preorder_traverse head
puts