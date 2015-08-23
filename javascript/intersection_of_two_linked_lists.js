// Write a program to find the node at which the intersection of two singly linked lists begins.


// For example, the following two linked lists:

// A:          a1 → a2
//                    ↘
//                      c1 → c2 → c3
//                    ↗            
// B:     b1 → b2 → b3
// begin to intersect at node c1.


// Notes:

// If the two linked lists have no intersection at all, return null.
// The linked lists must retain their original structure after the function returns.
// You may assume there are no cycles anywhere in the entire linked structure.
// Your code should preferably run in O(n) time and use only O(1) memory.

/**
 * Definition for singly-linked list.
 * function ListNode(val) {
 *     this.val = val;
 *     this.next = null;
 * }
 */

/**
 * @param {ListNode} headA
 * @param {ListNode} headB
 * @return {ListNode}
 */
var listModule = require('./src/list.js');

function getLengthOfList(head) {
	var i;
	for (i = 0; head !== null; head = head.next, ++i);
	return i;
};

var getIntersectionNode = function(headA, headB) {
	if (headA === null || headB === null)
		return null;

	var lenA, lenB, i;
	lenA = getLengthOfList(headA);
	lenB = getLengthOfList(headB);

	if (lenA > lenB)
		for (i = 0; i < lenA - lenB; ++i, headA = headA.next);
	else if (lenB > lenA)
		for (i = 0; i < lenB - lenA; ++i, headB = headB.next);

	while (headA != headB)
	{
		headA = headA.next;
		headB = headB.next;
	}

	return headA;
}

var head1 = listModule.createEvenList(4);
var head2 = listModule.createOddList(4);
var head = listModule.createList(5);
var node;
for (node = head1; node.next !== null; node = node.next);
node.next = head;

for (node = head2; node.next !== null; node = node.next);
node.next = head;

listModule.printList(head1);
listModule.printList(head2);

node = getIntersectionNode(head1, head2);
console.log(node.val);
