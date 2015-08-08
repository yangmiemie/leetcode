require_relative '../binary_tree_postorder_traversal'

describe 'LeetCode' do
	context 'binary_tree_postorder_traversal' do
		it 'a binary search tree' do
			array = [6, 4, 8, 2, 5, 7, 9]
			root = nil

			array.each { |value| root = insert value, root }
			expect(postorder_traversal root).to eql [2, 5, 4, 7, 9, 8, 6]
		end

		it 'an empty tree' do
			array = []
			root = nil

			array.each { |value| root = insert value, root }
			expect(postorder_traversal root).to eql []
		end
	end
end
