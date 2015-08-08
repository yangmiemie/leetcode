require_relative '../binary_tree_preorder_traversal'

describe 'LeetCode' do
	context 'binary_tree_preorder_traversal' do
		it 'a binary search tree' do
			array = [6, 4, 8, 2, 5, 7, 9]
			root = nil

			array.each { |value| root = insert value, root }
			expect(preorder_traversal root).to eql [6, 4, 2, 5, 8, 7, 9]			
		end

		it 'an empty tree' do
			array = []
			root = nil

			array.each { |value| root = insert value, root }
			expect(preorder_traversal root).to eql []
		end
	end
end
