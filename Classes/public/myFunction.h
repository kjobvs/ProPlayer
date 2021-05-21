#pragma once
#include <list>
class myFunction
{
private:
	myFunction();
	~myFunction();
public:
	static int random(int lowValue,int topValue);


	template<typename T>
	static int getPosition(std::list<T>* data, T pos)
	{
		if (data->size() == 0)
		{
			return -1;
		}
		int count = 0;
		for (auto it = data->begin(); it != data->end(); it++)
		{
			if (*it == *pos)
			{
				return count;
			}
			count++;
		}
		return -1;
	}
};

