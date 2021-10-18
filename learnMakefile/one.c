#include <stdio.h>
#include "first.h"
//#include "two.c"

int first(int n); 
int second(int n);
int third(int n);
void twofunc();
void threefunc();

int main(int argc, char const *argv[])
{
	printf("Here is one.c !!\n");
	int a = 10;
	first(a);
	twofunc();
	second(a);
	threefunc();
	third(11);
	return 0;
}