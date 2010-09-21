/*
 * Unit tests for sums and pattern matching.
 *
 * License: LGPL
 * Copyright 2010 Sandro Magi
 */

#include <stdio.h>
#include <assert.h>
#include "libsum.h"

SUM(foo) {
  foo_one,
  foo_two,
};

CASE(foo, foo_one) { int i; char c; };
CASE(foo, foo_two) { double d; };

int test(foo f) {
	MATCH(f) {
		AS(foo_one, y)
			printf("foo_one: %d, %c\n", y->i, y->c);
			return 1;
		AS(foo_two, y)
			printf("foo_two: %f\n", y->d);
			return 2;
		MATCHANY
			fprintf(stderr, "No such case %d!\n", *f);
			return 3;
	}
}

int main(int argc, char** argv) {
	{
		foo f;
		LET(f, foo_one, 3, 'g');
		assert(1 == test(f));
		free(f);
	}
	{
		foo x;
		LET(x, foo_two, 4.567);
		assert(2 == test(x));

		/* test MATCHANY */
		*x = (enum foo)4;
		assert(3 == test(x));

		free(x);
	}
	/*printf("size foo_one: %d\n", sizeof(CTOR(foo_one)));
	printf("size foo_two: %d\n", sizeof(CTOR(foo_two)));*/

	getc(stdin);

	return 0;
}
