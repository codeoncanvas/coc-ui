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

#include "cocButton.h"

namespace coc {

Button::Button(coc::Rect rectNew) {

    rect = rectNew;
    bEnabled = true;
    bEnabledChanged = false;
    bUseHandlers = false;
    bUpdateAsync = false;
    bRegisterEvents = false;

    bOver = false;
    bOverChanged = false;
    bDown = false;
    bDownChanged = false;
    
    bMovedInside = false;
    bMovedOutside = false;
    bPressedInside = false;
    bPressedOutside = false;
    bDraggedInside = false;
    bDraggedOutside = false;
    bReleasedInside = false;
    bReleasedOutside = false;
}

Button::~Button() {
    setRegisterEvents(false); // unregister events on destructor.
}

//--------------------------------------------------------------
ButtonRef Button::create(const coc::Rect & rect) {
    ButtonRef button(new Button(rect));
    return button;
}

//--------------------------------------------------------------
void Button::setRect(coc::Rect value) {
    rect = value;
}

void Button::setRect(float x, float y, float w, float h) {
    coc::Rect r;
    r.setX(x);
    r.setY(y);
    r.setW(w);
    r.setH(h);
    setRect(r);
}

const coc::Rect & Button::getRect() const {
    return rect;
}

//--------------------------------------------------------------
void Button::setEnabled(bool value) {
    bEnabledChanged = bEnabled != value;
    bEnabled = value;
}

void Button::setUseHandlers(bool value) {
    bUseHandlers = value;
}

void Button::setUpdateAsync(bool value) {
    bUpdateAsync = value;
}

void Button::setRegisterEvents(bool value) {
    if(bRegisterEvents == value) {
        return;
    }

    bRegisterEvents = value;
    if(bRegisterEvents == true) {
        handleEventRegister();
    } else {
        handleEventUnregister();
    }
}

//--------------------------------------------------------------
void Button::moveTo( int x, int y ) {
    rect.setX(x);
    rect.setY(y);
}

void Button::moveCenterTo( int x, int y ) {
    rect.setX(x - rect.getW()/2);
    rect.setY(y - rect.getH()/2);
}

//--------------------------------------------------------------
const glm::ivec2 & Button::getPointPosLast() const {
    return pointPos;
}

//--------------------------------------------------------------
void Button::reset() {

    bOver = false;
    bOverChanged = false;
    bDown = false;
    bDownChanged = false;
    
    bMovedInside = false;
    bMovedOutside = false;
    bPressedInside = false;
    bPressedOutside = false;
    bDraggedInside = false;
    bDraggedOutside = false;
    bReleasedInside = false;
    bReleasedOutside = false;
    
    points.clear();
}

//--------------------------------------------------------------
void Button::update() {

    bOverChanged = false;
    bDownChanged = false;
    
    bMovedInside = false;
    bMovedOutside = false;
    bPressedInside = false;
    bPressedOutside = false;
    bDraggedInside = false;
    bDraggedOutside = false;
    bReleasedInside = false;
    bReleasedOutside = false;
    
    //----------------------------------------------------------
    // when enabling / disabling the button,
    // it must be reset so all state information is cleared.
    
    bool bReset = false;
    bReset = bReset || bEnabledChanged;
    if(bReset) {
        reset();
    }
    bEnabledChanged = false;

    //----------------------------------------------------------
    for(int i=0; i<points.size(); i++) {
        ButtonPoint & point = points[i];
        
        bool bOverNew = rect.isInside(point.pos.x, point.pos.y);
        bOverChanged = (bOver != bOverNew);
        if(bOverChanged) {
            bOver = bOverNew;
        }
        
        if(point.type == ButtonPoint::Type::Moved) {
            
            if(bOver && bOverChanged && !bDown) {
                bMovedInside = true;
            }
            if(!bOver && bOverChanged && !bDown) {
                bMovedOutside = true;
            }
        
        } else if(point.type == ButtonPoint::Type::Pressed) {
        
            bool bDownNew = bOver;
            bDownChanged = (bDown != bDownNew);
            if(bDownChanged) {
                bDown = bDownNew;
            }
            
            if(bDown && bDownChanged) {
                bPressedInside = true;
            }
            if(!bDown) {
                bPressedOutside = true;
            }
            
        } else if(point.type == ButtonPoint::Type::Dragged) {
        
            if(bDown && bOverChanged && bOver) {
                bDraggedInside = true;
            }
            if(bDown && bOverChanged && !bOver) {
                bDraggedOutside = true;
            }
        
        } else if(point.type == ButtonPoint::Type::Released) {

            bool bDownNew = false;
            bDownChanged = (bDown != bDownNew);
            if(bDownChanged) {
                bDown = bDownNew;
            }
        
            if(!bDown && bDownChanged && bOver) {
                bReleasedInside = true;
            }
            if(!bDown && bDownChanged && !bOver) {
                bReleasedOutside = true;
            }
        }
        
        pointPos = point.pos; // save last point position.
    }
    
    points.clear();
    
    //----------------------------------------------------------
    if(bUseHandlers == false) {
        return;
    }

    if(movedInside()) {
        handleMovedInside();
    }
    if(movedOutside()) {
        handleMovedOutside();
    }
    if(pressedInside()) {
        handlePressedInside();
    }
    if(pressedOutside()) {
        handlePressedOutside();
    }
    if(draggedInside()) {
        handleDraggedInside();
    }
    if(draggedOutside()) {
        handleDraggedOutside();
    }
    if(releasedInside()) {
        handleReleasedInside();
    }
    if(releasedOutside()) {
        handleReleasedOutside();
    }
}

bool Button::over() const {
    return bOver;
}

bool Button::overChanged() const {
    return bOverChanged;
}

bool Button::down() const {
    return bDown;
}

bool Button::downChanged() const {
    return bDownChanged;
}

//--------------------------------------------------------------
bool Button::movedInside() const {
    return bMovedInside;
}

bool Button::movedOutside() const {
    return bMovedOutside;
}

bool Button::pressedInside() const {
    return bPressedInside;
}

bool Button::pressedOutside() const {
    return bPressedOutside;
}

bool Button::draggedInside() const {
    return bDraggedInside;
}

bool Button::draggedOutside() const {
    return bDraggedOutside;
}

bool Button::releasedInside() const {
    return bReleasedInside;
}

bool Button::releasedOutside() const {
    return bReleasedOutside;
}

//--------------------------------------------------------------
void Button::pointMoved(int x, int y) {
    if(bEnabled == false) {
        return;
    }
    
    pointNew(ButtonPoint::Type::Moved, x, y);
    
    if(bUpdateAsync) {
        update();
    }
}

void Button::pointPressed(int x, int y) {
    if(bEnabled == false) {
        return;
    }
    
    pointNew(ButtonPoint::Type::Pressed, x, y);
    
    if(bUpdateAsync) {
        update();
    }
}

void Button::pointDragged(int x, int y) {
    if(bEnabled == false) {
        return;
    }

    pointNew(ButtonPoint::Type::Dragged, x, y);
    
    if(bUpdateAsync) {
        update();
    }
}

void Button::pointReleased(int x, int y) {
    if(bEnabled == false) {
        return;
    }
    
    pointNew(ButtonPoint::Type::Released, x, y);
    
    if(bUpdateAsync) {
        update();
    }
}

void Button::pointNew(ButtonPoint::Type type, int x, int y) {
    points.push_back(ButtonPoint());
    ButtonPoint & point = points.back();
    point.type = type;
    point.pos = glm::ivec2(x, y);
}

}
