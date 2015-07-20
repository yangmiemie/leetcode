require('qunitjs');

function add(a, b) {
	return a + b;
};

test("Test Method 1", function () {
	ok(add(1, 2) == 2, "Test Method 1 Pass");
});