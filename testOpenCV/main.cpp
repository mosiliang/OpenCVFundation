#include "testOpenCV.h"
int main(int argc, char* argv[])
{
	string imgPath;
	//1--双右斜线
	//imgPath = "D:\\work\\testOpenCV\\lost.jpg";
	//2--双左斜线
	//imgPath = "D://work//testOpenCV//lost.jpg";
	//3--单左斜线
	//imgPath = "D:/work/testOpenCV/lost.jpg";
	//4--命令行参数：工程——属性——配置属性——调试——命令行参数
	//imgPath = argv[1];
	//5--相对路径（与工程文件在一个文件夹）
	//imgPath = "lost.jpg";
	Mat imgLost = imread("lost.jpg");
	Mat imgLena = imread("lena.jpg");
	if (imgLost.empty() || imgLena.empty())
	{
		cout << "Image can not read." << endl;
		return -1;
	}

	OpenCVDemo openCVDemo;
	openCVDemo.smartWindows(imgLost);
	//滤波
	openCVDemo.imgFilter(imgLena);
	//边缘检测
	openCVDemo.edgeDetect(imgLena);
	//直方图
	Histogram histogram;
	imshow("lena", imgLena);
	imshow("Histogram-lena", histogram.getHistogramImage(imgLena, 1));
	//图像增强
	openCVDemo.imgEnhance(imgLena);
	return 0;
}
