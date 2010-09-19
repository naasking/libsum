
#include <stdio.h>
#include "libsum.h"

SUM(foo) {
  foo_one,
  foo_two,
};

CASE(foo, foo_one) { int i; char c; };
CASE(foo, foo_two) { double d; };

int main(int argc, char** argv) {
	//LET(foo, f, foo_one, 3, 'g');
	foo f;
	LET(f, foo_one, 3, 'g');

	/*foo x;
	LET(x, foo_two, { 4.567 });*/
	{
	MATCH(f) {
	  AS(foo_one, y) printf("foo_one: %d, %c\n", y->i, y->c);
	  AS(foo_two, y) printf("foo_two: %d\n", y->d);
	  MATCHANY
		fprintf(stderr, "No such case!");
		exit(1);
	}
	}
	getc(stdin);
	return 0;
}
