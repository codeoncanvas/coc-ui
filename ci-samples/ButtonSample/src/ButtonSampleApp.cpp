#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Utilities.h"

#include "ciButton.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ButtonSampleApp : public App {
  public:
	void setup() override;
	void update() override;
	void draw() override;
    
    void mouseMove( MouseEvent event ) override;
    void mouseDown( MouseEvent event ) override;
    void mouseDrag( MouseEvent event ) override;
	void mouseUp( MouseEvent event ) override;
    void keyDown( KeyEvent event ) override;
    
    void addButtonEvent(std::string event);
    void addMouseEvent(std::string eventType, MouseEvent event);
    
    coc::ciButton button;
    std::vector<std::string> buttonEvents;
    std::vector<std::string> mouseEvents;
};

void ButtonSampleApp::setup() {
    
    int sw = getWindowWidth();
    int sh = getWindowHeight();
    
    int w = coc::min(sw, sh) * 0.5;
    int h = w;
    int x1 = (sw - w) * 0.5;
    int y1 = (sh - w) * 0.5;
    int x2 = x1 + w;
    int y2 = y1 + h;
    
    button.setRect(Rectf(x1, y1, x2, y2));
}

void ButtonSampleApp::update() {
    button.update();
    
    // below are button states which can be used to do different things.
    
    if(button.movedInside()) {
        addButtonEvent("moved_IN");
    }
    if(button.movedOutside()) {
        addButtonEvent("moved_OUT");
    }
    if(button.pressedInside()) {
        addButtonEvent("pressed_IN");
    }
    if(button.pressedOutside()) {
        addButtonEvent("pressed_OUT");
    }
    if(button.draggedInside()) {
        addButtonEvent("dragged_IN");
    }
    if(button.draggedOutside()) {
        addButtonEvent("dragged_OUT");
    }
    if(button.releasedInside()) {
        addButtonEvent("released_IN");
    }
    if(button.releasedOutside()) {
        addButtonEvent("released_OUT");
    }
}

void ButtonSampleApp::draw() {
	
    gl::clear( Color( 0, 0, 0 ) );
    
    gl::color(ColorA(0.1, 0.1, 0.1, 1.0)); // default color.
    if(button.over()) {
        gl::color(ColorA(0.5, 0.5, 1.0, 1.0)); // over color.
    }
    if(button.down()) {
        gl::color(ColorA(1.0, 0.5, 0.5, 1.0)); // down color;
    }
    gl::drawSolidRect(button.getRect());
    
    gl::color(ColorA(0.5, 0.5, 0.5, 1.0));
    gl::drawStrokedRect(button.getRect());
    
    gl::color(ColorA(1, 1, 1, 1));
    
    for(int i=0; i<buttonEvents.size(); i++) {
        gl::drawString(buttonEvents[i], vec2(getWindowWidth() - 140, 10 + i * 14));
    }
    for(int i=0; i<mouseEvents.size(); i++) {
        gl::drawString(mouseEvents[i], vec2(5, 10 + i * 14));
    }
}

void ButtonSampleApp::mouseMove( MouseEvent event ) {
    addMouseEvent("mouseMove", event);
    button.pointMoved(event.getX(), event.getY());
}

void ButtonSampleApp::mouseDown( MouseEvent event ) {
    addMouseEvent("mouseDown", event);
    button.pointPressed(event.getX(), event.getY());
}

void ButtonSampleApp::mouseDrag( MouseEvent event ) {
    addMouseEvent("mouseDrag", event);
    button.pointDragged(event.getX(), event.getY());
}

void ButtonSampleApp::mouseUp( MouseEvent event ) {
    addMouseEvent("mouseUp", event);
    button.pointReleased(event.getX(), event.getY());
}

void ButtonSampleApp::keyDown( KeyEvent event ) {

    // here are some other user cases.
    // where sometimes multiple events come through on the same frame,
    // or when win10 touch events don't fire when they should.

    int cx = getWindowWidth() * 0.5;
    int cy = getWindowHeight() * 0.5;

    if(event.getChar() == '1') {
        button.pointPressed(cx, cy);
    }
    
    if(event.getChar() == '2') { // test mouse moving in/out over button on the same frame.
        button.pointMoved(cx, cy);
        button.pointMoved(0, 0);
    }
}

void ButtonSampleApp::addButtonEvent(std::string event) {
    std::string str = toString(getElapsedFrames()) + ": " + event;
    buttonEvents.push_back(str);
    
    int maxNum = 30;
    if(buttonEvents.size() > maxNum) {
        int numToRemove = buttonEvents.size() - maxNum;
        buttonEvents.erase(buttonEvents.begin(), buttonEvents.begin() + numToRemove);
    }
}

void ButtonSampleApp::addMouseEvent(std::string eventType, MouseEvent event) {
    std::string str = toString(getElapsedFrames()) + ": " + eventType + " x=" + toString(event.getX()) + " y= " + toString(event.getY());
    mouseEvents.push_back(str);
    
    int maxNum = 30;
    if(mouseEvents.size() > maxNum) {
        int numToRemove = mouseEvents.size() - maxNum;
        mouseEvents.erase(mouseEvents.begin(), mouseEvents.begin() + numToRemove);
    }
}

CINDER_APP( ButtonSampleApp, RendererGl )
