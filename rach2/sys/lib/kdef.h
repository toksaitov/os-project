#ifndef _KDEF_H_
#define _KDEF_H_

/* NULL pointer */
#define NULL ((void*) 0)

/* Boolean data type */
typedef int bool;

#define false 0
#define true  1

/*
 * An unsigned integer type to represent size values of data structures.
 */
typedef unsigned int size_t;

/*
 * A signed integer type to represent size values of data structures.
 */
typedef signed int ssize_t;

/*
 * A signed integer type to store the difference between two pointers.
 */
typedef signed int ptrdiff_t;

#endif
