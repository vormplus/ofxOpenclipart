//
//  ofxOpenclipart.cpp
//
//  Created by Jan on 18/01/2018.
//

#include "ofxOpenclipart.h"

// ----------------------------------------

ofxOpenclipart::ofxOpenclipart()
{
    startThread();
   
    finishedLoading = false;
    
    baseURL = "https://openclipart.org";
    
    amount = 0;
    sortMethod = "";
}

// ----------------------------------------

ofxOpenclipart::~ofxOpenclipart()
{
    channel.close();
    waitForThread( true );
}

// ----------------------------------------

void ofxOpenclipart::search( string _searchQuery )
{
    channel.send( _searchQuery );
}

// ----------------------------------------

void ofxOpenclipart::threadedFunction()
{
   
    string query;
    
    while ( channel.receive( query ) ) {
        
        // Remove filenames from previous searches
        fileNames.clear();
        
        finishedLoading = false;
        
        string url = baseURL + "/search/json/?query=" + query;
        
        if ( amount != 0 ) {
            url += "&amount=" + ofToString( amount );
        }
        
        if ( sortMethod != "" ) {
            if ( sortMethod == "downloads" || sortMethod == "favorites" || sortMethod == "date" ) {
                url += "&sort=" + sortMethod;
            }
        }
        
        ofxJSONElement response;
        
        if ( !response.open( url ) ) {
            
            cout << "Failed to open JSON" << endl;
        
        } else {
            
            int numberOfItems = response["payload"].size();
            
            for ( int i = 0; i < numberOfItems; i++ ) {
                
                string svgURL = response["payload"][ i ]["svg"]["url"].asString();

                string svgFileName = svgURL;
                svgFileName.erase( 0, 33 ); // Remove the URL name
                svgFileName = query + "/" + svgFileName; // Use the query as folder name
                
                // Check if the file exists on disk before loading it again from the server
               
                ofFile svgFile( ofToDataPath( svgFileName ) );
                
                if ( svgFile.exists() ) {
                    
                    fileNames.push_back( svgFileName );

                } else {

                    ofHttpResponse resp = ofLoadURL( svgURL );
                    
                    // Write the SVG file to the bin/data folder
                    ofFile newSVGFile;
                    newSVGFile.open( svgFileName, ofFile::WriteOnly );
                    newSVGFile << resp.data;
                    
                    fileNames.push_back( svgFileName );
                }
            }
            
            finishedLoading = true;
        }
        
    }
}

// ----------------------------------------

bool ofxOpenclipart::isFinishedLoading()
{
    return finishedLoading;
}

// ----------------------------------------

vector<string> ofxOpenclipart::getFileNames()
{
    return fileNames;
}

// ----------------------------------------

void ofxOpenclipart::setAmount( int _amount )
{
    amount = _amount;
}

// ----------------------------------------

void ofxOpenclipart::setSortMethod( string _method )
{
    sortMethod = _method;
}


