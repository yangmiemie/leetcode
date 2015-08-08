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


