#pragma once
#include <iostream>
#include <fstream>
#include <cv.h>
#include <core\core.hpp>
#include <highgui.h>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;
class OpenCVDemo {
public:
	OpenCVDemo() {};
	~OpenCVDemo() {};
	Mat interPolation(Mat img);
	Mat laplacianSharpen(Mat img);
	Mat bilateral(Mat img);
	Mat histEqualize(Mat img);
	Mat medianFilter(Mat img);
	Mat enhanceContrast(Mat img);
	Mat transLookup(Mat img, int threshold);
};
Mat OpenCVDemo::interPolation(Mat img)
{
	Mat interOut;
	resize(img, interOut, Size(), 2, 2, INTER_LANCZOS4);
	return interOut;
}
Mat OpenCVDemo::bilateral(Mat img)
{
	Mat FilterOut;
	bilateralFilter(img, FilterOut, 10, 10 * 2, 100);
	return FilterOut;
}
Mat OpenCVDemo::histEqualize(Mat img)
{
	Mat imgChannel[3], histOut;
	split(img, imgChannel);
	for (int i = 0; i < 3; ++i)
		equalizeHist(imgChannel[i], imgChannel[i]);
	merge(imgChannel, 3, histOut);

	return histOut;
}
Mat OpenCVDemo::laplacianSharpen(Mat img)
{
	Mat laplacianFilter, imgChannel[3];
	split(img, imgChannel);
	for (int i = 0; i < 3; ++i)
	{
		Laplacian(imgChannel[i], imgChannel[i], 8, 1, 10);
	}
	merge(imgChannel, 3, laplacianFilter);
	return img - laplacianFilter;
}
Mat OpenCVDemo::medianFilter(Mat img)
{
	Mat medianOut;
	medianBlur(img, medianOut, 3);
	return medianOut;
}
Mat OpenCVDemo::enhanceContrast(Mat img)
{
	Mat contrastOut;
	Mat kernal = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(img, contrastOut, img.depth(), kernal);
	return contrastOut;
}
Mat OpenCVDemo::transLookup(Mat img, int threshold)
{
	//第一步 计算灰度图像的直方图
	const int channels[1] = { 0 };
	const int histSize[1] = { 256 };
	float hranges[2] = { 0, 255 };
	const float *ranges[1] = { hranges };
	MatND hist;
	calcHist(&img, 1, channels, Mat(), hist,
		1, histSize, ranges);
	//第二步 根据预设参数统计灰度级变换
	//由低到高进行查找
	int iLow = 0;
	for (; iLow < histSize[0]; iLow++)
	{
		if (hist.at<float>(iLow)>threshold)
			break;
	}
	//由高到底进行查找
	int iHigh = histSize[0] - 1;
	for (; iHigh >= 0; iHigh--)
	{
		if (hist.at<float>(iHigh) > threshold)
			break;
	}
	//第三步 建立查找表
	Mat lookUpTable(Size(1, 256), CV_8U);
	for (int i = 0; i < 256; i++)
	{
		if (i < iLow)
		{
			lookUpTable.at<uchar>(i) = 0;
		}
		else if (i>iHigh)
		{
			lookUpTable.at<uchar>(i) = 255;
		}
		else
		{
			lookUpTable.at<uchar>(i) = static_cast<uchar>(
				255.0*(i - iLow) / (iHigh - iLow + 0.5));
		}
	}

	//第四步，通过查找表进行映射变换
	Mat histTransResult;
	LUT(img, lookUpTable, histTransResult);

	return histTransResult;
}
