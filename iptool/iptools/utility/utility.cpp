#include "utility.h"
#include <algorithm>

#define MAXRGB 255
#define MINRGB 0
#define PI 3.14159265

std::string utility::intToString(int number)
{
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

int utility::checkValue(int value)
{
	if (value > MAXRGB)
		return MAXRGB;
	if (value < MINRGB)
		return MINRGB;
	return value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Function that applies gradient edge detection using the sobel operators.
 void utility::sobel(image& src, image& tgt, vector<roi>& roiList)
 {
	 tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	 tgt.copyImage(src);


	 for (int x = 0; x < roiList.size(); x++) {

		 int sum = 0;
		 int dX, dY;

		 for (int i = 1; i < src.getNumberOfRows() -1; i++)
		 {
			 for (int j = 1; j < src.getNumberOfColumns() -1; j++)
			 {
				 //Checks that the pixel is within the  boundaries
				 if ((i >= roiList[x].i) && (i <= roiList[x].iEnd) && (j >= roiList[x].j) && (j <= roiList[x].jEnd)) {
					 dX = dx(src, i, j);
					 dY = dy(src, i, j);
					 sum = abs(dX) + abs(dY);
					 sum = checkValue(sum);
					 tgt.setPixel(i, j, sum);

				 }
			 }
		 }
	 }

 }

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //Function that calculates dx
 int utility::dx(image& src, int j, int i)
 {

	 return src.getPixel(j - 1, i - 1) + 2 * src.getPixel(j, i - 1) +
		 src.getPixel(j + 1, i - 1) - src.getPixel(j - 1, i + 1) -
		 2 * src.getPixel(j, i + 1) - src.getPixel(j + 1, i + 1);

	 //return (src.getPixel(i - 1, j - 1) * -1) + (src.getPixel(i - 1, j + 1) * 1) +
		// (src.getPixel(i, j - 1) * -2) + (src.getPixel(i, j + 1) * 2) +
		// (src.getPixel(i + 1, j - 1) * -1) + (src.getPixel(i + 1, j + 1) * 1);
 }

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //Function that calculates dy
 int utility::dy(image& src, int j, int i)
 {
	 return src.getPixel(j - 1, i - 1) + 2 * src.getPixel(j - 1, i) +
		 src.getPixel(j - 1, i + 1) - src.getPixel(j + 1, i - 1) -
		 2 * src.getPixel(j + 1, i) - src.getPixel(j + 1, i + 1);

	 //return (src.getPixel(i - 1, j - 1) * 1) + (src.getPixel(i - 1, j) * 2) +
		// (src.getPixel(i - 1, j + 1) * 1) + (src.getPixel(i + 1, j - 1) * -1) +
		// (src.getPixel(i + 1, j) * -2) + (src.getPixel(i + 1, j + 1) * -1);
 }

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //Function that performs gradient amplitude. 
 void utility::colorSobel(image& src, image& tgt, vector<roi>& roiList, int threshold, const int& color)
 {
	 tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	 tgt.copyImage(src);


	 for (int x = 0; x < roiList.size(); x++) {

		 int sum = 0;
		 int dX, dY;

		 for (int i = 1; i < src.getNumberOfRows() - 1; i++)
		 {
			 for (int j = 1; j < src.getNumberOfColumns() - 1; j++)
			 {
				 //Checks that the pixel is within the  boundaries
				 if ((i >= roiList[x].i) && (i <= roiList[x].iEnd) && (j >= roiList[x].j) && (j <= roiList[x].jEnd)) {
					 dX = dxColor(src, i, j, color);
					 dY = dyColor(src, i, j, color);
					 sum = abs(dX) + abs(dY);
					 sum = checkValue(sum);
					 tgt.setPixel(i, j, color, sum);
				 }
			 }
		 }

		 for (int i = 0; i < src.getNumberOfRows(); i++)
		 {
			 for (int j = 0; j < src.getNumberOfColumns(); j++)
			 {
				 if ((i >= roiList[x].i) && (i <= roiList[x].iEnd) && (j >= roiList[x].j) && (j <= roiList[x].jEnd)) {

					 if (tgt.getPixel(i, j, color) < threshold) {
						 tgt.setPixel(i, j, RED, MINRGB);
						 tgt.setPixel(i, j, GREEN, MINRGB);
						 tgt.setPixel(i, j, BLUE, MINRGB);
					 }
					 else {
						 tgt.setPixel(i, j, RED, MAXRGB);
						 tgt.setPixel(i, j, GREEN, MAXRGB);
						 tgt.setPixel(i, j, BLUE, MAXRGB);
					 }
				 }
			 }
		 }
	 }

 }
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //Function that calculates dx
 int utility::dxColor(image& src, int j, int i, const int& color)
 {
	 return src.getPixel(j - 1, i - 1, color) + 2 * src.getPixel(j, i - 1, color) +
		 src.getPixel(j + 1, i - 1, color) - src.getPixel(j - 1, i + 1, color) -
		 2 * src.getPixel(j, i + 1, color) - src.getPixel(j + 1, i + 1, color);
 }

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //Function that calculates dy
 int utility::dyColor(image& src, int j, int i, const int& color)
 {
	 return src.getPixel(j - 1, i - 1, color) + 2 * src.getPixel(j - 1, i, color) +
		 src.getPixel(j - 1, i + 1, color) - src.getPixel(j + 1, i - 1, color) -
		 2 * src.getPixel(j + 1, i, color) - src.getPixel(j + 1, i + 1, color);
 }

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //Function that applis gradient amplitude and and direction and threshold. 
 void utility::direction(image& src, image& tgt, vector<roi>& roiList, int threshold, double direction)
 {
	 tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	 tgt.copyImage(src);

	 for (int x = 0; x < roiList.size(); x++) {

		 int sum = 0;
		 int dX, dY;
		 double angle;

		 for (int i = 1; i < src.getNumberOfRows() - 1; i++)
		 {
			 for (int j = 1; j < src.getNumberOfColumns() - 1; j++)
			 {
				 //Checks that the pixel is within the  boundaries
				 if ((i >= roiList[x].i) && (i <= roiList[x].iEnd) && (j >= roiList[x].j) && (j <= roiList[x].jEnd)) {
					 dX = dx(src, j, i);
					 dY = dy(src, j, i);
					 //caculate the direction
					 angle = atan2(dY, dX) * 180 / PI;
					 sum = abs(dX) + abs(dY);
					 sum = checkValue(sum);
					 tgt.setPixel(i, j, sum);
					 //Check if within direction specified
					 if (angle >= direction - 10 && angle <= direction + 10) {

						 if (tgt.getPixel(i, j) < threshold)
							 tgt.setPixel(i, j, MINRGB);
						 else
							 tgt.setPixel(i, j, MAXRGB);
					 }
					 else {
						 tgt.setPixel(i, j, MINRGB);
					 }
				 }
			 }
		 }
	 }
 }

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //Function that binarizes images
 void utility::binarize(image& src, vector<roi>& roiList, int threshold)
 {
	 for (int x = 0; x < roiList.size(); x++) {

		 for (int i = 0; i < src.getNumberOfRows(); i++)
		 {
			 for (int j = 0; j < src.getNumberOfColumns(); j++)
			 {
				 //Checks that the pixel is within the roi boundaries
				 if ((i >= roiList[x].i) && (i <= roiList[x].iEnd) && (j >= roiList[x].j) && (j <= roiList[x].jEnd))
				 {
					 if (src.getPixel(i, j) < threshold)
						 src.setPixel(i, j, MINRGB);
					 else
						 src.setPixel(i, j, MAXRGB);
				 }
			 }
		 }
	 }
 }

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //Function that combines three images together 
 void utility::oredImages(image& src, image& red, image& green, image& blue, image& tgt, vector<roi>& roiList)
 {
	 tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	 tgt.copyImage(src);

	 for (int x = 0; x < roiList.size(); x++) {

		 for (int i = 0; i < src.getNumberOfRows(); i++)
		 {
			 for (int j = 0; j < src.getNumberOfColumns(); j++)
			 {
				 //Checks that the pixel is within the  boundaries
				 if ((i >= roiList[x].i) && (i <= roiList[x].iEnd) && (j >= roiList[x].j) && (j <= roiList[x].jEnd)) {
					 if (red.getPixel(i, j) == MAXRGB || green.getPixel(i, j) == MAXRGB || blue.getPixel(i, j) == MAXRGB) {
						 tgt.setPixel(i, j, RED, MAXRGB);
						 tgt.setPixel(i, j, GREEN, MAXRGB);
						 tgt.setPixel(i, j, BLUE, MAXRGB);
					 }
					 else {
						 tgt.setPixel(i, j, RED, MINRGB);
						 tgt.setPixel(i, j, GREEN, MINRGB);
						 tgt.setPixel(i, j, BLUE, MINRGB);
					 }
				 }
			 }
		 }
	 }
 }

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //Function that convert rgb to hsi 
 void utility::RGBtoHSI(double r, double g, double b, double& h, double& s, double& i)
 {
	 double rn = r / (r + g + b);
	 double gn = g / (r + g + b);
	 double bn = b / (r + g + b);

	 h = acos((0.5 * ((rn - gn) + (rn - bn))) / (sqrt((rn - gn) * (rn - gn) + (rn - bn) * (gn - bn))));

	 if (bn > gn) {
		 h = 2 * PI - h;
	 }

	 s = 1 - 3 * min(rn, min(gn, bn));

	 i = (r + g + b) / (3 * 255.0);

	 h = (h * 180) / PI;
	 i = i * 255;
	 //s = s * 100;

 }

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //Function that converts the image from RBG to grey-image composed of the Intesity values from HSI of original image.
 void utility::edgeconversion(image& src, image& tgt, vector<roi> roiList) {

	 tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());

	 for (int x = 0; x < roiList.size(); x++) {

		 double R, G, B, H, S, I;

		 for (int i = 0; i < src.getNumberOfRows(); i++)
		 {
			 for (int j = 0; j < src.getNumberOfColumns(); j++)
			 {
				RGBtoHSI(src.getPixel(i, j, RED), src.getPixel(i, j, GREEN), src.getPixel(i, j, BLUE), H, S, I);
				tgt.setPixel(i, j, I);
			 }
		 }
	 }
 }
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////