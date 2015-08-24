# Given a sorted linked list, delete all duplicates such that each element appear only once.

# For example,
# Given 1->1->2, return 1->2.
# Given 1->1->2->3->3, return 1->2->3.

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

def delete_duplicates(head)
	return nil if head.nil?

	val = head.val
	pre_node = head.next
	node = head
	until pre_node.nil?
		pre_node = pre_node.next until pre_node.nil? || pre_node.val != val
		if pre_node.nil?		
			node.next = nil
			break
		end
		val = pre_node.val
		node.next = pre_node
		node = pre_node
		pre_node = pre_node.next
	end

	head
end

head = ListNode.new 0
head.next = ListNode.new 0
node = head.next
node.next = ListNode.new 1
node = node.next
node.next = ListNode.new 1
node = node.next
node.next = ListNode.new 1
node = node.next
node.next = ListNode.new 1

print_list head

head = delete_duplicates head
print_list head
