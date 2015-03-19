# Pattern Matching and Sum types for C
This is a set of macros that provide the ability to declare and pattern match on sum types:

    /* declare a sum type and its constructor tags */
    SUM(foo) {
      foo_one,
      foo_two,
    };
    /* declare each sum case */
    CASE(foo, foo_one) { int i; char c; };
    CASE(foo, foo_two) { double d; };
    
    void do_bar(foo f) {
      MATCH(f) {
        AS(foo_one, y) printf("foo_one: %d, %c\n", y->i, y->c);
        AS(foo_two, y) printf("foo_two: %d\n", y->d);
        MATCHANY 
          fprintf(stderr, "No such case!");
          exit(1);
      }
    }
    
    int main(int argc, char** argv) {
      foo f;
      LET(f, foo_one, (3, 'g')); /* (3,'g') is an initializer */
      do_bar(f);
    }

Note that each AS branch introduces a new scope, so you can declare new identifiers, unlike C's switch.

# Notes
 1. A MATCH statement must start in a position where new locals can be declared. In other words, in a new lexical scope, or after other locals have been declared.
 2. MATCHANY is mandatory, and must always come last.
 3. Each LET binding performs a dynamic memory allocation using malloc. The MAKE binding form allows you to specify a custom allocation function matching malloc's signature, but some form of allocation is needed.

# Future Work
Allow MATCH to discriminate on user-specified tag field names, eg. to allow matching on existing C unions instead of requiring them to adopt the SUM/CASE structure.

# License
My default license is LGPL v2, but I'm not sure how that interacts with the fact that the "library" consists solely of a header file, and thus has no runtime replaceable binary. I like the LGPL's conditions otherwise, so I'm open to other license suggestions that provide similar freedoms.
