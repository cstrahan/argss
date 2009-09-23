#ifndef _ARGSS_ARGSSERRORH_
#define _ARGSS_ARGSSERRORH_

#include <map>
#include "SFML/Graphics.hpp"

extern unsigned long ARGSS_Error;

void Init_ARGSSError();

void Check_Kind(unsigned long o, unsigned long c);
void Check_Types2(unsigned long x, unsigned long t1, unsigned long t2);
void Check_Bool(unsigned long x);
void Check_Class(unsigned long x, unsigned long t);
void Check_Classes(unsigned long x, int argc, unsigned long *types);
void Check_Classes_N(unsigned long x, unsigned long type);

#endif
