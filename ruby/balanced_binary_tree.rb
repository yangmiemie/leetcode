# Definition for a binary tree node.
# class TreeNode
#     attr_accessor :val, :left, :right
#     def initialize(val)
#         @val = val
#         @left, @right = nil, nil
#     end
# end

# @param {TreeNode} root
# @return {Boolean}

class TreeNode
	attr_accessor :val, :left, :right

	def initialize(val)
		@val = val;
		@left, @right = nil, nil
	end
end

def max(a, b)
	return a > b ? a : b
end

def is_tree_balanced(root)
	return [true, 0] if root.nil?
	return [true, 1] if root.left.nil? && root.right.nil?

	leftResult = is_tree_balanced(root.left)
	leftBalance, leftHeight = leftResult[0], leftResult[1]
	
	rightResult = is_tree_balanced(root.right)
	rightBalance, rightHeight = rightResult[0], rightResult[1]

	rootBalance = (leftHeight - rightHeight).abs > 1 ? false : true

	[leftBalance && rightBalance && rootBalance, max(leftHeight, rightHeight) + 1]
end

def is_balanced(root)
	balanced = is_tree_balanced(root)[0]
	balanced    
end

def insert(value, root)
	return TreeNode.new(value) if root.nil?

	if root.val > value
		root.left = insert value, root.left
	elsif root.val < value
		root.right = insert value, root.right
	end
	
	root
end

def preorder_traverse(root)
	return if root.nil?

	print root.val, " "
	preorder_traverse(root.left)
	preorder_traverse(root.right)
end

def inorder_traverse(root)
	return if root.nil?

	inorder_traverse(root.left)
	print root.val, " "
	inorder_traverse(root.right)
end

def postorder_traverse(root)
	return if root.nil?

	postorder_traverse(root.left)
	postorder_traverse(root.right)
	print root.val, " "
end


