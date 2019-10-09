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
	void smartWindows(Mat img);
	void imgFilter(Mat img);
	void edgeDetect(Mat img);
	void imgEnhance(Mat img);
	Mat sharpen(Mat img);
	void waitDestroy();
private:
	Mat imgLena;
	Mat imgLost;
};

class Histogram {
public:
	Histogram();
	~Histogram() {};
	Mat getHistogram(const Mat &image);
	Mat getHistogramImage(const Mat &image, int zoom);
	Mat getImageOfHistogram(const Mat &hist, int zoom);
private:
	int histSize[1];
	float hranges[2];
	const float* ranges[1];
	int channels[1];
};

void OpenCVDemo::smartWindows(Mat img)
{
	namedWindow("createWindow", 1);
	imshow("createWindow", img);
	moveWindow("createWindow", 30, 30);
	waitKey(0);
	destroyWindow("createWindow");
	//保存质量100的jpg文件
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);  //选择jpeg
	compression_params.push_back(100); //设置图片质量
	string imgSavePath = "D:/outfile.jpg";
	imwrite(imgSavePath, img, compression_params);
}

void OpenCVDemo::imgFilter(Mat img)
{
	Mat blurOut, GaussianOut, medianOut, bilateralOut;
	double sigmaX = 10.0;
	double sigmaY = 10.0;
	//1--均值滤波
	blur(img, blurOut, Size(3, 3));
	//2--高斯滤波
	GaussianBlur(img, GaussianOut, Size(3, 5), sigmaX, sigmaY);
	//3--中值滤波
	medianBlur(img, medianOut, 3);
	//4--双边滤波
	bilateralFilter(img, bilateralOut, 10, 10 * 2, 10 / 2);
	imshow("Lena", img);
	imshow("blur-Lena", blurOut);
	imshow("Gaussian-Lena", img);
	imshow("median-Lena", medianOut);
	imshow("bilateral-Lena", bilateralOut);
	waitDestroy();
}

void OpenCVDemo::edgeDetect(Mat img)
{
	Mat imgGray, sobelOut, absSobelOut, scharrOut, absScharrOut, laplacianOut, cannyOut;
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	//1--Sobel算子
	Sobel(imgGray, sobelOut, CV_16U, 1, 1, 3, 3);
	convertScaleAbs(sobelOut, absSobelOut);
	//2--Scharr算子
	Scharr(imgGray, scharrOut, CV_16U, 0, 1);
	convertScaleAbs(scharrOut, absScharrOut);
	//3--Laplacian算子
	Laplacian(img, laplacianOut, 8, 1, 3);
	//4--Canny算子，需先灰度化
	Canny(imgGray, cannyOut, 80, 240);
	imshow("Sobel-lena", absSobelOut);
	imshow("Scharr-lena", absScharrOut);
	imshow("Laplacian-lena", laplacianOut);
	imshow("Canny-lena", cannyOut);
	waitDestroy();
}

void OpenCVDemo::imgEnhance(Mat img)
{
	Mat linearEnhance, histEnhance, nearestInter, linearInter, areaInter, cubicInter, lanczos4Inter, sharpenEnhance;
	Histogram histogram;
	//1--线性变换
	convertScaleAbs(img, linearEnhance, 1.5, -10);
	//2--直方图均衡化
	Mat imgChannel[3];
	split(img, imgChannel);
	for (int i = 0; i < 3; ++i)
		equalizeHist(imgChannel[i], imgChannel[i]);
	merge(imgChannel, 3, histEnhance);
	//3--插值运算
	resize(img, nearestInter, img.size(), 0, 0, INTER_NEAREST);
	resize(img, linearInter, img.size(), 0, 0, INTER_LINEAR);
	resize(img, areaInter, img.size(), 0, 0, INTER_AREA);
	resize(img, cubicInter, img.size(), 0, 0, INTER_CUBIC);
	resize(img, lanczos4Inter, img.size(), 0, 0, INTER_LANCZOS4);
	//4--锐化
	sharpenEnhance = sharpen(img);
	
	imshow("LinearEnhance-lena", linearEnhance);
	imshow("Histogram-LinearEnhance-lena", histogram.getHistogramImage(linearEnhance, 1));
	imshow("HistEnhance-lena", histEnhance);
	imshow("Histogram-HistEnhance-lena", histogram.getHistogramImage(histEnhance, 1));
	imshow("Sharpen-lena", sharpenEnhance);
	imshow("Sharpen-HistEnhance-lena", histogram.getHistogramImage(sharpenEnhance, 1));

	waitDestroy();
	imshow("NearestInter-lena", nearestInter);
	imshow("LinearInter-lena", linearInter);
	imshow("AreaInter-lena", areaInter);
	imshow("CubicInter-lena", cubicInter);
	imshow("Lanczos4Inter-lena", lanczos4Inter);
	waitDestroy();
}

Mat OpenCVDemo::sharpen(Mat img)
{
	Mat laplacian;
	Mat imgChannel[3];
	split(img, imgChannel);
	for (int i = 0; i < 3; ++i)
		Laplacian(imgChannel[i], imgChannel[i], 8, 1, 3);
	merge(imgChannel, 3, laplacian);
	
	return img - laplacian;
}

void OpenCVDemo::waitDestroy()
{
	waitKey(0);
	destroyAllWindows();
}

Histogram::Histogram()
{
	histSize[0] = 256;
	hranges[0] = 0.0;
	hranges[1] = 256.0;
	ranges[0] = hranges;
	channels[0] = 0;
}

Mat Histogram::getHistogram(const Mat &image)
{
	Mat hist;
	Histogram hist1;
	//计算直方图
	calcHist(&image, 1, hist1.channels, Mat(), hist, 1, hist1.histSize, hist1.ranges);
	return hist;
}

Mat Histogram::getHistogramImage(const Mat &image, int zoom = 1)
{
	Mat hist = getHistogram(image);
	return getImageOfHistogram(hist, zoom);
}

Mat Histogram::getImageOfHistogram(const Mat &hist, int zoom = 1)
{
	//取得最大值和最小值
	double maxVal = 0;
	double minVal = 0;
	minMaxLoc(hist, &minVal, &maxVal, 0, 0);
	int histSize = hist.rows;
	Mat histImage(histSize*zoom, histSize*zoom, CV_8U, Scalar(255));
	//运算完之后如果结果为负->0;超出255->255
	int hpt = static_cast<int>(0.9*histSize);
	//画垂直线
	for (int h = 0; h < histSize; h++) {
		float binVal = hist.at<float>(h);
		if (binVal>0)
		{
			int intensity = static_cast<int>(binVal*hpt / maxVal);
			line(histImage, Point(h*zoom, histSize*zoom), Point(h*zoom, (histSize - intensity)*zoom), Scalar(0), zoom);
		}
	}
	return histImage;
}