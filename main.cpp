#include "globals.h"
#include "MyBitset.h"

map<char, float> mapSymbPrice;
map<string, curtype> mapLzwComp;
map<curtype, string> mapLzwDecomp;
//map<curtype, string> mapRle;

void main() {
	FillFile();
	CompressLzw();
	DecompressLzw();
	cout << IsFilesEqual(SOURCE_FILE_NAME, DECODED_LZW_FILE_NAME) << '\n';
	printf("%.2f\n", CalcCompressionRatio(ENCODED_LZW_FILE_NAME));
	ComressRLE();
	//cout << bitset<8>('A').to_string();
	stop
}