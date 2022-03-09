#ifndef GLOBALS_H
#define GLOBALS_H

//conditional translation

//include
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <bitset> //��� �������� ������������� � �������� ����
#include <filesystem>
#include <algorithm>

//define
#define SYMB_CNT 25				//����� ��������� ��������
#define SOURCE_FILE_SIZE 10000		//��������� ����� �����
#define LZW_DEPTH 13				//����������� ��� �����
									//��� �������� ���������� ���������� ~5000 ����� -> 13 ��� 
//#define LZW_DEPTH_BYTES 2

#define SOURCE_FILE_NAME "source.txt"				//�������� ������������ �����-"���������"
#define ENCODED_LZW_FILE_NAME "lzw_encoded.txt"		//�������� ��������������� LZW �����
#define DECODED_LZW_FILE_NAME "lzw_decoded.txt"		//�������� ��������������� LZW �����

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
static const char* kSymbStr = "������������0123456789 ).";

//global variables
extern map<char, float> mapSymbPrice;		//������� �������� � ��� �����������
extern map<string, curtype> mapLzwComp;		//������� ��������/������������������� � �� ����� ��� ������
extern map<curtype, string> mapLzwDecomp;		//������� ����� � �� ��������/������������������� ��� ����������

//functions
void FillFile();			//��������� ���� ��������� �������
void FillMap();				//��������� ������� �������� � ��� �����������
void CalcPrice();			//��������� ���� �����������
void InitMapLzwComp();			//�������������� ������� ��� ������ ��� LZW
void InitMapLzwDecomp();
string Int2Bin(curtype num);	//��������� ��������� �������������
							//��������� ���� ����������� ����� �������� ����������� LZW_DEPTH
string Int2Bin_dynamic(curtype num); //����������� � ������������ ������ �����
int CountBits(int num);
void CompressLzw();			//���������� ������ �� ��������� LZW
void DecompressLzw();		//���������� ���������� �� ��������� LZW
int GetFileSize_cpp17(const char* name);		//��������� ����� ����� !!! ������ C++17 � ���� (?) !!!
//int GetFileSize_lazy(const char* name);
float CalcCompressionRatio(const char* name);	//��������� ����. ������
#endif // !GLOBALS_H
