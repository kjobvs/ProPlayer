#include "myFunction.h"
#include <time.h>
#include <random>
using namespace std;

myFunction::myFunction()
{
}


myFunction::~myFunction()
{
}


int myFunction::random(int lowValue, int topValue)
{
	static default_random_engine random(time(NULL));
	uniform_int_distribution<int> u(lowValue, topValue);
	return u(random);
}