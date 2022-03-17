#include "globals.h"
//#include "MyBitset.h"

map<char, float> mapSymbPrice;
map<string, curtype> mapLzwComp;
map<curtype, string> mapLzwDecomp;

void main() {
	setlocale(LC_ALL, "Russian");
	FillFile();
	FillMap();
	CalcPrice();
	for (int i = 0; i < SYMB_CNT; i++)
	{
		cout << kSymbStr[i] << ": " << mapSymbPrice[kSymbStr[i]] << '\n';
	}

	CompressLzw(SOURCE_FILE_NAME);
	DecompressLzw(ENCODED_LZW_FILE_NAME);
	cout << "Проверка LZW: " << IsFilesEqual(SOURCE_FILE_NAME, DECODED_LZW_FILE_NAME) << '\n';
	printf("Коэф. сжатия: %.2f\n", CalcCompressionRatio(ENCODED_LZW_FILE_NAME));

	ComressRle(SOURCE_FILE_NAME);
	DecompressRle(ENCODED_RLE_FILE_NAME);
	cout << "Проверка RLE: " << IsFilesEqual(SOURCE_FILE_NAME, DECODED_RLE_FILE_NAME) << '\n';
	printf("Коэф.сжатия: %.2f\n", CalcCompressionRatio(ENCODED_RLE_FILE_NAME)) << '\n';

	DbgCheckEqual(SOURCE_FILE_NAME, DECODED_RLE_FILE_NAME);

	/*CompressLzw(SOURCE_FILE_NAME);
	ComressRle(ENCODED_LZW_FILE_NAME);
	DecompressRle(ENCODED_RLE_FILE_NAME);
	DecompressLzw(DECODED_RLE_FILE_NAME);
	cout << "Проверка LZW + RLE: " << IsFilesEqual(SOURCE_FILE_NAME, DECODED_LZW_FILE_NAME) << '\n';
	printf("Коэф. сжатия: %.2f\n", CalcCompressionRatio(ENCODED_RLE_FILE_NAME));

	ComressRle(SOURCE_FILE_NAME);
	CompressLzw(ENCODED_RLE_FILE_NAME);
	DecompressLzw(ENCODED_LZW_FILE_NAME);
	DecompressRle(DECODED_LZW_FILE_NAME);
	cout << "Проверка RLE + LZW: " << IsFilesEqual(SOURCE_FILE_NAME, DECODED_RLE_FILE_NAME) << '\n';
	printf("Коэф. сжатия: %.2f\n", CalcCompressionRatio(ENCODED_LZW_FILE_NAME));*/
	stop
}