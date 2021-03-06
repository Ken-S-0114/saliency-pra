#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  
  // 画像の読み込み
  inputOfImg.load("test.jpg");
  inputOfImg.update();
  
  // 動画の読み込み
  ofBackground(255,255,255);
  ofSetVerticalSync(true);
  player.load("test.mp4");
  player.play();
  
  // Mat変換
  image = ofxCv::toCv( inputOfImg );
  cvtColor(image, image, COLOR_BGR2GRAY);
  
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
    outputOfImg3.update();
  }
  
  // 顕著性マップ(BinWangApr2014)の設定
  ofPixelsRef p = player.getPixels();
  Mat m = ofxCv::toCv(p).clone();
  
  saliencyAlgorithm_BinWangApr2014.dynamicCast<MotionSaliencyBinWangApr2014>()->setImagesize( m.cols, m.rows );
  saliencyAlgorithm_BinWangApr2014.dynamicCast<MotionSaliencyBinWangApr2014>()->init();
  
  ofLog()<<"m_cols : "<<m.cols;
  ofLog()<<"m_rows : "<<m.rows;
  
  
}

//--------------------------------------------------------------
void ofApp::update(){
  player.update();
  
  if(player.isFrameNew()){
    // 1フレームを取得
//    ofPixelsRef pix = player.getPixels();
    // Mat変換
    Mat mat = ofxCv::toCv(player).clone();
    // 白黒加工
    cvtColor( mat, mat, COLOR_BGR2GRAY );
    
    // 顕著性マップ(BinWangApr2014)に変換
//    saliencyAlgorithm_BinWangApr2014->computeSaliency( mat.clone(), saliencyMap_BinWangApr2014 );
    
    saliencyAlgorithm_SPECTRAL_RESIDUAL->computeSaliency( mat.clone(), saliencyMap_BinWangApr2014 );
    
    ofLog()<<"saliencyMap_BinWangApr2014_cols : "<< saliencyMap_BinWangApr2014.cols;
    ofLog()<<"saliencyMap_BinWangApr2014_rows : "<< saliencyMap_BinWangApr2014.rows;
    ofLog()<<"saliencyMap_BinWangApr2014_type : "<< saliencyMap_BinWangApr2014.type();
    ofLog()<<"BinWangApr2014_at : "<<(int)saliencyMap_BinWangApr2014.at<uchar>(0,0);
    
    // アルファチャンネルの正規化を行う
    normalize( saliencyMap_BinWangApr2014.clone(), saliencyMap_BinWangApr2014_norm, 0.0, 255.0, NORM_MINMAX);
    
    ofLog()<<"正規化 : "<<(int)saliencyMap_BinWangApr2014_norm.at<uchar>(0,0);
    
    // Matの型（ビット深度）を変換する
    saliencyMap_BinWangApr2014_norm.convertTo( saliencyMap_BinWangApr2014_conv, CV_8UC3 );
    ofLog()<<"Matの型 : "<<(double)saliencyMap_BinWangApr2014_conv.at<double>(0,0);
//    ofxCv::toOf( saliencyMap_BinWangApr2014_3, outputOfImg5 );
    
  }
  
}

//--------------------------------------------------------------
void ofApp::draw(){
  // 出力（画像）
  inputOfImg.draw( 0, 50, 250, 300 );
  outputOfImg.draw( 250, 50, 250, 300 );
  outputOfImg2.draw( 500, 50, 250, 300 );
  outputOfImg3.draw( 750, 50, 250, 300 );

  // 出力（動画）
  player.draw( 0, 350, 500, 350);

  // 顕著性マップ(BinWangApr2014)を出力
//  ofxCv::drawMat( saliencyMap_BinWangApr2014_conv, 500, 350, 500, 350 );
  ofxCv::drawMat(saliencyMap_BinWangApr2014_conv, 500, 350, 500, 350);
  
//  outputOfImg5.save("output.jpg");
  
  // FPS表示
  ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 20, 20);

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
