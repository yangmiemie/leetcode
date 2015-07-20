require_relative '../balanced_binary_tree.rb'

describe 'LeetCode' do
	context 'balanced binary tree' do
		it 'two elements in the tree' do
			a = [8, 4]
			root = nil

			a.each { |x| root = insert x, root }
			expect(is_balanced(root)).to be_truthy
		end

		it 'three elements in the tree which is not balanced' do
			a = [8, 4, 3]
			root = nil

			a.each { |x| root = insert x, root }
			expect(is_balanced(root)).to be_falsy
		end

		it 'three elements in the tree which is balanced' do
			a = [8, 4, 10]
			root = nil

			a.each { |x| root = insert x, root }
			expect(is_balanced(root)).to be true
		end
	end
end
