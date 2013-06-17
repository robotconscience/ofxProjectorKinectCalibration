/** OFXKINECTPROJECTORCALIBRATION **/
/** work in progress, not even beta! **/
/** Kj1, www.hangaar.net **/

#pragma once

#include "ofMain.h"
#include "ofxUI.h"

#ifdef TARGET_WIN32
#include <Shlobj.h>
#include "ofxKinectNui.h"
#elif defined TARGET_OSX
#include "ofxOpenNI.h"
#endif

#include "ofxKinectProjectorCalibration.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"

#include "SecondWindow.h"
#include "ofxFensterManager.h"

using namespace cv;
using namespace ofxCv;

class testApp : public ofBaseApp 
{
    public:

        void setup();
        void update();
        void draw();
        void exit();

        void keyPressed(int key);
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void windowResized(int w, int h);

	private:
    //kinect & the wrapper
#ifdef TARGET_WIN32
        ofxKinectNui				camera;
#elif defined TARGET_OSX
        ofxOpenNI                   camera;
#endif
		ofxCvColorImage				kinectCalibratedColorImage;
        ofxCvColorImage             kinectImageGrayRGBA; // for ofxOpenNI...
		ofxCvGrayscaleImage			kinectLabelImageGray;
		RGBDCamCalibWrapper*		kinectWrapper;
		
		//calibration
		KinectProjectorCalibration	kinectProjectorCalibration;
		bool						enableCalibration;
		ofxCvContourFinder			contourFinder;

		//output
		KinectProjectorOutput		kinectProjectorOutput;
		bool						enableTestmode;

		//settings
		int projectorWidth;
		int projectorHeight;

		//gui
		void setupGui();
	    ofxUICanvas *gui;
		void guiEvent(ofxUIEventArgs &e);   
		void guiUpdateLabels();   

		//second window
		void setupSecondWindow();
		SecondWindow secondWindow;
		ofFbo secondWindowFbo;


};
