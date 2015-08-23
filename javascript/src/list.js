function ListNode(val) {
	this.val = val;
	this.next = null;
};

function createOddList(max) {
	var head = new ListNode(0);
	var node = head;

	for (var i = 1; i < max; ++i)
	{
		node.next = new ListNode(i * 2 + 1);
		node = node.next;
	}

	return head;
};

function createEvenList(max) {
	var head = new ListNode(0);
	var node = head;

	for (var i = 1; i < max; ++i)
	{
		node.next = new ListNode(i * 2);
		node = node.next;
	}

	return head;
};

function createList(max) {
	var head = new ListNode(1);
	var node = head;

	for (var i = 2; i < max; ++i)
	{
		node.next = new ListNode(i);
		node = node.next;
	}

	return head;
};

function printList(list) {
	var str = '';
	while (list != null)
	{
		str += list.val;
		str += ' ';
		list = list.next;
	}
	console.log(str);
};

exports.createOddList = createOddList;
exports.createEvenList = createEvenList;
exports.createList = createList;
exports.printList = printList;
