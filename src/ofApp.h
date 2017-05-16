#pragma once

#include "ofMain.h"
#include "ofxFmodSoundPlayer2.h"
#include "ofxXmlSettings.h"
#include "ofxGui.h"
struct Player{
    int soundIndx;
    float age;
    float volume;
};
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
    void loadStrings();
    
    vector<string>fileNames;

    vector<Player> players;
    ofxFmodSoundPlayer2 soundPlayer[3];
    
    
    vector<string>fileNamesOut;
    
    vector<Player> playersOut;
    ofxFmodSoundPlayer2 soundPlayerOut[3];
    
    float masterVol=1.;
    
    string message;
    string filePath;

    string messageOut;
    string filePathOut;
    
    ofxPanel gui;
    ofParameter<float>volIn,volOut;
};
