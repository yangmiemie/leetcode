# Write a function to delete a node (except the tail) in a singly linked list, given only access to that node.

# Supposed the linked list is 1 -> 2 -> 3 -> 4 and you are given the third node with value 3, the linked list should become 1 -> 2 -> 4 after calling your function.

# Definition for singly-linked list.
# class ListNode
#     attr_accessor :val, :next
#     def initialize(val)
#         @val = val
#         @next = nil
#     end
# end

# @param {ListNode} node
# @return {Void} Do not return anything, modify node in-place instead.

require_relative 'src/list.rb'

def delete_node(node)
	node.val = node.next.val
	node.next = node.next.next;
	return
end

list = create_list(10)
print_list list

# node = list
# node = node.next.next.next
delete_node list
print_list list

list = create_identical_list 10, 0
print_list list

delete_node list
print_list list