/**
 * @file LargeGapGrayCode.cpp
 * @author Kent Hansen <kenthansen1@gmail.com>
 * @date 8 Jan 2015
 * @brief File for constructing Large-Gap Gray codes (LGGC)
 *
 * LGGC is a special type of Gray code with the additional
 * property that it contains large run lengths.
 * 
 * For more information about LGGC construction, see:
 * http://www.github.com/tckent/largegap-graycode
 */

#include "LargeGapGrayCode.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <math.h>

const int maxBitWidth = 20;

LargeGapGrayCode::LargeGapGrayCode() {
	m_transitionSequences.resize(maxBitWidth);
	m_creationMethod.resize(maxBitWidth);

	m_transitionSequences[0] = {0, 0};
	m_creationMethod[0] = "by hand";

	m_transitionSequences[1] = {0, 1, 0, 1};
	m_creationMethod[1] = "by hand";

	m_transitionSequences[2] = {0, 1, 0, 2, 0, 1, 0, 2};
	m_creationMethod[2] = "by hand";

	m_transitionSequences[3] = {0, 1, 2, 3, 2, 1, 0, 2, 0, 3, 0, 1, 3, 2, 3, 1};
	m_creationMethod[3] = "by hand";

	m_transitionSequences[5] = {0, 1, 2, 3, 4, 5, 0, 2, 4, 1, 3, 2, 0, 5, 4, 2, 3, 1, 4, 0, 2, 5, 3 ,4, 2, 1, 0, 4, 3 ,5 ,2, 4, 0, 1, 2, 3, 4, 5, 0, 2, 4, 1, 3, 2, 0, 5, 4, 2, 3, 1, 4, 0, 2, 5, 3 ,4, 2, 1, 0, 4, 3 ,5 ,2, 4};
	m_creationMethod[5] = "backtrack";

	createCodeFromTheorem2(2, 2, 1, 1, 1);
	createCodeFromTheorem1(5, 2, 3, 1);
	createCodeFromTheorem1(6, 2, 3, 1);
	createCodeFromTheorem1(7, 2, 3, 1);
	createCodeFromTheorem1(5, 5, 17, 15);
	createCodeFromTheorem1(9, 2, 3, 1);
	createCodeFromTheorem1(7, 5, 17, 15);
	createCodeFromTheorem1(8, 5, 19, 13);
	createCodeFromTheorem1(7, 7, 65, 63);
	createCodeFromTheorem1(10, 5, 21, 11);
	createCodeFromTheorem1(11, 5, 21, 11);
	createCodeFromTheorem1(10, 7, 73, 55);
	createCodeFromTheorem1(11, 7, 75, 53);
	createCodeFromTheorem1(14, 5, 23, 9);
	createCodeFromTheorem1(10, 10, 513, 511);
}

LargeGapGrayCode::~LargeGapGrayCode() {
}


std::vector<int> LargeGapGrayCode::getTransitionSequence(int bitWidth)
{
	if(bitWidth <= maxBitWidth) {
		return m_transitionSequences[bitWidth-1];
	}
	else {
		std::vector<int> empty;
		return empty;
	}
}

std::vector<std::bitset<20> > LargeGapGrayCode::getBinaryCode(int bitWidth)
{
	std::vector<std::bitset<20> > binaryCode;

	std::vector<int> ts = getTransitionSequence(bitWidth);
	std::bitset<20> bs(0);

	for(int i = 0; i < pow(2, bitWidth); i++)
	{
		binaryCode.push_back(bs);
		bs.flip(ts[i]);
	}

	return binaryCode;
}


void LargeGapGrayCode::printAllStatistics()
{
	printStatisticsHeader();
	for(int i = 3; i <= maxBitWidth; ++i) {
		printStatistics(i);
	}
}


void LargeGapGrayCode::printStatisticsHeader()
{
	std::cout 	<< std::setw(5) << "n"
			<< std::setw(12) << "Method"
			<< std::setw(12) << "MinGap"
			<< std::setw(12) << "MaxGap"
			<< std::setw(12) << "MinCount"
			<< std::setw(12) << "MaxCount"
			<< std::setw(14) << "GapVariance" << std::endl;
	std::cout << "------------------------------------------------------------------------------------" << std::endl;
}


void LargeGapGrayCode::printStatistics(int bitWidth)
{
	std::map<int, int> runLengths = computeRunLengths(bitWidth);
	int minGap, minCount, maxGap, maxCount;
	computeMinGap(runLengths, minGap, minCount);
	computeMaxGap(runLengths, maxGap, maxCount);
	double gapVariance = computeGapVariance(runLengths);
	std::cout 	<< std::setw(5) << bitWidth
			<< std::setw(12) << m_creationMethod[bitWidth-1]
			<< std::setw(12) << minGap
			<< std::setw(12) << maxGap
			<< std::setw(12) << minCount
			<< std::setw(12) << maxCount
			<< std::setw(14) << gapVariance << std::endl;
}


void LargeGapGrayCode::createCodeFromTheorem1(int n, int m, int s, int t)
{
	if(n >= m && m >= 1 && isOddPositive(s) && isOddPositive(t) && (s+t) == pow(2,m) && (n+m <= maxBitWidth)) {
		std::vector<char> P = createPVector(s, t);
		std::vector<char> Z = multiCopyVector(P, pow(2, n));
		std::vector<int> t = createTransitionSequenceTheorem1(n, m, Z);
		m_transitionSequences[n+m-1] = t;
		std::stringstream ss;
		ss << "(" << n << " + " << m << ")";
		m_creationMethod[n+m-1] = ss.str();
	}
	else {
		std::cout << "Constraints for Theorem 1 are not satisfied." << std::endl;
	}
}


void LargeGapGrayCode::createCodeFromTheorem2(int n, int m, int r, int s, int t)
{
	if(n >= m && m >= r && r >= 1 && isOddPositive(s) && isOddPositive(t) && (s+t) == pow(2,r) && (n+m+r <= maxBitWidth)) {
		std::vector<char> P = createPVector(s, t);
		std::vector<char> Q = multiCopyVector(P, pow(2, n));
		replaceLastBWithC(Q);
		std::vector<char> Z = multiCopyVector(Q, pow(2, m));
		std::vector<int> t = createTransitionSequenceTheorem2(n, m, r, Z);
		m_transitionSequences[n+m+r-1] = t;
		std::stringstream ss;
		ss << "(" << n << " + " << m << " + " << r << ")";
		m_creationMethod[n+m+r-1] = ss.str();
	}
	else {
		std::cout << "Constraints for Theorem 2 are not satisfied." << std::endl;
	}
}


std::map<int, int> LargeGapGrayCode::computeRunLengths(int bitWidth)
{
	std::vector<int> t = m_transitionSequences[bitWidth-1];
	std::vector<int> transitionLastSeen(bitWidth, -1);

	std::map<int, int> numRunLengths;

	for(int runThrough = 1; runThrough <= 2; ++runThrough) {
		for(int i = 0; i < t.size(); ++i) {
			if(transitionLastSeen[t[i]] == -1) {
				transitionLastSeen[t[i]] = i;
			}
			else {
				int runLength = runThrough*t.size()+i-transitionLastSeen[t[i]];
				transitionLastSeen[t[i]] = runThrough*t.size()+i;

				if(runThrough == 2) {
					std::map<int, int>::iterator it = numRunLengths.find(runLength);
					if (it != numRunLengths.end()) {
					    it->second += 1;
					}
					else {
						numRunLengths.insert(std::make_pair(runLength, 1));
					}
				}
			}
		}
	}

	return numRunLengths;
}


void LargeGapGrayCode::computeMinGap(const std::map<int, int>& runLengths, int& minGap, int& minCount)
{
	minGap = 999;

	for(std::map<int, int>::const_iterator it = runLengths.begin(); it != runLengths.end(); ++it) {
		if(it->first < minGap) {
			minGap = it->first;
			minCount = it->second;
		}
	}
}


void LargeGapGrayCode::computeMaxGap(const std::map<int, int>& runLengths, int& maxGap, int& maxCount)
{
	maxGap = 0;

	for(std::map<int, int>::const_iterator it = runLengths.begin(); it != runLengths.end(); ++it) {
		if(it->first > maxGap) {
			maxGap = it->first;
			maxCount = it->second;
		}
	}
}


double LargeGapGrayCode::computeGapVariance(const std::map<int, int>& runLengths)
{
	int sum = 0;
	int runs = 0;

	for(std::map<int, int>::const_iterator it = runLengths.begin(); it != runLengths.end(); ++it) {
		sum += it->first * it->second;
		runs += it->second;
	}

	double mean = (double)sum/runs;

	int squaredDiff = 0;
	for(std::map<int, int>::const_iterator it = runLengths.begin(); it != runLengths.end(); ++it) {
		squaredDiff += (it->first-mean)*(it->first-mean) * it->second;
	}

	double variance = (double)squaredDiff/runs;

	return variance;
}



bool LargeGapGrayCode::isOddPositive(int value)
{
	bool ret = false;
	if(value > 0 && value%2 == 1) {
		ret = true;
	}
	return ret;
}


std::vector<char> LargeGapGrayCode::createPVector(int s, int t)
{
	double startRatio = (double) t/s;
	int bUsed = 0;
	int aUsed = 0;

	std::vector<char> tmp(s+t);
	for(int i = 0; i < tmp.size(); ++i) {
		if((double)bUsed/(aUsed+1) >= startRatio) {
			tmp[i] = 'a';
			aUsed++;
		}
		else {
			tmp[i] = 'b';
			bUsed++;
		}
	}
	return tmp;
}


std::vector<char> LargeGapGrayCode::multiCopyVector(const std::vector<char>& oldVector, int numCopies)
{
	std::vector<char> newVector(oldVector.size()*numCopies);
	for(int i = 0; i < numCopies; ++i) {
		for(int j = 0; j < oldVector.size(); ++j) {
			newVector[i*oldVector.size() + j] = oldVector[j];
		}
	}
	return newVector;
}


std::vector<int> LargeGapGrayCode::createTransitionSequenceTheorem1(int n, int m, const std::vector<char>& Z)
{
	std::vector<int> tmp(Z.size());

	std::vector<int> A = m_transitionSequences[n-1];
	std::vector<int> B = m_transitionSequences[m-1];
	int idxA = 0;
	int idxB = 0;

	for(int i = 0; i < Z.size(); i++)
    	{
		if(Z[i] == 'a') {
			tmp[i] = A[idxA++ % A.size()];
		}
		else if(Z[i] == 'b') {
			tmp[i] = B[idxB++ % B.size()] + n;
		}
    	}
	return tmp;
}


std::vector<int> LargeGapGrayCode::createTransitionSequenceTheorem2(int n, int m, int r, const std::vector<char>& Z)
{
	std::vector<int> tmp(Z.size());

	std::vector<int> A = m_transitionSequences[n-1];
	std::vector<int> B = m_transitionSequences[m-1];
	std::vector<int> C = m_transitionSequences[r-1];
	int idxA = 0;
	int idxB = 0;
	int idxC = 0;

	for(int i = 0; i < Z.size(); i++)
    	{
		if(Z[i] == 'a') {
			tmp[i] = A[idxA++ % A.size()];
		}
		else if(Z[i] == 'b') {
			tmp[i] = B[idxB++ % B.size()] + n;
		}
		else if(Z[i] == 'c') {
			tmp[i] = C[idxC++ % C.size()] + n + m;
		}
    	}
	return tmp;
}

void LargeGapGrayCode::replaceLastBWithC(std::vector<char>& v)
{
	for(int k = v.size()-1; k >= 0; --k) {
		if(v[k] == 'b') {
			v[k] = 'c';
			break;
		}
	}
}
