// Given a binary tree, return the postorder traversal of its nodes' values.

// For example:
// Given binary tree {1,#,2,3},
//    1
//     \
//      2
//     /
//    3
// return [3,2,1].

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

var postorderTraversal = function(root) {
	if (root === null)
		return [];

	var order, stack, lastVisited;
	order = [];
	stack = [];
	lastVisited = null;

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
			if (root.right === null || root.right === lastVisited)
			{
				order.push(root.val);
				lastVisited = root;
				root = null;
			}
			else
			{
				stack.push(root);
				root = root.right;				
			}
		}
	}

	return order;
};

var root = treeModule.createTree();
treeModule.preorderTraverse(root);
var order;
order = postorderTraversal(root);
console.log(order);