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
    bool bDebug;
};

void ImageSampleApp::setup() {

    bDebug = true;

    gl::TextureRef texture = gl::Texture::create(loadImage(getAssetPath("jaws.jpg")));
    image = coc::ciImage::create(texture);
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
    
    if(bDebug) {
        string scaleStr = "None";
        if(image->getScaleType() == coc::Image::ScaleModeFit) {
            scaleStr = "Fit";
        } else if(image->getScaleType() == coc::Image::ScaleModeFill) {
            scaleStr = "Fill";
        }
        
        string cropStr = "None";
        if(image->getCropType() == coc::Image::CropRect) {
            cropStr = "Rect";
        } else if(image->getCropType() == coc::Image::CropCircle) {
            cropStr = "Circle";
        }
        
        string insetStr = toString(image->getInsetMin()) + " px";
        
        gl::color(1, 0, 0);
        gl::drawStrokedRect(imageRect);
        
        gl::color(0,0,0,0.5);
        gl::drawSolidRect(Rectf(glm::vec2(0,0), glm::vec2(150, 100)));

        int textX = 10;
        int textY = 15;
        int lineH = 20;
        
        gl::color(1, 1, 1);
        gl::drawString("Keyboard shortcuts", glm::vec2(textX, textY));
        gl::drawString("(1) Scale: " + scaleStr, glm::vec2(textX, textY+=lineH));
        gl::drawString("(2) Crop: " + cropStr, glm::vec2(textX, textY+=lineH));
        gl::drawString("(3) Inset: " + insetStr, glm::vec2(textX, textY+=lineH));
        
        gl::color(1, 1, 1);
    }
}

void ImageSampleApp::keyDown(KeyEvent event) {

    char key = event.getChar();

    if(key == '1') {
    
        int scaleType = (image->getScaleType() + 1) % 3;
        image->setScaleType((coc::Image::ScaleType)scaleType);
    
    } else if(key == '2') {
    
        int cropType = (image->getCropType() + 1) % 3;
        image->setCropType((coc::Image::CropType)cropType);
        
    } else if(key == '3') {
    
        float inset = image->getInsetMin();
        if(inset == 0) {
            // inset of 42px into the original image
            // this is the inset of the gold frame in the jaws.jpg
            image->setInset(42);
        } else {
            image->setInset(0); // disable inset.
        }
        
    } else if(key == 'd' || key == 'D') {
    
        bDebug = !bDebug;
    }
}

CINDER_APP( ImageSampleApp, RendererGl )
