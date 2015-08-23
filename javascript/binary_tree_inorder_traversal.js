// Given a binary tree, return the inorder traversal of its nodes' values.

// For example:
// Given binary tree {1,#,2,3},
//    1
//     \
//      2
//     /
//    3
// return [1,3,2].

/**
 * Definition for a binary tree node.
 * function TreeNode(val) {
 *     this.val = val;
 *     this.left = this.right = null;
 * }
 */
/**
 * @param {TreeNode} root
 * @return {number[]}
 */

var treeModule = require('./src/tree.js');

var inorderTraversal = function(root) {
	if (root === null)
		return [];

	var order, stack;
	order = [];
	stack = [];

	while (root !== null || stack.length !== 0)
	{
		if (root !== null)
		{
			stack.push(root);
			root = root.left;			
		}
		else
		{
			root = stack.pop();
			order.push(root.val);
			root = root.right;
		}
	}

	return order;
};

var root = treeModule.createTree();
treeModule.preorderTraverse(root);
var order;
order = inorderTraversal(root);
console.log(order);