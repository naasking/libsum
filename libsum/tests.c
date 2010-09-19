
#include <stdio.h>
#include "libsum.h"

SUM(foo) {
  foo_one,
  foo_two,
};

CASE(foo, foo_one) { int i; char c; };
CASE(foo, foo_two) { double d; };

void test(foo f) {
	MATCH(f) {
		AS(foo_one, y) printf("foo_one: %d, %c\n", y->i, y->c);
		AS(foo_two, y) printf("foo_two: %f\n", y->d);
		MATCHANY
			fprintf(stderr, "No such case!");
			exit(1);
	}
}

int main(int argc, char** argv) {
	{
		foo f;
		LET(foo, f, foo_one, 3, 'g');
		//LET(f, foo_one, x, x->i=3, x->c='g');
		test(f);
	}
	{
		foo x;
		LET(foo, x, foo_two, 4.567);
		//LET(x, foo_two, y, y->d = 4.567);
		test(x);
	}
	printf("size foo_one: %d\n", sizeof(CTOR(foo_one)));
	printf("size foo_two: %d\n", sizeof(CTOR(foo_two)));

	getc(stdin);
	return 0;
}
