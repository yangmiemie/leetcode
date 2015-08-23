function TreeNode(val) {
	this.val = val;
  this.left = this.right = null;
}

var createTree = function() {
	var root, array, len;

	array = [5, 7, 4, 6, 9, 2];
	len = array.length;

	for (var i = 0, root = null; i < len; ++i)
		root = insert(root, array[i]);

	return root;
}

var insert = function(root, value) {
	if (root == null)
		return new TreeNode(value);

	if (root.val > value)
		root.left = insert(root.left, value);
	else if (root.val < value)
		root.right = insert(root.right, value);

	return root;
}

var postorderTraverse = function(root) {
	if (root == null)
		return;

	postorderTraverse(root.left);
	postorderTraverse(root.right);
	console.log(root.val);
}

var preorderTraverse = function(root) {
	if (root == null)
		return;

	console.log(root.val);
	preorderTraverse(root.left);
	preorderTraverse(root.right);
}

var inorderTraverse = function(root) {
	if (root == null)
		return;

	inorderTraverse(root.left);
	console.log(root.val);
	inorderTraverse(root.right);
}

exports.createTree = createTree;
exports.postorderTraverse = postorderTraverse;
exports.inorderTraverse = inorderTraverse;
exports.preorderTraverse = preorderTraverse;