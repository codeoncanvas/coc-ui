/**
 *
 *      ┌─┐╔═╗┌┬┐┌─┐
 *      │  ║ ║ ││├┤
 *      └─┘╚═╝─┴┘└─┘
 *   ┌─┐┌─┐╔╗╔┬  ┬┌─┐┌─┐
 *   │  ├─┤║║║└┐┌┘├─┤└─┐
 *   └─┘┴ ┴╝╚╝ └┘ ┴ ┴└─┘
 *
 * Copyright (c) 2014-2016 Code on Canvas Pty Ltd, http://CodeOnCanvas.cc
 *
 * This software is distributed under the MIT license
 * https://tldrlegal.com/license/mit-license
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code
 *
 **/

#include "cocScrollbar.h"

namespace coc {

//--------------------------------------------------------------
Scrollbar::Scrollbar():
type(Type::Vertical),
position(0.0),
contentRatio(0.5),
ease(0.0),
thumbOffset(0.0),
bThumbPressed(false),
bPositionChangeInternal(false),
bPositionChangeExternal(false) {
    //
}

Scrollbar::~Scrollbar() {
    //
}

//--------------------------------------------------------------
ScrollbarRef Scrollbar::create() {
    ScrollbarRef scrollbar = ScrollbarRef(new Scrollbar());
    scrollbar->setup();
    return scrollbar;
}

void Scrollbar::setup() {
    track = initButton();
    thumb = initButton();
}

//--------------------------------------------------------------
void Scrollbar::setType(coc::Scrollbar::Type value) {
    type = value;
}

coc::Scrollbar::Type Scrollbar::getType() const {
    return type;
}

//--------------------------------------------------------------
void Scrollbar::setRect(coc::Rect value) {
    rect = value;
}

const coc::Rect & Scrollbar::getRect() const {
    return rect;
}

//--------------------------------------------------------------
void Scrollbar::setContentRatio(float value) {
    contentRatio = value;
}

float Scrollbar::getContentRatio() const {
    return contentRatio;
}

//--------------------------------------------------------------
void Scrollbar::setThumbOffset(float value) {
    thumbOffset = value;
}

float Scrollbar::getThumbOffset() const {
    return thumbOffset;
}

//--------------------------------------------------------------
void Scrollbar::setEase(float value) {
    ease = value;
}

float Scrollbar::getEase() const {
    return ease;
}

//--------------------------------------------------------------
void Scrollbar::setPosition(float value) {
    bPositionChangeExternal = (position != value);
    position = value;
}

float Scrollbar::getPosition() const {
    return position;
}

//--------------------------------------------------------------
void Scrollbar::setEnabled(bool value) {
    track->setEnabled(value);
    thumb->setEnabled(value);
}

//--------------------------------------------------------------
void Scrollbar::update() {

    bPositionChangeInternal = false;

    const coc::Rect & trackRect = rect;
    coc::Rect thumbRect = trackRect;
    
    if(type == Type::Vertical) {
    
        float trackRectY = trackRect.getY();
        float trackRectH = trackRect.getH();
        float thumbRectH = trackRectH * contentRatio;
        float thumbRectY = coc::map(position, 0.0, 1.0, trackRectY - thumbOffset, trackRectY + trackRectH - thumbRectH + thumbOffset, true);
        thumbRect.setH(thumbRectH);
        thumbRect.setY(thumbRectY);
        
    } else if(type == Type::Horizontal) {

        float trackRectX = trackRect.getX();
        float trackRectW = trackRect.getW();
        float thumbRectW = trackRectW * contentRatio;
        float thumbRectX = coc::map(position, 0.0, 1.0, trackRectX - thumbOffset, trackRectX + trackRectW - thumbRectW + thumbOffset, true);
        thumbRect.setW(thumbRectW);
        thumbRect.setX(thumbRectX);
    }
    
    track->setRect(trackRect);
    track->update();
    
    thumb->setRect(thumbRect);
    thumb->update();

    if(thumb->pressedInside()) {
        
        track->reset(); // when thumb is pressed, cancel events going down to the track.
        
        thumbPressStartPos.x = thumb->getRect().getX();
        thumbPressStartPos.y = thumb->getRect().getY();
        thumbPressInsidePos = thumb->getPointPosLast();
        bThumbPressed = true;
    
    } else if(thumb->releasedInside() || thumb->releasedOutside()) {
    
        bThumbPressed = false;
    }
    
    bool bTrackPressed = track->pressedInside();
    
    bool bUpdateThumbPos = false;
    bUpdateThumbPos = bUpdateThumbPos || bThumbPressed;
    bUpdateThumbPos = bUpdateThumbPos || bTrackPressed;
    
    if(bUpdateThumbPos) {
        
        const glm::ivec2 & thumbPressPos = thumb->getPointPosLast();
        const glm::ivec2 & trackPressPos = track->getPointPosLast();
        coc::Rect thumbRect = thumb->getRect();
        int thumbMin = 0;
        int thumbMax = 0;
        int thumbDrag = 0;
        int thumbPos = 0;
        float thumbPosNorm = 0;
        
        if(type == coc::Scrollbar::Type::Vertical) {
            
            if(bThumbPressed) {
                thumbDrag = thumbPressPos.y - thumbPressInsidePos.y;
                thumbPos = thumbPressStartPos.y + thumbDrag;
            } else if(bTrackPressed) {
                thumbPos = trackPressPos.y - (thumbRect.getH() * 0.5);
            }

            thumbMin = trackRect.getY();
            thumbMax = thumbMin + trackRect.getH() - thumbRect.getH();
            thumbPosNorm = coc::map(thumbPos, thumbMin, thumbMax, 0.0, 1.0, true);
            thumbPos = coc::map(thumbPosNorm, 0.0, 1.0, thumbMin - thumbOffset, thumbMax + thumbOffset);
            
            thumbRect.setY(thumbPos);
        
        } else if(type == coc::Scrollbar::Type::Horizontal) {
        
            if(bThumbPressed) {
                thumbDrag = thumbPressPos.x - thumbPressInsidePos.x;
                thumbPos = thumbPressStartPos.x + thumbDrag;
            } else if(bTrackPressed) {
                thumbPos = trackPressPos.x - (thumbRect.getW() * 0.5);
            }

            thumbMin = trackRect.getX();
            thumbMax = thumbMin + trackRect.getW() - thumbRect.getW();
            thumbPosNorm = coc::map(thumbPos, thumbMin, thumbMax, 0.0, 1.0, true);
            thumbPos = coc::map(thumbPosNorm, 0.0, 1.0, thumbMin - thumbOffset, thumbMax + thumbOffset);
            
            thumbRect.setX(thumbPos);
        }
        
        bPositionChangeInternal = (position != thumbPosNorm);
        position = thumbPosNorm;
        thumb->setRect(thumbRect);
    }
    
    bPositionChangeExternal = false;
}

//--------------------------------------------------------------
void Scrollbar::pointMoved(int x, int y) {
    track->pointMoved(x, y);
    thumb->pointMoved(x, y);
}

void Scrollbar::pointPressed(int x, int y) {
    track->pointPressed(x, y);
    thumb->pointPressed(x, y);
}

void Scrollbar::pointDragged(int x, int y) {
    track->pointDragged(x, y);
    thumb->pointDragged(x, y);
}

void Scrollbar::pointReleased(int x, int y) {
    track->pointReleased(x, y);
    thumb->pointReleased(x, y);
}

}
