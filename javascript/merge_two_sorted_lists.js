// Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.

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

var mergeTwoLists = function(headA, headB) {
	if (headA === null || headA === undefined)
		return headB;

	if (headB === null || headB === undefined)
		return headA;

	var head;

	if (headA.val < headB.val)
	{
		head = headA;
		headA = headA.next;
	}
	else
	{
		head = headB;
		headB = headB.next;
	}

	node = head;
	while (headA !== null && headB !== null)
	{
		if (headA.val < headB.val)
		{
			node.next = headA;
			headA = headA.next;
		}
		else
		{
			node.next = headB;
			headB = headB.next;
		}

		node = node.next;
	}

	if (headA !== null)
		node.next = headA;

	if (headB !== null)
		node.next = headB;

	return head;
};

var head1 = listModule.createList(10);
var head2 = listModule.createList(10);

listModule.printList(head1);
listModule.printList(head2);

var head = mergeTwoLists(head1, head2);
listModule.printList(head);


