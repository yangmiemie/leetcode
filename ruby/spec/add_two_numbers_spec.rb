require_relative '../add_two_numbers'

describe 'LeetCode' do

	context 'add_two_numbers' do
		it 'add two list with same length' do
			a1 = [2, 4, 3]
			a2 = [5, 6, 4]
			l1 = init_list a1
			l2 = init_list a2

			l = add_two_numbers l1, l2

			expect(l.val).to eql 7
			l = l.next
			expect(l.val).to eql 0
			l = l.next
			expect(l.val).to eql 8
			l = l.next
			expect(l).to be_nil
		end

		it 'add two list with different length' do
			a1 = [2, 4, 3]
			a2 = [5, 6, 4, 6]
			l1 = init_list a1
			l2 = init_list a2
			
			l = add_two_numbers l1, l2

			expect(l.val).to eql 7
			l = l.next
			expect(l.val).to eql 0
			l = l.next
			expect(l.val).to eql 8
			l = l.next
			expect(l.val).to eql 6
			l = l.next
			expect(l).to be_nil
		end

		it 'add two list with last digit greater than 10' do
			a1 = [2, 4, 3]
			a2 = [5, 6, 8]
			l1 = init_list a1
			l2 = init_list a2

			l = add_two_numbers l1, l2

			expect(l.val).to eql 7
			l = l.next
			expect(l.val).to eql 0
			l = l.next
			expect(l.val).to eql 2
			l = l.next
			expect(l.val).to eql 1
			l = l.next
			expect(l).to be_nil
		end

		it 'add two list with empty array' do
			a1 = [2, 4, 3]
			a2 = []
			l1 = init_list a1
			l2 = init_list a2

			l = add_two_numbers l1, l2

			expect(l.val).to eql 2
			l = l.next
			expect(l.val).to eql 4
			l = l.next
			expect(l.val).to eql 3
			l = l.next
			expect(l).to be_nil
		end
	end
end
