#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "saliencySpecializedClasses.hpp"

using namespace std;
using namespace cv;
using namespace saliency;

class ofApp : public ofBaseApp {

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

  // 元データ
  ofImage inputOfImg;
  // 出力データ
  ofImage outputOfImg, outputOfImg2, outputOfImg3;
  
  // 画像関連のデータ
  Mat image;
  Mat saliencyMap_SPECTRAL_RESIDUAL, binaryMap_SPECTRAL_RESIDUAL;
  Mat saliencyMap_FINE_GRAINED, binaryMap_FINE_GRAINED;
  
  // SPECTRAL_RESIDUAL(顕著性マップを求めるアルゴリズム)
  Ptr<StaticSaliencySpectralResidual> saliencyAlgorithm_SPECTRAL_RESIDUAL = StaticSaliencySpectralResidual::create();
  // FINE_GRAINED(顕著性マップを求めるアルゴリズム)
  Ptr<StaticSaliencyFineGrained> saliencyAlgorithm_FINE_GRAINED = StaticSaliencyFineGrained::create();

};
