#include "MyBitset.h"

MyBitset::MyBitset(int d, string s) : depth(d), set(s), num() {
	for (int i = 0; i < depth; i++) {
		if (set[depth - 1 - i] == '1') {
			num |= 1 << i; 
		}
		else { 
			num |= 0 << i; 
		}	
	}
}

MyBitset::MyBitset(int d, int n) : depth(d), num(n), set()  {
	set.resize(depth);
	for (int i = 0; i < depth; i++) {
		if (n % 2) {
			set[depth - 1 - i] = '1';
		}
		else {
			set[depth - 1 - i] = '0';
		}
		n = n >> 1;
	}
}

string MyBitset::ToString() const {
	return set;
}

int MyBitset::ToInt() const {
	return num;
}
