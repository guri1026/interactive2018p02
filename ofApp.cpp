#include "ofApp.h"

////////// player02 /////////////////////


//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,150);
    ofSetFrameRate(30);
    
    sender.setup(HOST, PORT);
    
    
    serial.setup("/dev/cu.usbserial-DM009MZW", 9600);
    madeConnect = false;
    
    
    /// Gui setup
    gui.setup();
    gui.add(shake_lim.setup("shake_lim", 200, 0, 400));
    gui.add(move_min.setup("move_min left", 300, 0, 900));
    gui.add(move_max.setup("move_max right", 590, 0, 900));
    gui.add(sensu_lim.setup("open_lim", 29, 20, 40));
    
}


//--------------------------------------------------------------
void ofApp::update(){
    serial_check();
    
    calculation();
    
    send_Message();
    
    
    ///////////////////////////////////////////////
    
    cout << "x : " << data[0] << " / " <<
    "y : " << data[1] << " / " <<
    "z : " << data[2] << " / " <<
    "foto : " << data[3] << " / " << endl;
    
    ///////////////////////////////////////////////

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawBitmapString("player02", 220, 50);
    
    gui.draw();
    if(shake_on_off){
        ofDrawBitmapString("shake", 50, ofGetHeight()/2);
    }
    else{
        ofDrawBitmapString("No_shake", 50, ofGetHeight()/2);
    }
    
    if(move_left){
        ofDrawBitmapString("left", 150, ofGetHeight()/2);
    }
    else if(move_straight){
        ofDrawBitmapString("straight", 150, ofGetHeight()/2);
    }
    else if(move_right){
        ofDrawBitmapString("right", 150, ofGetHeight()/2);
    }
    
    if(data[3] <= sensu_lim)
        ofDrawBitmapString("close", 250, ofGetHeight()/2);
    else
        ofDrawBitmapString("open", 250, ofGetHeight()/2);
    
    if(data[0] <= 320)
        ofDrawBitmapString("stand", 250, ofGetHeight()/2 + 30);
}

//--------------------------------------------------------------

void ofApp::serial_check(){
    /// シリアル通信を行う
    if(madeConnect == false){
        serial.writeByte(255);
    }
    
    if(serial.available() >= 4){
        for(int i=0; i<3; i++){
            before_data[i] = data[i];
        }
        madeConnect = true;
        value = serial.readByte();
        
        if(value == 255){
            for(int i=0; i<4; i++){
                data[i] = ofMap(serial.readByte(), 0, 100, 0, 1023);
            }
        }
        
        serial.writeByte(255);
        
    }
}

//--------------------------------------------------------------

void ofApp::calculation(){
    int sum = 0;
    for(int i=0; i<3; i++){
        sum = sum + pow( ( data[i]-before_data[i] ), 2.0);
    }
    d = 0;
    d = sqrt(sum);
    
    /// shake __________________
    if(d > shake_lim){
        shake_on_off = true;
    }
    else{
        shake_on_off = false;
        move_right = move_left = false;
    }
    
    /// move ___________________
    if(shake_on_off == true && data[1] < move_min){
        move_left = false;
        move_straight = false;
        
        move_left = true;
    }
    
    else if(shake_on_off == true &&  move_min <= data[1] && data[1] <= move_max){
        move_right = false;
        move_left = false;
        
        move_straight = true;
        
    }
    
    else if(shake_on_off == true && data[1] > move_max){
        move_right = false;
        move_straight = false;
        
        move_right = true;
    }
    
    else{
        move_right = move_straight = move_left = false;
    }
    
    
}

//--------------------------------------------------------------

void ofApp::send_Message(){
    if(shake_on_off)    shake();
    else    no_shake();
    
    
    if(move_right)  right_move();
    else if(move_left)   left_move();
    else if(move_straight)  straight_move();
    
    
    if(data[3] <= sensu_lim)   sensu_close();
    else    sensu_open();
    
    
    if(data[0] <= 320){
        sensu_stand();
    }
    
    
}

//--------------------------------------------------------------

void ofApp::shake(){
    ofxOscMessage m;
    m.setAddress("/player02/shake/yes");
    //m.addFloatArg(shake_on_off);
    sender.sendMessage(m);
}

void ofApp::no_shake(){
    ofxOscMessage m;
    m.setAddress("/player02/shake/no");
    sender.sendMessage(m);
}

void ofApp::right_move(){
    ofxOscMessage m;
    m.setAddress("/player02/move/right");
    sender.sendMessage(m);
    
}

void ofApp::left_move(){
    ofxOscMessage m;
    m.setAddress("/player02/move/left");
    sender.sendMessage(m);
}

void ofApp::straight_move(){
    ofxOscMessage m;
    m.setAddress("/player02/move/straight");
    sender.sendMessage(m);
}

void ofApp::sensu_open(){
    ofxOscMessage m;
    m.setAddress("/player02/sensu/open");
    sender.sendMessage(m);
}

void ofApp::sensu_close(){
    ofxOscMessage m;
    m.setAddress("/player02/sensu/close");
    sender.sendMessage(m);
}
void ofApp::sensu_stand(){
    ofxOscMessage m;
    m.setAddress("/player02/sensu/stand");
    sender.sendMessage(m);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
