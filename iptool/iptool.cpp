/************************************************************
 *															*
 * This sample project include three functions:				*
 * 1. Add intensity for gray-level image.					*
 *    Input: source image, output image name, value			*
 *															*
 * 2. Image thresholding: pixels will become black if the	*
 *    intensity is below the threshold, and white if above	*
 *    or equal the threhold.								*
 *    Input: source image, output image name, threshold		*
 *															*
 * 3. Image scaling: reduction/expansion of 2 for 			*
 *    the width and length. This project uses averaging 	*
 *    technique for reduction and pixel replication			*
 *    technique for expansion.								*
 *    Input: source image, output image name, scale factor	*
 *															*
 ************************************************************/

#include "./iptools/core.h"
#include <string.h>
#include <fstream>
#include <algorithm>

using namespace std;

#define MAXLEN 256

int main (int argc, char** argv)
{
	image src, tgt;
	ifstream fp(argv[1]);
	char str[MAXLEN];
	rsize_t strmax = sizeof str;
	char outfile[MAXLEN];
	char *pch, *next_pch;
	int nOP;

	//Variables to store input
	int roiCount, ws;
	//Roi vector to store list of rois 
	vector<roi> roiList;

	if (!fp.is_open()) {
		fprintf(stderr, "Can't open file: %s\n", argv[1]);
		exit(1);
	}

	fp >> str;
	roiCount = atoi(str);

	//Loop that reads each roi informationa and adds the roi object to the vector list
	for (int i = 0; i < roiCount; i++) {
		//Created a roi temp and passed the user input to each value
		roi roiTemp;

		fp >> str;
		roiTemp.i = atoi(str);

		fp >> str;
		roiTemp.j = atoi(str);

		fp >> str;
		roiTemp.iEnd = atoi(str);

		fp >> str;
		roiTemp.jEnd= atoi(str);

		//Adds the roi to the list of rois
		roiList.push_back(roiTemp);
	}

	//Get number of operations
	fp >> nOP;

	for (int OP = 0; OP < nOP; OP++) {
		fp >> str;
		src.read(str);

		fp >> str;
		strcpy_s(outfile, MAXLEN, str);

		fp >> str;

		////////////////////////////////////////////////////////////////////////////
		if (strncmp(str, "gradient", 8) == 0) {
			for (int x = 0; x < roiList.size(); x++) {
				utility::sobel(src, tgt, roiList);
			}
		}

		else if (strncmp(str, "threshold", 9) == 0) {
			for (int x = 0; x < roiList.size(); x++) {
				
				//Read threshold value
				fp >> str;
				int a = atoi(str);

				utility::sobel(src, tgt, roiList);
				utility::binarize(tgt, roiList, a);
			}
		}
		else if (strncmp(str, "direction", 9) == 0) {
			for (int x = 0; x < roiList.size(); x++) {

				//Read threshold value
				fp >> str;
				int a = atoi(str);

				//Read direction
				fp >> str;
				int b = atoi(str);
				utility::direction(src, tgt, roiList, a, b);
			}
		}
		else if (strncmp(str, "colorEdge", 9) == 0) {
			for (int x = 0; x < roiList.size(); x++) {
				
				//Read threshold value
				fp >> str;
				int a = atoi(str);

				//Read output image names
				char redOutput[256];
				char greenOutput[256];
				char blueOutput[256];

				fp >> str;
				strcpy_s(redOutput, 256, str);

				fp >> str;
				strcpy_s(greenOutput, 256, str);

				fp >> str;
				strcpy_s(blueOutput, 256, str);

				image redImage;
				image blueImage;
				image greenImage;

				utility::colorSobel(src, redImage, roiList, a, RED);
				redImage.save(redOutput);

				utility::colorSobel(src, greenImage, roiList, a, GREEN);
				greenImage.save(greenOutput);

				utility::colorSobel(src, blueImage, roiList, a, BLUE);
				blueImage.save(blueOutput);

				utility::oredImages(src, redImage, greenImage, blueImage, tgt, roiList);
			}
		}
		else if (strncmp(str, "intensityEdge", 13) == 0) {
			for (int x = 0; x < roiList.size(); x++) {
				char gradientOutput[256];

				//Read threshold value
				fp >> str;
				int a = atoi(str);

				fp >> str;
				strcpy_s(gradientOutput , 256, str);

				image gradientImage;
				image temp;

				utility::edgeconversion(src, temp, roiList);
				utility::sobel(temp, gradientImage, roiList);
				gradientImage.save(gradientOutput);

				tgt.resize(gradientImage.getNumberOfRows(), gradientImage.getNumberOfColumns());
				tgt.copyImage(gradientImage);

				utility::binarize(tgt, roiList, a);
			}
		}
		
		////////////////////////////////////////////////////////////////////////////
		else {
			cout << "Error at iteration op: " << OP << endl;
			printf("No function: %s\n", str);
			continue;
		}
       
		tgt.save(outfile);
	}
	//fclose(fp);
	fp.close();
	return 0;
}


