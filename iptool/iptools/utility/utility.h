#ifndef UTILITY_H
#define UTILITY_H

#include "../image/image.h"
#include <sstream>
#include <math.h>

class utility
{
	public:
		utility();
		virtual ~utility();
		static std::string intToString(int number);
		static int checkValue(int value);

		//Project three functions
		static void sobel(image& src, image& tgt, vector<roi>& roiList);
		static int dx(image& src, int i, int j);
		static int dy(image& src, int i, int j);

		static void colorSobel(image& src, image& tgt, vector<roi>& roiList, int threshold, const int& color);
		static int dxColor(image& src, int j, int i, const int& color);
		static int dyColor(image& src, int j, int i, const int& color);

		static void direction(image& src, image& tgt, vector<roi>& roiList, int threshold, double direction);
		static void oredImages(image& src, image& red, image& green, image& blue, image& tgt, vector<roi>& roiList);

		static void binarize(image& src, vector<roi>& roiList, int threshold);
		static void RGBtoHSI(double r, double g, double b, double& h, double& s, double& i);
		static void edgeconversion(image& src, image& tgt, vector<roi> roiList);
		
};

#endif

