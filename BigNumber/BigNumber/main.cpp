#include "Integer.h"

int main()
{
	Integer a = Integer("10737418240");

	(a >> 31).print();
	return 0;
}