#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Utilities.h"

#include "ciImage.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ImageSampleApp : public App {
  public:
	void setup() override;
	void update() override;
	void draw() override;
    void keyDown(KeyEvent event) override;
    
    coc::Rect imageRect;
    coc::ciImageRef image;
};

void ImageSampleApp::setup() {

    gl::TextureRef texture = gl::Texture::create(loadImage(getAssetPath("jaws.jpg")));
    image = coc::ciImage::create(texture);
    image->setInset(42);
}

void ImageSampleApp::update() {
    
    int windowW = getWindowWidth();
    int windowH = getWindowHeight();
    int windowSizeMin = coc::min(windowW, windowH);
    imageRect = coc::Rect(0, 0, windowW, windowH);
    imageRect.grow(-windowSizeMin * 0.1);
    
    image->setPos(imageRect.getUpperLeft());
    image->setSize(imageRect.getSize());
    image->update();
}

void ImageSampleApp::draw() {
	
    gl::clear(ColorA(0.1,0.1,0.1,1));
    
    image->draw();
    
    gl::color(1, 0, 0);
    gl::drawStrokedRect(imageRect);
    gl::color(1, 1, 1);
}

void ImageSampleApp::keyDown(KeyEvent event) {

    if(event.getChar() == '1') {
    
        int scaleMode = (image->getScaleMode() + 1) % 3;
        image->setScaleMode((coc::Image::ScaleMode)scaleMode);
    
    } else if(event.getChar() == '2') {
    
        int crop = (image->getCrop() + 1) % 3;
        image->setCrop((coc::Image::Crop)crop);
    }
}

CINDER_APP( ImageSampleApp, RendererGl )
