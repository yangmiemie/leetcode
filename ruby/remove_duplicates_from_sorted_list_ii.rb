# Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

# For example,
# Given 1->2->3->3->4->4->5, return 1->2->5.
# Given 1->1->1->2->3, return 2->3.

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
	return head if head.nil? || head.next.nil?

	fake_head = ListNode.new -1
	fake_head.next = head

	node1 = fake_head.next.next
	node2 = fake_head
	until node1.nil?
		node1 = node1.next until node1.nil? || node1.val != node2.next.val
		
		if node1.nil?
			node2.next = nil unless node2.next.next.nil?
			break
		end

		if node2.next.next == node1
			node2 = node2.next
			node1 = node1.next
		else
			node2.next = node1
			node1 = node1.next
		end
	end

	return fake_head.next
end

head = ListNode.new -1
head.next = ListNode.new 0
node = head.next
node.next = ListNode.new 1
node = node.next
node.next = ListNode.new 1
node = node.next
node.next = ListNode.new 1
node = node.next
node.next = ListNode.new 2
node = node.next
node.next = ListNode.new 3

print_list head

head = delete_duplicates head
print_list head