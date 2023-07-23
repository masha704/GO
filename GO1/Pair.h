#pragma once
class Pair
{
public:
	int firts = 0;
	int second = 0;
	Pair() {
		firts = 0;
		second = 0;
	}
	Pair(const Pair& another_Pair)
	{
		firts = another_Pair.firts;
		second = another_Pair.second;
	}
	Pair(int _first, int _second)
	{
		firts = _first;
		second = _second;
	}
};
