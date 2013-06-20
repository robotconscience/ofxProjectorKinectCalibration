/** OFXKINECTPROJECTORCALIBRATION **/
/** work in progress, not even beta! **/
/** Kj1, www.hangaar.net **/

#pragma once

#include "ofMain.h"
#include "ofxUI.h"

#define USE_OPENNI2

#include "ofxKinectProjectorCalibration.h"

#ifdef TARGET_WIN32
#include <Shlobj.h>
#include "ofxKinectNui.h"
#elif defined TARGET_OSX
#ifdef USE_OPENNI2
#include "ofxOpenNI2Grabber.h"
#include "RGBDCamCalibWrapperOfxOpenNi2.h"
#else
#include "ofxOpenNI.h"
#include "RGBDCamCalibWrapperOfxOpenNi.h"
#endif
#endif

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
#ifdef USE_OPENNI2
        ofxOpenNI2Grabber           camera;
#else
        ofxOpenNI                   camera;
#endif
#endif
		ofxCvColorImage				kinectCalibratedColorImage;
        ofxCvColorImage             kinectImageGrayRGBA; // for ofxOpenNI...
		ofxCvGrayscaleImage			kinectLabelImageGray;
		RGBDCamCalibWrapper*		kinectWrapper;
		
		//calibration
		KinectProjectorCalibration	kinectProjectorCalibration;
		bool						enableCalibration;
    
        ContourFinder               contourFinder;
        float                         threshold;

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
