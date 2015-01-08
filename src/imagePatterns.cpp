/**
 * @file imagePatterns.cpp
 * @author Kent Hansen <kenthansen1@gmail.com>
 * @date 8 Jan 2015
 * @brief Generation of image patterns that can be used for structured light applications.
 *
 * 	Usage: ./imagePatterns bitWidth
 *
 * For more information, see: http://www.github.com/tckent/largegap-graycode
 */

#include "LargeGapGrayCode.h"
#include <opencv2/opencv.hpp>

const int maxBitWidth = 10;
const int imgWidth = pow(2, maxBitWidth);
const int imgHeight = 500;

void createImagePatterns(int bitWidth);

int main(int argc,char *argv[])
{
	if(argc != 2) {
		std::cout << "Usage: ./imagePatterns bitWidth" << std::endl;
		return -1;
	}
	int bitWidth = atoi(argv[1]);

	if(bitWidth > 0 && bitWidth <= maxBitWidth) {
		createImagePatterns(bitWidth);
	}
	return 0;
}


void createImagePatterns(int bitWidth)
{
	LargeGapGrayCode lggc;
	std::vector<std::bitset<20> > binaryCode = lggc.getBinaryCode(bitWidth);

	int stripeWidth = imgWidth/pow(2,bitWidth);
	cv::Mat image = cv::Mat::zeros(imgHeight, imgWidth, CV_8U);
	
	for(int i = 0; i < bitWidth; ++i) {
		for(int j = 0; j < pow(2, bitWidth); ++j) {
			if(binaryCode[j][i]) {
				for(int l = 0; l < stripeWidth; ++l) {
					for(int k = 0; k < imgHeight/bitWidth; k++) {
						image.at<uchar>(k+i*imgHeight/bitWidth, stripeWidth*j + l) = 255;
					}
				}
			}
		}
	}

	std::stringstream windowTitle;
	windowTitle << "Large-Gap Gray code: All " << bitWidth << " bits";
	cv::imshow(windowTitle.str().c_str() , image);
	cv::waitKey(0);

	for(int i = 0; i < bitWidth; ++i) {
		image = cv::Mat::zeros(imgHeight, imgWidth, CV_8U);
		for(int j = 0; j < pow(2, bitWidth); ++j) {
			if(binaryCode[j][i]) {
				for(int l = 0; l < stripeWidth; ++l) {
					for(int k = 0; k < imgHeight; k++) {
						image.at<uchar>(k, stripeWidth*j + l) = 255;
					}
				}
			}
		}
		windowTitle.str("");
		windowTitle << "Large-Gap Gray code: Bit " << i;
		cv::imshow(windowTitle.str().c_str(), image);
		cv::waitKey(0);
	}
}
