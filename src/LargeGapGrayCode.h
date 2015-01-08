/**
 * @file LargeGapGrayCode.h
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

#ifndef LARGEGAPGRAYCODE_H_
#define LARGEGAPGRAYCODE_H_

#include <vector>
#include <bitset>
#include <map>

class LargeGapGrayCode {
public:
	LargeGapGrayCode();
	virtual ~LargeGapGrayCode();

	std::vector<int> getTransitionSequence(int bitWidth);
	std::vector<std::bitset<20> > getBinaryCode(int bitWidth);

	void printAllStatistics();
	void printStatisticsHeader();
	void printStatistics(int bitWidth);

	void createCodeFromTheorem1(int n, int m, int s, int t);
	void createCodeFromTheorem2(int n, int m, int r, int s, int t);

private:
	bool isOddPositive(int value);
	std::vector<char> createPVector(int s, int t);
	std::vector<char> multiCopyVector(const std::vector<char>& oldVector, int numCopies);
	void replaceLastBWithC(std::vector<char>& v);
	std::vector<int> createTransitionSequenceTheorem1(int n, int m, const std::vector<char>& Z);
	std::vector<int> createTransitionSequenceTheorem2(int n, int m, int r, const std::vector<char>& Z);

	std::map<int, int> computeRunLengths(int bitWidth);
	double computeGapVariance(const std::map<int, int>& runLengths);
	void computeMinGap(const std::map<int, int>& runLengths, int& minGap, int& minCount);
	void computeMaxGap(const std::map<int, int>& runLengths, int& maxGap, int& maxCount);

	std::vector<std::vector<int> > m_transitionSequences;
	std::vector<std::string> m_creationMethod;
};

#endif /* LARGEGAPGRAYCODE_H_ */
