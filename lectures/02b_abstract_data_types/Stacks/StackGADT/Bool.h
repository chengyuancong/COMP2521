// Bool.h ... faux boolean data type
// Written by John Shepherd, July 2014
//
// WARNING: never use expressions like
//   (x > 5) == TRUE  or  (x < 3) == FALSE
// use simply
//   (x > 5)          or  !(x < 3)  or (x >= 3)


#ifndef BOOL_H
#define BOOL_H

typedef unsigned char Bool;

#define FALSE 0
#define TRUE  1

#endif
