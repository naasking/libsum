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

#define CTOR(ctor) struct { int tag; struct ctor data; }

/* create a new instance of the given sum */
#define LET(var, ctor, ...) MAKE(var, ctor, malloc, __VA_ARGS__)

/* provide a custom allocator */
#define MAKE(var, ctor, malloc, ...) do { \
  CTOR(ctor) __tmp = { ctor, { __VA_ARGS__ } }; \
  CTOR(ctor)* __tmpp = (CTOR(ctor)*)malloc(sizeof(__tmp)); \
  __tmpp->tag = __tmp.tag; \
  __tmpp->data = __tmp.data; \
  var = &(__tmpp->tag); } while (0)

//#define LET(var, ctor, l, ...) do { \
//  CTOR(ctor)* __tmp = (CTOR(ctor)*)malloc(sizeof(__tmp)); \
//  struct ctor *##l = &__tmp->data; \
//  __VA_ARGS__; \
//  var = &__tmp->_tag; } while (0)

/* deconstruct a sum type */
#define MATCH(X) int* MATCH_needs_new_scope = (int*)(X); switch(*MATCH_needs_new_scope) {

/* match a particular constructor */
#define AS(ctor, var) break; } case ctor##: { struct ctor* var = FROM(ctor, MATCH_needs_new_scope);

#define FROM(ctor, var) (struct ctor*)((char*)var + offsetof(CTOR(ctor), data))

/* match any constructor */
#define MATCHANY break; } default:
