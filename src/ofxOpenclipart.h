//
//  ofxOpenClipart.h
//
//  Created by Jan on 18/01/2018.
//

#pragma once

#include "ofMain.h"
#include "ofxJSON.h"

class ofxOpenclipart : public ofThread
{
    
public:
    
    ofxOpenclipart();
    ~ofxOpenclipart();
    
    void search( string _searchString );
    
    ofThreadChannel<string> channel;
    ofThreadChannel<bool> channelReady;
    
    void threadedFunction();
    
    bool isFinishedLoading();
    
    vector<string> getFileNames();
    
    void setAmount( int _amount );
    
    void setSortMethod( string _method );
    
private:
    
    string baseURL;
    
    bool finishedLoading;

    vector<string> fileNames;

    int amount; // Maximum 200
    string sortMethod; // date, downloads, favorites
    
};
