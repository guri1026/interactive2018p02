#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"

#define HOST "127.0.0.1"
#define PORT 8100

///////// player01 ///////////////

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    void shake();
    void no_shake();
    void left_move();
    void right_move();
    void straight_move();
    void sensu_open(); 
    void sensu_close();
    void sensu_stand();
    
    void serial_check();
    void calculation();
    void send_Message(); ///x250
    
    ofxOscSender sender;
    ofSerial serial;
    bool madeConnect;
    
    //// shake //////
    int value;
    int x,y,z;
    int data[4];
    int before_data[3];
    
    int shake_count;
    
    bool shake_on_off;
    bool move_right, move_left, move_straight;
    
    long d;
    
    
    ////// Gui_count ______________
    ofxPanel gui;
    ofxIntSlider shake_lim;
    ofxIntSlider move_min, move_max;
    ofxIntSlider sensu_lim;
    
    
		
};
