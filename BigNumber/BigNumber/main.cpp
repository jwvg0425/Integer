#include "Integer.h"

int main()
{
	Integer a = Integer("239841029834710293874");
	Integer b = Integer("735982342");

	(b*a).print();
	(b*(-a)).print();
	return 0;
}