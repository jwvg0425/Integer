#include "Integer.h"
#include <iostream>
#include <ctime>


Integer factorial(unsigned int n)
{
	if (n == 0)
		return 1;

	return factorial(n - 1)*n;
}

int main()
{
	Integer factor = factorial(300);
	Integer b;

	std::cout << factor << std::endl;
	std::cin >> b;
	std::cout << b << std::endl;
	
	return 0;
}