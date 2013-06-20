#include "testApp.h"
#include "ofMain.h"
#include "ofAppGlutWindow.h"
#include "ofxFensterManager.h"

//========================================================================
int main( ){
	ofSetupOpenGL(ofxFensterManager::get(), 1280, 800, OF_WINDOW);

	ofRunFensterApp(new testApp());
}
