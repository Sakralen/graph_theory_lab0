#include "globals.h"

map<char, float> mapSymbPrice;
map<string, curtype> mapLzwComp;
map<curtype, string> mapLzwDecomp;

void main() {
	FillFile();
	CompressLzw();
	DecompressLzw();
	//printf("%.2f\n", CalcCompressionRatio(ENCODED_LZW_FILE_NAME));
	stop
}