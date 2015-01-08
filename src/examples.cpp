/**
 * @file examples.cpp
 * @author Kent Hansen <kenthansen1@gmail.com>
 * @date 8 Jan 2015
 * @brief Example usage of Large-Gap Gray code (LGGC) class.
 *
 * 	1) Shows statistics for LGGC ranging from 3-20 bits
 * 	2) Construction of four different 16-bit codes and their statistics
 *	3) Print of constructed 7-bit code. Note the length of horizontal bit runs
 *
 * For more information, see: http://www.github.com/tckent/largegap-graycode
 */

#include <iostream>
#include <math.h>
#include "LargeGapGrayCode.h"

void printBinaryCode(const std::vector<std::bitset<20> >& code, int bitWidth);

int main() {
	LargeGapGrayCode lggc;
	std::cout << "####################################################################" << std::endl;
	std::cout << "####### 1)  Printing statistics for all Large-Gap Gray Codes #######" << std::endl;
	std::cout << "####################################################################" << std::endl << std::endl;
	lggc.printAllStatistics();

	std::cout << std::endl << std::endl;
	std::cout << "####################################################################" << std::endl;
	std::cout << "#######  2)  Printing statistics for different 16-bit codes  #######" << std::endl;
	std::cout << "####################################################################" << std::endl << std::endl;
	lggc.printStatisticsHeader();
	lggc.createCodeFromTheorem1(14, 2, 3, 1);
	lggc.printStatistics(16);
	lggc.createCodeFromTheorem1(8, 8, 129, 127);
	lggc.printStatistics(16);
	lggc.createCodeFromTheorem1(9, 7, 65, 63);
	lggc.printStatistics(16);
	lggc.createCodeFromTheorem1(11, 5, 21, 11);
	lggc.printStatistics(16);

	std::cout << std::endl << std::endl;
	std::cout << "####################################################################" << std::endl;
	std::cout << "#######       3)  Printing generated 7-bit binary code       #######" << std::endl;
	std::cout << "#######             Note: MinGap = 5 and MaxGap = 11         #######" << std::endl;
	std::cout << "####################################################################" << std::endl << std::endl;
	printBinaryCode(lggc.getBinaryCode(7), 7);

	return 0;
}


void printBinaryCode(const std::vector<std::bitset<20> >& code, int bitWidth)
{
	for(int j = 0; j < bitWidth; ++j)
	{
		for(int i = 0; i < pow(2, bitWidth); i++)
		{
		    std::cout << code[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
