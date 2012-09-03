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

	void createRectangle(uint8_t* pixels, int x1, int y1, int x2, int y2);
	void createLine(uint8_t* pixels, int x, int y);
	void createCircle(uint8_t* pixels, int x, int y, int r);
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
	
		for (int y = 10; y <= endy; y++){			
			for (int x = 20; x <= endx; x++) {				
				pixels [3* (x+y*surfaceSize)]=50;
				pixels [3* (x+y*surfaceSize)+1]=150;
				pixels [3* (x+y*surfaceSize)+2]=200;		
			}		
		}	

}
/*
void CatPictureApp::createLine(uint8_t* pixels, int x, int y) {
	for (int i = 0; i <= x-1; i++) {
		pixels[3*i]=200;
		pixels[3*i+1]=150;
		pixels[3*i+2]=50;
	}
}
*/

void CatPictureApp::createCircle(uint8_t* pixels, int x, int y, int r) {

	if (r <= 0) return;

	for(int newY = y-r; newY <= y+r; newY++) {
		for (int newX=x-r; newX <= x+r; newX++) {
			//Check bounds
			if (newY < 0 || newX < 0 || newY >= appHeight || newX >= appWidth) continue;

			int newR = (int)sqrt((double)((newX-x)*(newX-x) + (newY-y)*(newY-y)));

			if(newR <= r) {
				int offset = 3*(newX+newY*surfaceSize);
				pixels [offset] = 175;
				pixels [offset+1] = 150;
				pixels [offset+2] = 50;
			}
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

	//Color8u fill1 = Color8u(128,128,192);
	//Color8u border1 = Color8u(192,192,255);
	//Color8u fill2 = Color8u(192,192,192);
	//Color8u border2 = Color8u(255,255,255);

	createRectangle(pixels, 300, 100, 50, 100);
	//createLine(pixels, 800, 600);
	createCircle(pixels, 300, 350, 100);
}

void CatPictureApp::draw()
{
	//clear out the window with mint green
	gl::clear( Color( 0.7f, 1.0f, 0.7f ) ); 

	//draw the surface
	gl::draw(*mySurface_);
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
