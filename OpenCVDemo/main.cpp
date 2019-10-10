#include "opencvDemo.h"
int main()
{
	string img;
	for (int i=1;i<7;++i)
	{
		img = "D:/work/testOpenCV/OpenCVDemo/blur/";
		img.append(to_string(i)).append(".jpg");
		Mat blurImg1 = imread(img);
		if (blurImg1.empty())
		{
			cout << "Image can't open." << endl;
			waitKey(0);
			return -1;
		}
		OpenCVDemo opencvDemo;

		//////////3--transLookup
		Mat transLookupOut1, imgChannel[3];
		split(blurImg1, imgChannel);
		for (int i = 0; i < 3; ++i)
		{
			imgChannel[i] = opencvDemo.transLookup(imgChannel[i], 100);
		}
		merge(imgChannel, 3, transLookupOut1);
		//string imgOut = "D:/work/testOpenCV/OpenCVDemo/blur/output/";
		//imgOut.append(to_string(i)).append("-transLookup100.jpg");
		//imwrite(imgOut, transLookupOut1);
		
		////////1--filter-sharpen-media
		//Mat bilateralOut1 = opencvDemo.bilateral(transLookupOut1);
		//Mat laplacianOut1 = opencvDemo.laplacianSharpen(bilateralOut1);
		//Mat medianOut1 = opencvDemo.medianFilter(laplacianOut1);
		//string imgOut = "D:/work/testOpenCV/OpenCVDemo/blur/output/";
		//imgOut.append(to_string(i)).append("-transLookup-filter-sharpen-median.jpg");
		//imwrite(imgOut, medianOut1);

		////////2--filter-contrast
		Mat bilateralOut1 = opencvDemo.bilateral(transLookupOut1);
		Mat contrastOut1 = opencvDemo.enhanceContrast(bilateralOut1);
		string imgOut = "D:/work/testOpenCV/OpenCVDemo/blur/output/";
		imgOut.append(to_string(i)).append("-transLookup-filter-contrast.jpg");
		imwrite(imgOut, contrastOut1);
	}
	return 0;
}