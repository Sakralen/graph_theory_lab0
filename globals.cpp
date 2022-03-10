#include "globals.h"

#include <iostream>
#include <fstream>
//#include <ctime>
#include <random>
#include "MyBitset.h"

void FillFile() {
	//srand(time(0));
	std::mt19937 engine;		//Для 
	std::random_device device;	//вихря
	engine.seed(device());		//Мерсенна
	
	ofstream ofs(SOURCE_FILE_NAME);
	if (ofs.is_open()) {
		for (int i = 0; i < SOURCE_FILE_SIZE; i++) {
			//ofs << kSymbArr[(rand() % ARR_SYMB_CNT)];
			std::uniform_int_distribution<int> distribution(0, kSymbStr.size() - 1);
			ofs << kSymbStr[distribution(engine)];
		}
		ofs.close();
	}
	else {
		throw std::exception();
	}
}

void FillMap() {
	ifstream ifs(SOURCE_FILE_NAME);
	if (ifs.is_open()) {
		char buf;
		while (ifs >> std::noskipws >> buf) { //std::noskipws не игнорирует пробелы
			mapSymbPrice[buf]++;
		}
		ifs.close();
	}
	else {
		throw std::exception();
	}
}

void CalcPrice() {
	for (auto it = mapSymbPrice.begin(); it != mapSymbPrice.end(); ++it) {
		(*it).second /= SOURCE_FILE_SIZE;	
	}
}

void InitMapLzwComp() {
	for (curtype i = 0; i < kSymbStr.size(); i++) {
		mapLzwComp[string(1, kSymbStr[i])] = i; //Такой конструктор string для формирования 
											//единичной строки char'ов
	}
}

//string Int2Bin(curtype num) {
//	return bitset<LZW_DEPTH>(num).to_string();
//}

//const char* Int2C_String(int num) {
//	return std::to_string(num).c_str();
//}

int CountBits(int num) {
	return static_cast<int>(log(num) / log(2) + 1);
}

void CompressLzw() {
	mapLzwComp.clear();
	InitMapLzwComp();

	ifstream ifs(SOURCE_FILE_NAME);
	ofstream ofs(ENCODED_LZW_FILE_NAME/*, ios::binary*/);
	if (ifs.is_open() && ofs.is_open()) {
		char buf;
		string sequence;
		while (ifs >> std::noskipws >> buf) {
			if (mapLzwComp.find(sequence + buf) != mapLzwComp.end()) {	//Если последовательность уже есть в словаре:
				sequence += buf;								//удлиняем ее следующим символом
			}
			else {												//Если нет:
				//ofs << Int2Bin(mapLzwComp[sequence]);			//Выводим код предыдущей последовательности
				ofs << bitset<LZW_DEPTH>(mapLzwComp[sequence]).to_string();
				mapLzwComp[sequence + buf] = mapLzwComp.size();		//Добавляем новую последовательнось в словарь,
																//формируя для нее код в dec;
				sequence = buf;									//начинаем снова с последнего символа
			}
		}
		//ofs << Int2Bin(mapLzwComp[sequence]);
		ofs << bitset<LZW_DEPTH>(mapLzwComp[sequence]).to_string();
		ifs.close();
		ofs.close();
	}
	else {
		throw std::exception();
	}
}

void InitMapLzwDecomp() {
	for (curtype i = 0; i < kSymbStr.size(); i++) {
		mapLzwDecomp[i] = string(1, kSymbStr[i]); 
	}
	stop
}

void DecompressLzw() {
	mapLzwDecomp.clear();
	InitMapLzwDecomp();

	ifstream ifs(ENCODED_LZW_FILE_NAME/*, ios::binary*/);
	ofstream ofs(DECODED_LZW_FILE_NAME);
	if (ifs.is_open() && ofs.is_open()) {
		char buf;
		string sequence;	//Буффер для бинарной последовательности длиной LZW_DEPTH
		string tmpSequence;
		curtype code;
		curtype prevCode;

		for (int i = 0; i < LZW_DEPTH; i++) {
			ifs >> std::noskipws >> buf;
			sequence += buf;
		}
		code = bitset<LZW_DEPTH>(sequence).to_ulong();
		ofs << mapLzwDecomp[code];
		prevCode = code;
		sequence.clear();

		while (ifs >> std::noskipws >> buf) {
			sequence += buf;
			if (sequence.size() == LZW_DEPTH) {
				code = bitset<LZW_DEPTH>(sequence).to_ulong();
				if (mapLzwDecomp.find(code) != mapLzwDecomp.end()) {	//Если код уже есть в словаре:
					ofs << mapLzwDecomp[code];							//Выводим последовательность, соотв. этому коду
					mapLzwDecomp[mapLzwDecomp.size()] = mapLzwDecomp[prevCode] + mapLzwDecomp[code][0];	//Добавляем в словарь
																		//новую последовательность
				}
				else {	//Если кода нет:
					tmpSequence = mapLzwDecomp[prevCode] + mapLzwDecomp[prevCode][0]; //Добавили новый код
																			//= старый + новый[0]
					ofs << tmpSequence; 
					mapLzwDecomp[code] = tmpSequence;
					//mapLzwDecomp[mapLzwDecomp.size()] = tmpSequence;	//???
				}
				prevCode = code;
				sequence.clear();
			}
		}
		//output.txt << symb
		ifs.close();
		ofs.close();
	}
	else {
		throw std::exception();
	}
}

int GetFileSize_cpp17(string name) {
	return std::filesystem::file_size(name);
}

//int GetFileSize_lazy(const char* name) {
//	ifstream ifs(name);
//	if (ifs.is_open()) {
//		int size = 0;
//		while (!ifs.eof()) {
//			ifs.get();
//			size++;
//		}
//		ifs.close();
//		return --size;
//	}
//	else {
//		throw std::exception();
//	}
//}

float CalcCompressionRatio(const char* name) {
	float ratio = static_cast<float>(SOURCE_FILE_SIZE) / (GetFileSize_cpp17(name) / 8);
	//printf("%.2f\n", ratio);
	return ratio;
}

bool IsFilesEqual(const string f1Name, const string f2Name) {
	std::ifstream f1(f1Name);
	std::ifstream f2(f2Name);

	if (f1.is_open() && f2.is_open()) {
		if (GetFileSize_cpp17(f1Name) == GetFileSize_cpp17(f2Name)) {
			std::istreambuf_iterator<char> begin1(f1);
			std::istreambuf_iterator<char> begin2(f2);
			std::istreambuf_iterator<char> end;
			bool res = std::equal(begin1, end, begin2);
			f1.close();
			f2.close();
			return res;
		}
		else {
			f1.close();
			f2.close();
			return false;
		}
	}
	else {
		throw std::exception();
	}
}

void ComressRLE() {
	ifstream ifs(SOURCE_FILE_NAME);
	ofstream ofs(ENCODED_RLE_FILE_NAME);
	if (ifs.is_open() && ofs.is_open()) {
		char buf;
		char prev;
		short sameCnt = 1;
		short diffCnt = 1;
		//int max = -1;

		ifs >> std::noskipws >> prev;
		while (ifs >> std::noskipws >> buf) {
			//Рассмотреть граничный случай с EOF
			if (buf == prev) {
				if (sameCnt != 1 << (RLE_DEPTH - 1)) {
					sameCnt++;
					/*if (count > max) {
						max = count;
					}*/
				}
				else {
					if (sameCnt) {
						ofs << sameCnt << prev;
					}
					else {
						ofs << prev;
					}
					sameCnt = 1;
				}
			}
			else {
				if (sameCnt) {
					ofs << sameCnt << prev;
				}
				else {
					ofs << prev;
				}
				sameCnt = 1;
			}
			prev = buf;
		}
		if (sameCnt) {
			ofs << ++sameCnt << prev;
		}
		else {
			ofs << prev;
		}
		ifs.close();
		ofs.close();
	}
	else {
		throw std::exception();
	}
}