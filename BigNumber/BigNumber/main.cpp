#include "BigInt.h"

int main()
{
	Integer a("-5");
	Integer b(5);

	(a-b).print();
	b.print();
	return 0;
}