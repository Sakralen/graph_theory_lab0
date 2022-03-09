#pragma once

#include <string>
using std::string;

class MyBitset {
	int depth;
	string set;
	int num;
public:
	MyBitset(int depth, string s);
	MyBitset(int depth, int num);
	string ToString() const;
	int ToInt() const;
};

