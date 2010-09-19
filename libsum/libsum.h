/*
 * Disjoint unions, aka sum types, and pattern matching for C.
 */

#include <memory.h>
#include <stdlib.h>
#include <stddef.h>

/* declare a sum type, which externally just looks like a pointer
 * to an enum */
#define SUM(name) typedef enum name* name; enum name

/* declare a concrete instance of the sum, which declares its structure 
 * and constructors */
#define CASE(sum, ctor) struct ctor

#define CTOR(ctor) struct { int _tag; struct ctor data; }

/* create a new instance of the given sum */
/* alternately, could use __VA_ARGS__ for initializer */
#define LET(var, ctor, ...) do { \
  CTOR(ctor) __tmp = { ctor, { __VA_ARGS__ } }; \
  var = NEW(ctor); } while (0)

#define NEW(ctor) memcpy( (CTOR(ctor)*)malloc(sizeof(CTOR(ctor))), &__tmp, sizeof(__tmp))

/* deconstruct a sum type */
#define MATCH(X) int* MATCH_needs_new_scope = (int*)(X); switch(*MATCH_needs_new_scope) {

/* match a particular constructor */
#define AS(ctor, var) break; } case ctor##: { struct ctor* var = (struct ctor*)((char*)MATCH_needs_new_scope + offsetof(CTOR(ctor), data));

/* match any constructor */
#define MATCHANY break; } default:
