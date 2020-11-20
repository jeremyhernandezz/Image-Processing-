Jeremy Hernandez

*** This project is built under Visual Studio 2015

This software is architectured as follows

iptool/iptool.cpp- This file includes the main function.

iptool/iptools -This folder hosts the files that are compiled into a static library. 
	image - This folder hosts the files that define an image and a roi.
	utility- this folder hosts the files that students store their implemented algorithms.


*** INSTALATION ***

On Windows

Open the project by double click iptool.sln.

*** FUNCTIONS ***

1.sobel
Function that applies gradient edge detection using the sobel operators.
 
2.dx
Function that calculates the dx for edge detection.

3.dy
Function that calculates the dy for edge detection.			

4.colorSobel
Function that applies gradient amplitude on RGB channels.

5.dxColor
Function that calculates the dx of a RGB channel.

6. dyColor
Function that calculates the dy of a TGB channel.

7.direction 
Function that generates binarized edge image of threshold gradient amplitude and direction.

8.oredImages
Function that combines all RGB channel images together by oring them. 

9.binarize 
Function that binarizes the image based on a given threshold.

10.RGBtoHSI
Function that converts RGB values to HSI.

11.edgeconversion
Function that converts the image from RBG to grey-image composed of the Intesity values from HSI of original image.


*** PARAMETERS ***

The first parameter of the parameters.txt is the number of rois in the image.
There second throught the 4 are the starting and ending x and y coordinates of one roi. (x1, y1, x2, y2)

Parameter following this is the number of operations that will be conducted. 

This is followed by 4 parameters  

1. the input file name;
2. the output file name;
3. the name of the filter. Use any of the functions mentioned above for your filters;
4. the value for user threshold, and the output file names edge detection on RGB channels and theshold on I images. 


*** Run the program:

Directly debug in Visual Studio.
You can find the output image in output folder.


*** Important information ***

Application assumes the next format of input image (ppm/pgm) file:
line1: <version>
line2: <#columns> <#rows>
line3: <max_value>
line4-end-of-file:<pix1><pix2>...<pix_n>

if it is a grayscale image then every pixel is a char value. If it is a RGB image then every pixel is a set of 3 char values: <red><green><blue>

Thus, if you have a problem with reading image, the first thing you should check is input file format.
