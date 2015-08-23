class ListNode
    attr_accessor :val, :next
    def initialize(val)
        @val = val
        @next = nil
    end
end

def create_list(max)
	head = ListNode.new 0
	(1..max - 1).inject(head) { |head, val| head.next = ListNode.new(val); head = head.next }
	head
end

def create_identical_list(max, value)
	head = ListNode.new value
	(1..max - 1).inject(head) { |head, val| head.next = ListNode.new(value); head = head.next }
	head
end

def create_rand_list(max)
	head = ListNode.new rand(max * 2)
	(1..max - 1).inject(head) { |head, val| head.next = ListNode.new(rand(max * 2)); head = head.next }
	head
end


def print_list(head)
	until head.nil?
		print head.val, ' '
		head = head.next
	end

	puts
end
