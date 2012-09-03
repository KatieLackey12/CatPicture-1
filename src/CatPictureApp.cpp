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
*	A.1 (rectangle), A.2 (circle), A.
*	B.
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
	*by y and x in the for loop and its size by the parameters.
	*
	*@param pixels An array of pixels
	*@param x1 Determines the width of the rectangle
	*@param y1 Determines the height of the rectangle
	*@param x2 
	*@param y2 
	*/
	void createRectangle(uint8_t* pixels, int x1, int y1, int x2, int y2);
	
	/**
	*Draws a line segment, 
	*
	*@param
	*/
	void createLine(uint8_t* pixels, int x1, int y1, int x2, int y2);
	
	/**
	*Draws a filled circle, 
	*
	*@param 
	*/
	void createCircle(uint8_t* pixels, int x, int y, int r);

	/**
	*Draws a triangle...
	*
	*@param
	*/
	void createTriangle(uint8_t* pixels, int legLength, int pt1, int pt2, int pt3);
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

		for (int y = 30; y <= endy; y++){			
			for (int x = 50; x <= endx; x++) {
				offset = 3*(x+y*surfaceSize);
				pixels[offset] = 50;
				pixels[offset+1] = 150;
				pixels[offset+2] = 200;		
			}		
		}	

}

void CatPictureApp::createLine(uint8_t* pixels, int x1, int y1, int x2, int y2) {
	
	int offset;
	float dify, difx, slope, count;

	//Use formula for the slope of a line segment:
	dify = y2-y1;
	difx = x2-x1;
	slope = dify/difx;
	count = y1;

	for (int i = x1; i <= x2; i++) {
		
		offset = 3*(i+slope*surfaceSize);

		pixels[offset]=50;
		pixels[offset+1]=150;
		pixels[offset+2]=50;
		
		count += slope;
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
				pixels [offset] = 100;
				pixels [offset+1] = 10;
				pixels [offset+2] = 100;
			}
		}
	}
}

void CatPictureApp::createTriangle(uint8_t* pixels, int legLength, int pt1, int pt2, int pt3) {

	if ((pt1 <= appWidth) && ((pt1 + legLength) <= appWidth)) {

		int x = pt1;
		int y = pt2;

		for (int i = 0; i <= legLength; i++) {
			pixels[3*(x+y*surfaceSize)] = 0;
			pixels[3*(x+y*surfaceSize)+1] = 100;
			pixels[3*(x+y*surfaceSize)+2] = 100;

			x += 1;
			y += 1;
		}

		for (int i = 0; i <= legLength*2; i++) {
			pixels[3*(x+y*surfaceSize)] = 0;
			pixels[3*(x+y*surfaceSize)+1] = 100;
			pixels[3*(x+y*surfaceSize)+2] = 100;

			x -= 1;
		}

		for (int i = 0; i <= legLength; i++) {
			pixels[3*(x+y*surfaceSize)] = 0;
			pixels[3*(x+y*surfaceSize)+1] = 100;
			pixels[3*(x+y*surfaceSize)+2] = 100;

			x += 1;
			y -= 1;
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

	createRectangle(pixels, 200, 300, 0, 0);
	//createLine(pixels, 100, 400, 200, 0);
	createCircle(pixels, 300, 350, 100);
	createTriangle(pixels, 100, 400, 200, 0);
}

void CatPictureApp::draw()
{
	//clear out the window with mint green
	gl::clear( Color( 0.7f, 1.0f, 0.7f ) ); 

	//draw the surface
	gl::draw(*mySurface_);
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
