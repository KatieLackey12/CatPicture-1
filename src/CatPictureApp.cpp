/**
*@file CatPictureApp.cpp
*
*@author Allyson Yoder
*@date 8/26/2012
*
*@note This project was written as a homework assignment for
*CSE 274 taught by Dr. Brinkman at Miami University during the 
*Fall 2012 semester.
*
*This project satisfys the following requirements for HW1:
*	A.1 (rectangle), A.2 (circle), A.3 (line), A.7 (triangle)
*	B.
*	C The picture my program draws is a little red house and a sun
*		with a singular ray shining from it just for kicks :)
*	D Image saves to a file "yoderal2.png"
*	E. 
*/

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CatPictureApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void settings(Settings* mySettings);

private:
	//float brightness;
	Surface* mySurface_; //create a surface to display and modify

	static const int appWidth = 800;
	static const int appHeight = 600;
	static const int surfaceSize = 1024;

	/**
	*Draws a filled rectangle to the screen, its location is determined
	*by y and x in the for loop and its size is determined by the parameters.
	*
	*@param pixels An array of pixels
	*@param x1 Determines the width of the rectangle
	*@param y1 Determines the height of the rectangle
	*@param x2 The x-coordinate for the bounds of the rectangle
	*@param y2 The y-coordinate for the bounds of the rectangle
	*
	*Satisfys requirement A.1
	*/
	void createRectangle(uint8_t* pixels, int x1, int y1, int x2, int y2);
	
	/**
	*Draws a line segment.
	*
	*@param pixels An array of pixels
	*@param segLength Determines the length of the segment
	*@param pt1 The x-coordinate for the starting position
	*@param pt2 The y-coordinate for the starting position
	*
	*Satisfys requirement A.3
	*/
	void createLine(uint8_t* pixels, int segLength, int pt1, int pt2);
	
	/**
	*Draws a filled circle, 
	*
	*@param pixels An array of pixels
	*@param x The x-coordinate of the position of the circle center
	*@param y The y-coordinate of the position of the circle center
	*@param r The size of the radius
	*
	*Satisfys requirement A.2
	*/
	void createCircle(uint8_t* pixels, int x, int y, int r);

	/**
	*Draws an empty triangle made up of 3 line segments. 
	*
	*@param pixels An array of pixels
	*@param legLength Determines how long the legs of the triangle will be
	*@param pt1 The x-coordinate for the starting position
	*@param pt2 The y-coordinate for the starting position
	*
	*Satisfys requirement A.7
	*/
	void createTriangle(uint8_t* pixels, int legLength, int pt1, int pt2);

	/**
	*
	*/
	void blurSurface(uint8_t* pixels);
};

void CatPictureApp::settings(Settings* mySettings) {
	(*mySettings).setWindowSize(appWidth, appHeight);
	(*mySettings).setResizable(false);
}

void CatPictureApp::createRectangle(uint8_t* pixels, int x1, int y1, int x2, int y2) {
	//Find starting and ending coordinates of rectangle 
	int startx = (x1 < x2) ? x1 : x2;
	int endx = (x1 > x2) ? x1 : x2;
	int starty = (y1 < y2) ? y1 : y2;
	int endy = (y1 > y2) ? y1 : y2;

	//Bounds checking
	if (endx < 0) return;
	if (endy < 0) return;
	if (startx >= appWidth) return;
	if (starty >= appHeight) return;
	if (endx >= appWidth) endx = appWidth-1;
	if (endy >= appHeight) endy = appHeight-1;
	
	int offset;

		for (int y = 75; y <= endy; y++){			
			for (int x = 50; x <= endx; x++) {
				offset = 3*(x+y*surfaceSize);
				pixels[offset] = 178;
				pixels[offset+1] = 34;
				pixels[offset+2] = 34;		
			}		
		}	

}

void CatPictureApp::createLine(uint8_t* pixels, int segLength, int pt1, int pt2) {
	
	int x = pt1;
	int y = pt2;

		for (int i = 0; i <= segLength; i++) {
			pixels[3*(x+y*surfaceSize)] = 255;
			pixels[3*(x+y*surfaceSize)+1] = 245;
			pixels[3*(x+y*surfaceSize)+2] = 0;

			x += 1;
			y += 1;
		}
}

void CatPictureApp::createCircle(uint8_t* pixels, int x, int y, int r) {

	if (r <= 0) return;

	for(int newY = y-r; newY <= y+r; newY++) {
		for (int newX=x-r; newX <= x+r; newX++) {
			//Check bounds
			if (newY < 0 || newX < 0 || newY >= appHeight || newX >= appWidth) continue;

			int newR = (int)sqrt((double)((newX-x)*(newX-x) + (newY-y)*(newY-y)));

			if(newR <= r) {
				int offset = 3*(newX+newY*surfaceSize);
				pixels [offset] = 255;
				pixels [offset+1] = 245;
				pixels [offset+2] = 0;
			}
		}
	}
}

void CatPictureApp::createTriangle(uint8_t* pixels, int legLength, int pt1, int pt2) {

	if ((pt1 <= appWidth) && ((pt1 + legLength) <= appWidth)) {

		int x = pt1;
		int y = pt2;

		for (int i = 0; i <= legLength; i++) {
			pixels[3*(x+y*surfaceSize)] = 139;
			pixels[3*(x+y*surfaceSize)+1] = 69;
			pixels[3*(x+y*surfaceSize)+2] = 19;

			x += 1;
			y += 1;
		}

		
		for (int i = 0; i <= legLength*2; i++) {
			pixels[3*(x+y*surfaceSize)] = 139;
			pixels[3*(x+y*surfaceSize)+1] = 69;
			pixels[3*(x+y*surfaceSize)+2] = 19;

			x -= 1;
		}

		for (int i = 0; i <= legLength; i++) {
			pixels[3*(x+y*surfaceSize)] = 139;
			pixels[3*(x+y*surfaceSize)+1] = 69;
			pixels[3*(x+y*surfaceSize)+2] = 19;

			x += 1;
			y -= 1;
		}
	}
}

void CatPictureApp::blurSurface(uint8_t* pixels) {

	int offset;
	float z = 1.0/9.0;
	float kernal[9] = 
	{z, z, z,
	z, z, z, 
	z, z, z};

	for (int y1 = 1; y1 < appHeight+1; y1++) {
		for (int x1 = 1; x1 < appWidth+1; x1++) {
			for (int y2 = 1; y2 < y1+1; y2++) {
				for (int x2 = 1; x2 < x1+1; x2++) {
					//calculate offset for y2 and x2
					//offset = 3*(x2+y2*surfaceSize);
					//pixels [offset] = 255;
					//pixels [offset + 1] = 0;
					//pixels [offset + 2] = 0;
				}
			}
			//store in offset for x1 and y1
			//offset = 3*(x1+y1*surfaceSize);
			//pixels [offset] = 255;
			//pixels [offset + 1] = 0;
			//pixels [offset + 2] = 0;
		}
	}
	
}

void CatPictureApp::setup()
{
	//brightness = 1.0f;
	mySurface_ = new Surface(surfaceSize, surfaceSize, false);

}

void CatPictureApp::mouseDown( MouseEvent event )
{
}

void CatPictureApp::update()
{
	//brightness = brightness - 0.01f;
	//if(brightness < 0.0f){
		//brightness = 1.0f; }

	//Get array of pixel info
	uint8_t* pixels = (*mySurface_).getData();

	createRectangle(pixels, 50, 100, 150, 175);
	createCircle(pixels, 200, 25, 30);
	createTriangle(pixels, 50, 100, 25);
	createLine(pixels, 50, 200, 25);

	writeImage("yoderal2.png", *mySurface_);
}

void CatPictureApp::draw()
{
	//clear out the window with mint green
	gl::clear( Color( 0.7f, 1.0f, 0.7f ) ); 

	//draw the surface
	gl::draw(*mySurface_);
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
