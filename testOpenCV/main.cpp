#include "testOpenCV.h"
int main(int argc, char* argv[])
{
	string imgPath;
	//1--˫��б��
	//imgPath = "D:\\work\\testOpenCV\\lost.jpg";
	//2--˫��б��
	//imgPath = "D://work//testOpenCV//lost.jpg";
	//3--����б��
	//imgPath = "D:/work/testOpenCV/lost.jpg";
	//4--�����в��������̡������ԡ����������ԡ������ԡ��������в���
	//imgPath = argv[1];
	//5--���·�����빤���ļ���һ���ļ��У�
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
	//�˲�
	openCVDemo.imgFilter(imgLena);
	//��Ե���
	openCVDemo.edgeDetect(imgLena);
	//ֱ��ͼ
	Histogram histogram;
	imshow("lena", imgLena);
	imshow("Histogram-lena", histogram.getHistogramImage(imgLena, 1));
	//ͼ����ǿ
	openCVDemo.imgEnhance(imgLena);
	return 0;
}
