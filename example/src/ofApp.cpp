#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    searchQuery = "mushroom";
    
    ofSetWindowTitle( "ofxOpenclipart | Press spacebar to search" );

    svgLoaded = false;
    
    ofFbo::Settings s;
    s.width = ofGetWidth();
    s.height = ofGetHeight();
    
    fbo.allocate( s );
    
}

//--------------------------------------------------------------
void ofApp::update()
{
    if ( openclipart.isFinishedLoading() ) {
        if ( !svgLoaded ) {
            
            vector<string> fileNames = openclipart.getFileNames();
            
            // Just load the SVG files in the update() method for now.
            // This could also be done in a separate thread,
            // but it ususally takes less than a second to load the SVG
            // files from the disk.
            
            cout << "LOADING SVG FILES" << endl;
            cout << "START: " << ofGetElapsedTimef() << endl;
            
            for ( int i = 0; i < fileNames.size(); i++ ) {
            
                ofxSVG svg;
                svg.load( fileNames[ i ] );
            
                svgFiles.push_back( svg );
                
            }
            
            cout << "END: "  << ofGetElapsedTimef() << endl;
            cout << "Number of files loaded: " << svgFiles.size() << endl;
            
            svgLoaded = true;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground( 128 );
    
    if ( !svgLoaded ) {
    
        string msg = "Openclipart is finished loading: " + ofToString( openclipart.isFinishedLoading() );
        ofDrawBitmapString( msg, 20, 20 );
    
    } else {
        
        // Draw a random SVG file every 10 frames
        
        if ( ofGetFrameNum() % 10 == 0 ) {
        
            fbo.begin();
            
            int randomSVG = ofRandom( svgFiles.size() );
            
            cout << "Random SVG: " << randomSVG << endl;
            
            ofPushMatrix();
            ofTranslate( ofRandom( fbo.getWidth() ), ofRandom( fbo.getHeight() ) );
            ofRotate( ofRandom( 360 ) );
            
            float scaleFactor = 1.0f;
            
            float w = svgFiles[ randomSVG ].getWidth();
            if ( w > 150 ) {
                scaleFactor = 1.0f / ( w / 150.0f );
            }
            ofScale( scaleFactor, scaleFactor );
            
            svgFiles[ randomSVG ].draw();
            ofPopMatrix();
            
            fbo.end();
        
        }
        
        ofSetColor( 255 );
        fbo.draw( 0, 0 );

    }
}

//--------------------------------------------------------------
void ofApp::keyPressed( int key )
{
    if ( key == ' ' ) {
        
        // Set the amount of SVG files you want to load
        // Maximum is 200, but this may take a long time
        // If you don't use this method, the API will return 10 items
        
        openclipart.setAmount( 20 );
        
        // Set the sort method.
        // Possible options are: date, downloads, favorites
        // If you don't use this method, the API will sort on downloads
        
        openclipart.setSortMethod("favorites");
        
        openclipart.search( searchQuery );
        ofSetWindowTitle( "ofxOpenclipart | Searching for \"" + searchQuery + "\"" );
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{

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
