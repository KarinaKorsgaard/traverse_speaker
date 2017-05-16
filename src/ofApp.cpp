#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    gui.setup();
    gui.add(volIn.set("volume in",0,0,5));
    gui.add(volOut.set("volume out",0,0,5));
    gui.loadFromFile("settings.xml");
    
    ofxXmlSettings xml;
    xml.load("config.xml");
    filePath = xml.getValue("config:path", "");
    filePathOut = xml.getValue("config:pathOut", "");
    cout << filePathOut << endl;
    loadStrings();
    cout<< fileNames.size()<<endl;
    cout<< fileNamesOut.size()<<endl;
    
    ofxFmodSetPreferedDevice(0);
    
    for(int i = 0; i<3;i++){
        
        soundPlayer[i].setMix8(1, 0, 0, 0, 0, 0, 0, 0);
        
        Player p = *new Player;
        
        int sIndx = int(ofRandom(fileNames.size()));
        soundPlayer[i].setVolume(0.f);
        if(fileNames.size()>0)soundPlayer[i].load(fileNames[sIndx]);
        soundPlayer[i].play();
        players.push_back(p);
    }
    
    for(int i = 0; i<3;i++){
        soundPlayerOut[i].setMix8(0, 1, 0, 0, 0, 0, 0, 0);
        Player p = *new Player;
        
        int sIndx = int(ofRandom(fileNamesOut.size()));
        soundPlayerOut[i].setVolume(0.f);
        if(fileNamesOut.size()>0)soundPlayerOut[i].load(fileNamesOut[sIndx]);
        soundPlayerOut[i].play();
        playersOut.push_back(p);
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofxFmodSoundUpdate();
    
    if(ofGetFrameNum()%200==0)loadStrings();
    
//    if(fileNames.size()>2000)
//        ofFile::removeFile(fileNames.front(), false);
    
    for(int i = 0; i<players.size();i++){
        Player * p = &players[i];
        p->age++;
        if(p->age>60*60)p->volume-=0.1;
        else if (p->age<30)p->volume+=0.01;
        else if (ofRandom(1)>.5)p->volume+=0.01;
        else p->volume-=0.01;
        
        if(p->volume<0. || (!soundPlayer[i].isPlaying() && p->age>10)){
            
            int sIndx = int(ofRandom(fileNames.size()-1));
            soundPlayer[i].unload();
            if(fileNames.size()>0)soundPlayer[i].load(fileNames[sIndx]);
            p->age = 0;
            p->volume = 0;
            p->soundIndx = sIndx;
            soundPlayer[i].play();
        }
        p->volume=CLAMP(p->volume,0,1);
        soundPlayer[i].setVolume(p->volume*volIn);
    }
    
    for(int i = 0; i<playersOut.size();i++){
        Player * p = &playersOut[i];
        p->age++;
        if(p->age>60*60)p->volume-=0.1;
        else if (p->age<30)p->volume+=0.01;
        else if (ofRandom(1)>.5)p->volume+=0.01;
        else p->volume-=0.01;
        
        if(p->volume<0. || (!soundPlayerOut[i].isPlaying() && p->age>10)){
            
            int sIndx = int(ofRandom(fileNamesOut.size()-1));
            soundPlayerOut[i].unload();
            if(fileNamesOut.size()>0)soundPlayerOut[i].load(fileNamesOut[sIndx]);
            p->age = 0;
            p->volume = 0;
            p->soundIndx = sIndx;
            soundPlayerOut[i].play();
        }
        p->volume=CLAMP(p->volume,0,1);
        soundPlayerOut[i].setVolume(p->volume*volOut);
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
    ofTranslate(250,0);
    ofDrawBitmapString("master volume "+ofToString(masterVol), 10, 150);
    
    for(int i = 0; i<players.size();i++){
        Player p = players[i];
        ofDrawBitmapString(ofToString(p.soundIndx), i*30+15, 120);
        ofDrawRectangle(i*30, 0, 28, p.volume*100);
    }
    ofDrawBitmapString(message, 10, 320);
    ofDrawBitmapString(messageOut, 10, 420);
    ofTranslate(200,0);
    //ofDrawBitmapString("master volume "+ofToString(masterVol), 10, 150);
    for(int i = 0; i<playersOut.size();i++){
        Player p = playersOut[i];
        ofDrawBitmapString(ofToString(p.soundIndx), i*30+15, 120);
        ofDrawRectangle(i*30, 0, 28, p.volume*100);
    }
    
   
}

void ofApp::loadStrings(){
    
    fileNames.clear();
    fileNamesOut.clear();
    
    
    string path = filePath;
    ofDirectory dir(path);
    
    dir.allowExt("wav");
    dir.listDir();
    dir.sort();

    message = dir.isDirectory()? "directoryIN found, looking in: "+filePath:"error: directory not found. Change path in config.xml";
    
    for(int i = 0 ; i<dir.size();i++){
        fileNames.push_back(dir.getPath(i));
    }
    
    
    string pathOut = filePathOut;
    ofDirectory dirOut(pathOut);
    
    dirOut.allowExt("wav");
    dirOut.listDir();
    dirOut.sort();
    
    messageOut = dir.isDirectory()? "directoryOUT found, looking in: "+filePathOut:"error: directory not found. Change path in config.xml";
    
    for(int i = 0 ; i<dirOut.size();i++){
        fileNamesOut.push_back(dirOut.getPath(i));
    }
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    loadStrings();
    
    if(key=='+')masterVol+=0.1;
    if(key=='-')masterVol-=0.1;
    
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
