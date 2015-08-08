require_relative '../binary_tree_inorder_traversal'

describe 'LeetCode' do
	context 'binary tree inorder traversal' do
		it 'traverse a binary tree' do
			array = [6, 4, 7]
			root = nil

			array.each { |value| root = insert value, root }
			expect(inorder_traversal root).to eq [4, 6, 7]
		end
	end
end