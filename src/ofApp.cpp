#include "ofApp.h"
#include "ofxCv.h"
#include "opencv/cv.h"
#include "saliencySpecializedClasses.hpp"

using namespace std;
using namespace cv;
using namespace saliency;

//--------------------------------------------------------------
void ofApp::setup(){
  inputOfImg.load("test.jpg");
  inputOfImg.update();
  
  image = ofxCv::toCv(inputOfImg);
  Ptr<StaticSaliencySpectralResidual> saliencyAlgorithm = StaticSaliencySpectralResidual::create();
//  cv::Ptr<Saliency> saliencyAlgorithm = Saliency::create( saliency_algorithm );
  saliencyAlgorithm->computeSaliency( image, saliencyMap );

  ofxCv::toOf(saliencyMap, outputOfImg);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

  outputOfImg.draw(0,0);
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
