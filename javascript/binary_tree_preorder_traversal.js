// Given a binary tree, return the preorder traversal of its nodes' values.

// For example:
// Given binary tree {1,#,2,3},
//    1
//     \
//      2
//     /
//    3
// return [1,2,3].

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

// var preorderTraversal = function(root) {
// 	if (root === null)
// 		return [];

// 	var stack = [];
// 	stack.push(root.val);
	
// 	if (root.left !== null)
// 		stack = stack.concat(preorderTraversal(root.left));
	
// 	if (root.right !== null)
// 		stack = stack.concat(preorderTraversal(root.right));
	
// 	return stack;
// };

var preorderTraversal = function(root) {
	if (root === null)
		return [];

	var stack, order;
	stack = [];
	order = [];

	while (root !== null || stack.length !== 0)
	{
		if (root !== null)
		{
			order.push(root.val);

			if (root.right !== null)
				stack.push(root.right);
			root = root.left;
		}
		else
		{
			root = stack.pop();
		}
	}

	return order;
}

var root = treeModule.createTree();
treeModule.preorderTraverse(root);
var order;
order = preorderTraversal(root);
console.log(order);