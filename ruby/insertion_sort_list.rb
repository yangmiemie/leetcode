# Sort a linked list using insertion sort.

# Definition for singly-linked list.
# class ListNode
#     attr_accessor :val, :next
#     def initialize(val)
#         @val = val
#         @next = nil
#     end
# end

# @param {ListNode} head
# @return {ListNode}

require_relative 'src/list.rb'

def insertion_sort_list(head)
	return head if head.nil? || head.next.nil?

	pre_node = head
	node = head.next

	until node.nil?
		if pre_node.val <= node.val
			pre_node = node
			node = node.next
			next
		end

		pre_node.next = node.next
		position = head
		position = position.next while position.val < node.val && position != node
		position.val, node.val = node.val, position.val
		node.next = position.next
		position.next = node
		node = pre_node.next
	end

	head
end

list = create_rand_list 2
print_list list
list = insertion_sort_list list
print_list list