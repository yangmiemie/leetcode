require_relative '../two_sum'

describe 'LeetCode' do
	context :two_sum do
		target = 9

		it 'exist one solution' do
			numbers = [2, 7, 11, 15]
			expect(two_sum numbers, target).to eq [1, 2]
		end

		it 'exist one solution with unorder' do
			numbers = [7, 11, 15, 2]
			expect(two_sum numbers, target).to eq [1, 4]
		end

		it 'solution not found' do
			numbers = [7, 11, 15, 3]
			expect(two_sum numbers, target).to be_empty
		end

		it 'empty nums' do
			numbers = []
			expect(two_sum numbers, target).to be_empty
		end
	end	

end