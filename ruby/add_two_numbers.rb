# You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

# Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
# Output: 7 -> 0 -> 8


# Definition for singly-linked list.
# class ListNode
#     attr_accessor :val, :next
#     def initialize(val)
#         @val = val
#         @next = nil
#     end
# end

# @param {ListNode} l1
# @param {ListNode} l2
# @return {ListNode}

class ListNode
    attr_accessor :val, :next
    def initialize(val)
        @val = val
        @next = nil
    end
end

def add_two_node(carry, l1, *args)
	val2 = args.size > 0 ? args[0].val : 0
	sum = l1.val + val2 + carry
	carry = sum >= 10 ? 1 : 0
	value = carry > 0 ? sum - 10 : sum
	l1 = l1.next
	args[0] = args[0].next if args.size > 0
	[value, carry, l1, args[0]]
end

def add_two_numbers(l1, l2)
	return l1 if l2.nil?
	return l2 if l1.nil?

	result = add_two_node(0, l1, l2)
	value, carry, l1, l2 = result[0], result[1], result[2], result[3]
	head = ListNode.new(value)
	list = head

	while !l1.nil? && !l2.nil?
		result = add_two_node(carry, l1, l2)
		value, carry, l1, l2 = result[0], result[1], result[2], result[3]
		node = ListNode.new(value)
		list.next = node
		list = node
	end

	l = l1.nil? ? l2 : l1
	while !l.nil?
		result = add_two_node(carry, l)
		value, carry, l = result[0], result[1], result[2]
		node = ListNode.new(value)
		list.next = node
		list = node
	end

 	if (carry > 0)
 		node = ListNode.new(carry)
 		list.next = node
 		list = node
 	end

	head
end

def init_list(array)
	return nil if array.size == 0

	head = ListNode.new array[0]
	l = head

	(1...array.size).each do |i|
		node = ListNode.new array[i]
		l.next = node
		l = node
	end

	head
end

def print_list list
	while !list.nil?
		print list.val, " "
		list = list.next
	end

	puts
end

# (2 -> 4 -> 3) + (5 -> 6 -> 4)
# a1 = [2, 4, 3]
# a2 = [5, 6, 4]

# l1 = init_list a1
# l2 = init_list a2

# print_list l1
# print_list l2

# l = add_two_numbers l1, l2
# p l
# print_list l