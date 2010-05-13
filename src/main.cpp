/*=======================================================
 Copyright (c) avp::ptr, 2010
=======================================================*/

#include "DrawingLifeIncludes.h"
#include "DrawingLifeApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){
    int w;
    int h;
    ofxXmlSettings settings;
	
#if defined TARGET_OSX
	// On mac the working directory is at this point in bin.
	// In DrawingLifeApp working directory is DrawingLifeApp.app/Contents/MacOS
	// Have to set Data dir seperately in main.cpp and DrawingLifeApp.cpp.
	ofSetDataPathRoot("./data/");
#endif
    settings.loadFile("AppSettings.xml");
    w = settings.getValue("settings:window:width", 1024);
    h = settings.getValue("settings:window:height", 768);

    ofAppGlutWindow window;
//    ofSetupOpenGL(&window, 1680,1000, OF_GAME_MODE);
	ofSetupOpenGL(&window, w, h, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new DrawingLifeApp(settings));
}
