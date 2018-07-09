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
  Mat m = ofxCv::toCv(p);
  saliencyAlgorithm_BinWangApr2014.dynamicCast<MotionSaliencyBinWangApr2014>()->setImagesize( m.cols, m.rows );
  saliencyAlgorithm_BinWangApr2014.dynamicCast<MotionSaliencyBinWangApr2014>()->init();
}

//--------------------------------------------------------------
void ofApp::update(){
  player.update();
  
  if(player.isFrameNew()){
    // 1フレームを取得
    ofPixelsRef pix = player.getPixels();
    // Mat変換
    Mat mat = ofxCv::toCv(pix).clone();
    // 白黒加工
    cvtColor( mat, mat, COLOR_BGR2GRAY );
    // 画像(ofImage)に変換
    ofxCv::toOf( mat, outputOfImg4 );
    outputOfImg4.update();
    
    // 顕著性マップ(BinWangApr2014)に変換開始
    Mat mat_gray = mat.clone();
    // 顕著性マップ(BinWangApr2014)に変換
    saliencyAlgorithm_BinWangApr2014->computeSaliency( mat_gray, saliencyMap_BinWangApr2014 );
    // アルファチャンネルの正規化を行う
    normalize( saliencyMap_BinWangApr2014, saliencyMap_BinWangApr2014, 0.0f, 255.0f );
    // Matの型（ビット深度）を変換する
    saliencyMap_BinWangApr2014.convertTo( saliencyMap_BinWangApr2014, CV_8UC3 );

  }
  
}

//--------------------------------------------------------------
void ofApp::draw(){
  // 出力（画像）
  inputOfImg.draw( 0, 0, 250, 300 );
  outputOfImg.draw( 250, 0, 250, 300 );
  outputOfImg2.draw( 500, 0, 250, 300 );
  outputOfImg3.draw( 750, 0, 250, 300 );
  
  // 出力（動画）
  player.draw(0, 300, 300, 200);
  outputOfImg4.draw( 300, 300, 300, 200 );

  // 顕著性マップ(BinWangApr2014)を出力
  ofxCv::drawMat(saliencyMap_BinWangApr2014, 600, 300, 300, 200);
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
