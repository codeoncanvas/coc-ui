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
        string alignmentStr = "Center";
        if(image->getAlignment() == coc::Image::AlignmentTopLeft) {
            alignmentStr = "TopLeft";
        } else if(image->getAlignment() == coc::Image::AlignmentTopCenter) {
            alignmentStr = "TopCenter";
        } else if(image->getAlignment() == coc::Image::AlignmentTopRight) {
            alignmentStr = "TopRight";
        } else if(image->getAlignment() == coc::Image::AlignmentBottomLeft) {
            alignmentStr = "BottomLeft";
        } else if(image->getAlignment() == coc::Image::AlignmentBottomCenter) {
            alignmentStr = "BottomCenter";
        } else if(image->getAlignment() == coc::Image::AlignmentBottomRight) {
            alignmentStr = "BottomRight";
        } else if(image->getAlignment() == coc::Image::AlignmentLeftCenter) {
            alignmentStr = "LeftCenter";
        } else if(image->getAlignment() == coc::Image::AlignmentRightCenter) {
            alignmentStr = "RightCenter";
        }
    
        string scaleStr = "None";
        if(image->getScale() == coc::Image::ScaleStretch) {
            scaleStr = "Stretch";
        } else if(image->getScale() == coc::Image::ScaleFit) {
            scaleStr = "Fit";
        } else if(image->getScale() == coc::Image::ScaleFill) {
            scaleStr = "Fill";
        }
        
        string cropStr = "None";
        if(image->getCrop() == coc::Image::CropRect) {
            cropStr = "Rect";
        } else if(image->getCrop() == coc::Image::CropCircle) {
            cropStr = "Circle";
        }
        
        string insetStr = toString(image->getInsetMin()) + " px";
        
        gl::color(1, 0, 0);
        gl::drawStrokedRect(imageRect);
        
        gl::color(0,0,0,0.5);
        gl::drawSolidRect(Rectf(glm::vec2(0,0), glm::vec2(150, 150)));

        int textX = 10;
        int textY = 15;
        int lineH = 20;
        
        gl::color(1, 1, 1);
        gl::drawString("Resize window.", glm::vec2(textX, textY));
        gl::drawString("Use keyboard shortcuts,", glm::vec2(textX, textY+=lineH));
        gl::drawString("(1) Alignment: " + alignmentStr, glm::vec2(textX, textY+=lineH));
        gl::drawString("(2) Scale: " + scaleStr, glm::vec2(textX, textY+=lineH));
        gl::drawString("(3) Crop: " + cropStr, glm::vec2(textX, textY+=lineH));
        gl::drawString("(4) Inset: " + insetStr, glm::vec2(textX, textY+=lineH));
        
        gl::color(1, 1, 1);
    }
}

void ImageSampleApp::keyDown(KeyEvent event) {

    char key = event.getChar();

    if(key == '1') {
    
        int alignment = (image->getAlignment() + 1) % (int)coc::Image::AlignmentTotal;
        image->setAlignment((coc::Image::Alignment)alignment);
    
    } else if(key == '2') {
    
        int scale = (image->getScale() + 1) % (int)coc::Image::ScaleTotal;
        image->setScale((coc::Image::Scale)scale);
    
    } else if(key == '3') {
    
        int crop = (image->getCrop() + 1) % (int)coc::Image::CropTotal;
        image->setCrop((coc::Image::Crop)crop);
        
    } else if(key == '4') {
    
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
