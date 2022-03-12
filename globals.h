#ifndef GLOBALS_H
#define GLOBALS_H

//conditional translation

//include
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <bitset> //Для удобного представления в двоичном виде
#include <filesystem>
#include <algorithm>
//#include <regex>

//define
#define SYMB_CNT 25				//Длина заданного алфавита
#define SOURCE_FILE_SIZE 10000		//Требуемая длина файла
#define LZW_DEPTH 13				//Разрядность для кодов LZW
									//Для заданных параметров получается ~5000 кодов -> 13 бит 
#define RLE_DEPTH 8				//Разрядность для количества повторений в RLE
									//Худший случай -- повторение одного символа 10000 раз -> 14 бит					 
//#define LZW_DEPTH_BYTES 2


#define SOURCE_FILE_NAME "source.txt"				//Название формируемого файла-"исходника"
#define ENCODED_LZW_FILE_NAME "lzw_encoded.txt"		//Название закодированного LZW файла
#define DECODED_LZW_FILE_NAME "lzw_decoded.txt"		//Название декодированного LZW файла
#define ENCODED_RLE_FILE_NAME "rle_encoded.txt"		//Название закодированного LZW файла
#define DECODED_RLEFILE_NAME "rle_decoded.txt"		//Название декодированного LZW файла

#define stop __asm nop

//using
using std::ofstream;
using std::ifstream;
using std::map;
using std::string;
using std::bitset;
//using std::ios;
using std::cout;

//typedef
typedef short curtype;

//constants
const string kSymbStr = "аыибксАЫИБКС0123456789 ).";
//const string kSymbStr = "abc";

//enums
enum class Sequence{
	kRepeating,
	kDifferent
};


//global variables
extern map<char, float> mapSymbPrice;		//Словарь символов и цен кодирования
extern map<string, curtype> mapLzwComp;		//Словарь символов/последовательностей и их кодов для сжатия
extern map<curtype, string> mapLzwDecomp;		//Словарь кодов и их символов/последовательностей для распаковки
extern map<curtype, string> mapRle;

//functions
void FillFile();			//Заполняет файл случайным образом
void FillMap();				//Формирует словарь символов и цен кодирования
void CalcPrice();			//Вычисляет цену кодирования
void InitMapLzwComp();			//Инициализирует словарь для сжатия для LZW
void InitMapLzwDecomp();
//string Int2Bin(curtype num);	//Формирует строковое представление
							//двоичного вида десятичного числа заданной разрядности LZW_DEPTH
//string Int2Bin_dynamic(curtype num); //модификация с динамической длиной слова
int CountBits(int num);
void CompressLzw();			//Производит сжатие по алгоритму LZW
void DecompressLzw();		//Производит распаковку по алгоритму LZW
int GetFileSize_cpp17(string name);		//Вычисляет длину файла !!! Только C++17 и выше (?) !!!
//int GetFileSize_lazy(const char* name);
float CalcCompressionRatio(const char* name);	//Вычисляет коэф. сжатия
bool IsFilesEqual(const string f1, const string f2);
void ComressRle();

void EncodeRepSeq(char letter, int count, ofstream& ofs);
void EncodeDiffSeq(int startPos, int count, ifstream& ifs, ofstream& ofs);

#endif // !GLOBALS_H
