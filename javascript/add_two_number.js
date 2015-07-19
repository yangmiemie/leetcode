/**
 * Definition for singly-linked list.
 * function ListNode(val) {
 *     this.val = val;
 *     this.next = null;
 * }
 */
/**
 * @param {ListNode} l1
 * @param {ListNode} l2
 * @return {ListNode}
 */

function ListNode(val) {
	this.next = null;
	this.val = val;
}

var addTwoNode = function(carry, l1, l2)
{
	var sum, value;
	var val2;

	val2 = l2 === undefined ? 0 : l2.val;
	sum = carry + l1.val + val2;
	value = sum >= 10 ? sum - 10 : sum;
	carry = sum >= 10 ? 1 : 0;

	return [value, carry];
}

var addTwoNumbers = function(l1, l2) {
    if (l1.length === 0)
    	return l2;

    if (l2.length === 0)
    	return l1;

    var head, list, node, l;
    var result, carry;

    result = addTwoNode(0, l1, l2);
    head = new ListNode(result[0]);
    carry = result[1];
    l1 = l1.next;
    l2 = l2.next;
    list = head;

    while ((l1 !== null) && (l2 !== null))
    {
    	result = addTwoNode(carry, l1, l2);
    	node = new ListNode(result[0]);
    	carry = result[1];
    	list.next = node;
    	list = list.next;
    	l1 = l1.next;
    	l2 = l2.next;
    }

    l = (l1 !== null) ? l1 : l2;
    while (l !== null)
    {
    	result = addTwoNode(carry, l);
    	node = new ListNode(result[0]);
    	carry = result[1];
    	list.next = node;
    	list = list.next;
    	l = l.next;
    }

    if (carry > 0)
    {
    	node = new ListNode(carry);
    	list.next = node;
    	list = list.next;
    }

    return head;
};

var initList = function(array) {
	if (array.length === 0)
		return null;

	var head, list, node;
	var i;
	
	head = new ListNode(array[0]);
	list = head;
	for (i = 1; i < array.length; ++i)
	{
		node = new ListNode(array[i]);
		list.next = node;
		list = node;
	}

	return head;
}

var printList = function(list) {
	while (list != null)
	{
		console.log(list.val);
		list = list.next;
	}
}

// (2 -> 4 -> 3) + (5 -> 6 -> 4)

var a1, a2;
var l1, l2, list;

a1 = [1];
a2 = [9, 9];

l1 = initList(a1);
l2 = initList(a2);

list = addTwoNumbers(l1, l2);
printList(list);