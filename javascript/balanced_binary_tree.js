/**
 * Definition for a binary tree node.
 * function TreeNode(val) {
 *     this.val = val;
 *     this.left = this.right = null;
 * }
 */
/**
 * @param {TreeNode} root
 * @return {boolean}
 */
function TreeNode(val) {
	 this.val = val;
   this.left = this.right = null;
}

var abs = function(a) {
	return a > 0 ? a : -1 * a;
}

var max = function(a, b) {
	return a > b ? a : b;
}

var isTreeBalanced = function(root, height) {
	var leftBalanced, rightBalanced;
	var leftHeight, rightHeight;

	if (root === null)
	{
		height.value = 0;
		return true;
	}

	if (root.left === null && root.right === null)
	{
		height.value = 1;
		return true;
	}

	leftHeight = {};
	rightHeight = {};
	leftBalanced = isTreeBalanced(root.left, leftHeight);	
	rightBalanced = isTreeBalanced(root.right, rightHeight);

	height.value = max(leftHeight.value, rightHeight.value) + 1;
	return abs(leftHeight.value - rightHeight.value) <= 1 && leftBalanced && rightBalanced;
};

var isBalanced = function(root) {
   var height = {};
   return isTreeBalanced(root, height);
};

var insert = function(root, value) {
	if (root == null)
		return new TreeNode(value);

	if (root.val > value)
		root.left = insert(root.left, value);
	else if (root.val < value)
		root.right = insert(root.right, value);

	return root;
}

var postTraverse = function(root) {
	if (root == null)
		return;

	console.log(root.val);
	postTraverse(root.left);
	postTraverse(root.right);
}

var array = [1, 2, 3]
var i;
var root;

root = null
for (i = 0; i < array.length; ++i) {
	root = insert(root, array[i]);
}

console.log(isBalanced(root));

