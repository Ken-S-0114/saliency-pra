#include "ofApp.h"
#include "ofxCv.h"
#include "opencv/cv.h"
#include "saliencySpecializedClasses.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;
using namespace saliency;

//--------------------------------------------------------------
void ofApp::setup(){
  
  // 画像の読み込み
  inputOfImg.load("test.jpg");
  inputOfImg.update();
  
  // 動画の読み込み
//  ofBackground(255,255,255);
//  ofSetVerticalSync(true);
  player.load("test.mp4");
  player.play();
  
  // Mat変換
  image = ofxCv::toCv( inputOfImg );
  
  // 顕著性マップ(SPECTRAL_RESIDUAL)に変換
  if (saliencyAlgorithm_SPECTRAL_RESIDUAL->computeSaliency( image, saliencyMap_SPECTRAL_RESIDUAL )) {
    
    // SPECTRAL_RESIDUAL(バイナリマップ)
    StaticSaliencySpectralResidual spec;
    spec.computeBinaryMap( saliencyMap_SPECTRAL_RESIDUAL, binaryMap_SPECTRAL_RESIDUAL );
    
    // 画像(ofImage)に変換
    ofxCv::toOf( saliencyMap_SPECTRAL_RESIDUAL, outputOfImg );
    ofxCv::toOf( binaryMap_SPECTRAL_RESIDUAL, outputOfImg2 );
    outputOfImg2.update();
  }
  
  // 顕著性マップ(FINE_GRAINED)に変換
  if (saliencyAlgorithm_FINE_GRAINED->computeSaliency( image, saliencyMap_FINE_GRAINED )) {
    // 画像(ofImage)に変換
    ofxCv::toOf( saliencyMap_FINE_GRAINED, outputOfImg3 );
    //    outputOfImg3.update();
  }
  
}

//--------------------------------------------------------------
void ofApp::update(){
  player.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
  // 出力
  inputOfImg.draw( 0, 0, 250, 300 );
  outputOfImg.draw( 250, 0, 250, 300 );
  outputOfImg2.draw( 500, 0, 250, 300 );
  outputOfImg3.draw( 750, 0, 250, 300 );
  player.draw(0, 300, 500, 300);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  switch(key){
    case 'f':
      // 連続再生 or フレームごとの再生
      player.setPaused(!player.isPaused());
      break;
    case OF_KEY_LEFT:
      // 前フレームの表示
      player.previousFrame();
      break;
    case OF_KEY_RIGHT:
      // 次のフレームの表示
      player.nextFrame();
      break;
  }
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
