#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "grammarhelper.h"

#define E 1
#define E_ 2
#define T 3
#define T_ 4
#define F 5
#define brop 6
#define idd 7
#define plus 8
#define star 9
#define dollar 10
#define brcl 11
#define eps 12

Rule createFirsts();
Rule createFollow();
