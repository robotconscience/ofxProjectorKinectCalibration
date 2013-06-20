//
//  RGBDCamCalibWrapperOfxOpenNi2.h
//  ProjectionCalibration_ofxOpenNI2
//
//  Created by BRenfer on 6/18/13.
//
//

/*
 WRAPPER CLASS FOR CALIBRATING 3D CAMERAS TO PROJECTORS
 ofxopenni
 */

#pragma once

#include "RGBDCamCalibWrapper.h"
#include "ofxOpenNI2Grabber.h"

using namespace cv;
using namespace ofxCv;

class RGBDCamCalibWrapperOfxOpenNi2 : public RGBDCamCalibWrapper {
    
private:
	ofxCvColorImage				colorImage;
    ofxOpenNI2Grabber*                  backend;
    bool                        ready;
    openni::CoordinateConverter coordianteConverter;
    
public:
	
	//Casting your backend
    void setup(void* _backend){
        ready = false;
        
        //cast the backend
        backend = static_cast<ofxOpenNI2Grabber*>(_backend);
        
        //check if the backend is connected & capturing calibrated video
        if(!backend->isReady) {
            ofLog(OF_LOG_ERROR,"Please open the kinect prior to setting the RGBDcamWrapper");
            return;
        }
        //		 if(!backend->grabsCalibratedVideo()) {
        //             ofLog(OF_LOG_ERROR,"Please enable the grabs calibrated video setting in for ofxKinectNui");
        //             return;
        //		 }
        
        //allocate buffers
        colorImage.allocate(640,480);//backend->getWidth(),backend->getHeight());
        
        ready = true;
    }
    
	//getting the calibrated color/depth image
	ofxCvColorImage	getColorImageCalibrated() {
        if (!ready) {
			ofLog(OF_LOG_ERROR,"Please open the kinect prior to setting the RGBDcamWrapper");
			return colorImage;
		}
		ofPixels p = backend->getRGBPixels();
		colorImage.setFromPixels(p);
		return colorImage;
	}
    
	//coordinate getters
	ofPoint	getWorldFromRgbCalibrated(ofPoint p) {
        if (!ready) {
			ofLog(OF_LOG_ERROR,"Please open the kinect prior to setting the RGBDcamWrapper");
			return ofPoint(0,0);
		}
        
        int index = backend->getDepthRawPixels().getPixelIndex(int(p.x), int(p.y));
        unsigned short z = backend->getDepthRawPixels()[index];
        
//        p.z = backend->getDepthRawPixels().getPixels()[(int)(backend->settings.width * p.y + p.x)] / 10000.0f;
        
//        cout << p.x <<":"<<p.y << ":"<< z <<endl;
        
        ofPoint toReturn;
        
        coordianteConverter.convertDepthToWorld(backend->depthSource.videoStream, p.x, p.y, float(z), &toReturn.x, &toReturn.y, &toReturn.z);
        //oniCoordinateConverterDepthToWorld(backend->depthSource.videoStream._getHandle(), p.x, p.y, p.z, &toReturn.x, &toReturn.y, &toReturn.z);
        
//        cout << toReturn.z << endl;
        
//        toReturn.z /= 10000.0f;
        
        return toReturn;
	}
    
};
