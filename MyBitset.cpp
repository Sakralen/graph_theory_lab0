#include "MyBitset.h"

MyBitset::MyBitset(int d, string s) : depth(d), set(s), num() {
	for (int i = 0; i < depth; i++) {
		num |= std::stoi(string(1, set[depth - 1 - i])) << i;
	}
}

MyBitset::MyBitset(int d, int n) : depth(d), num(n), set()  {

}

string MyBitset::ToString() const {
	return set;
}

int MyBitset::ToInt() const {
	return num;
}
