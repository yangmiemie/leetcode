require_relative '../validate_binary_search_tree.rb'

describe 'LeetCode'  do
	context 'validate binary search tree' do
		it 'a valid binary search tree' do
			array = [6, 4, 7]
			root = nil
			array.each { |v| root = insert v, root }
			expect(is_valid_bst root).to be_truthy
		end

		it 'a emtpy binary search tree' do
			array = []
			root = nil
			array.each { |v| root = insert v, root }
			expect(is_valid_bst root).to be_truthy
		end

		it 'a invalid binary search tree' do
			root = TreeNode.new(10)
			root.left = TreeNode.new(20)

			expect(is_valid_bst root).to be_falsy
		end	
	end
end