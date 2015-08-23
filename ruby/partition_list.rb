# Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

# You should preserve the original relative order of the nodes in each of the two partitions.

# For example,
# Given 1->4->3->2->5->2 and x = 3,
# return 1->2->2->4->3->5.

# Definition for singly-linked list.
# class ListNode
#     attr_accessor :val, :next
#     def initialize(val)
#         @val = val
#         @next = nil
#     end
# end

# @param {ListNode} head
# @param {Integer} x
# @return {ListNode}

require_relative 'src/list.rb'

def partition(head, x)
	return head if head.nil? || head.next.nil?

	stack = []
	node = head
	until node.next.nil?
		stack << node
		node = node.next
	end

	until stack.size === 0
		node = stack.pop
		pre_node = node.next
		while pre_node != nil && node.val >= x && pre_node.val < x
			node.val, pre_node.val = pre_node.val, node.val
			node = pre_node
			pre_node = pre_node.next
		end
	end

	head
end

rand_list = create_rand_list 16
print_list rand_list
rand_list = partition rand_list, 0
print_list rand_list
