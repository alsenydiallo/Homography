Name: Alseny Diallo
Email: Alsenidiallo@live.com

Inluced Files:
--------------
- LUtest.c (containt a set of matrice test: 5x5, 10x10 and 600x600)
- LUdecomp.c : (contain algorithm for solving lineair system (matrice) 		matrice using LU decomposition)
- LUdecomp.h (conatain function declaration for the LUdecomp.c)
- hmap.c (contain implimentation that determines the pixel cordonote of  	the images to be transformed)
- Homography. (contain inplimentation for the image transformation involing
	projections)
- cheerios-small.ppm (image to be transfomed)
- boxtop.in (contain the desirable coordonte for transforming the image)
- Makefile (contain the compiling configuration)


Project Overview:
-----------------
For this project I implimmented a module for solving linear equations of the form Ax = b using LU decomposition and then used the module to build an application that determines the parameters of an interesting
image transformation involving projections. The program will discover a transformation that maps the pixels for the face on the cereal box. This type of transformation is called a homography

Build and Run:
--------------
the build and run configuration in contained in the make file.

Note: make sure you save the Makefile as "Makefile" with no extentsion. Any extention ex: Makefile.txt will cause the make file not to run.

for runing the makefile just type "make" on the command line of a unix console

run code with the line: 
./homography < boxtop.in | ./hmap cheerios-small.ppm 500 650 > face.ppm

Note:
-----
To be able to view the trasformed image, download a .ppm file reader
