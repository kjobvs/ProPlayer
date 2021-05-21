#include "CLFunction.h"

int myNumber::getMin(int _a, int _b)
{
	int result;
	_a > _b ? result =  _b : result =  _a;
	return result;
}