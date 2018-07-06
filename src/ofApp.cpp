#include "ofApp.h"
#include "ofxCv.h"
#include "opencv/cv.h"
#include "saliencySpecializedClasses.hpp"

using namespace std;
using namespace cv;
using namespace saliency;

//--------------------------------------------------------------
void ofApp::setup(){
  
  // 画像の読み込み
  inputOfImg.load("test.jpg");
  inputOfImg.update();
  
  // Mat変換
  image = ofxCv::toCv(inputOfImg);
  
  // SPECTRAL_RESIDUAL(顕著性マップを求めるアルゴリズム)
  Ptr<StaticSaliencySpectralResidual> saliencyAlgorithm = StaticSaliencySpectralResidual::create();
  
  // 顕著性マップに変換
  saliencyAlgorithm->computeSaliency( image, saliencyMap );
  
  // 顕著性マップに変換
  if (saliencyAlgorithm->computeSaliency( image, saliencyMap )) {
    // SPECTRAL_RESIDUAL(バイナリマップ)
    StaticSaliencySpectralResidual spec;
    spec.computeBinaryMap( saliencyMap, binaryMap );
  }

  // 画像(ofImage)に変換
  ofxCv::toOf(saliencyMap, outputOfImg);
  ofxCv::toOf(binaryMap, outputOfImg2);
  
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  // 出力
  inputOfImg.draw(0, 0, 200, 200);
  outputOfImg.draw(200, 0, 200, 200);
  outputOfImg2.draw(400, 0, 200, 200);
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
