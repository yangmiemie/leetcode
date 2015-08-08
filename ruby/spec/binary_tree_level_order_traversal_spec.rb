require_relative '../binary_tree_level_order_traversal'

describe 'LeetCode' do
	context 'binary_tree_level_order_traversal' do
		it 'a binary search tree' do
			array = [6, 4, 8, 2, 5, 7, 9]
			root = nil

			array.each { |value| root = insert value, root }
			expect(level_order root).to eql [[6], [4, 8], [2, 5, 7, 9]]			
		end
	end
end