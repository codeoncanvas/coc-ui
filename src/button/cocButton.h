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

#pragma once

#include "cocCore.h"

namespace coc {

//--------------------------------------------------------------
struct ButtonPoint {

    enum Type {
        Undefined = 0,
        Moved,
        Pressed,
        Dragged,
        Released
    };
    
    ButtonPoint(Type type=Undefined, glm::ivec2 pos=glm::ivec2()) {
        this->type = type;
        this->pos = pos;
    }

    Type type;
    glm::ivec2 pos;
};

//--------------------------------------------------------------
class Button;
typedef std::shared_ptr<Button> ButtonRef;

class Button {

public:

    Button(coc::Rect rect = coc::Rect());
    ~Button();
    
    static ButtonRef create(const coc::Rect & rect = coc::Rect());
    
    void setRect(coc::Rect rect);
    void setRect(float x, float y, float w, float h);
    const coc::Rect & getRect() const;

    void setEnabled(bool value);
    void setUseHandlers(bool value);
    void setUpdateAsync(bool value);
    void setRegisterEvents(bool value);

	void moveTo( int x, int y);
	void moveCenterTo( int x, int y);

    const glm::ivec2 & getPointPosLast() const;

    void reset();
    
    void update();
    
	virtual void draw() const {}
    virtual void drawDebug() const {}

    bool over() const;
    bool overChanged() const;
    bool down() const;
    bool downChanged() const;

    bool movedInside() const;
    bool movedOutside() const;
    bool pressedInside() const;
    bool pressedOutside() const;
    bool draggedInside() const;
    bool draggedOutside() const;
    bool releasedInside() const;
    bool releasedOutside() const;

	void pointMoved(int x, int y);
    void pointPressed(int x, int y);
	void pointDragged(int x, int y);
	void pointReleased(int x, int y);
    void pointNew(ButtonPoint::Type type, int x, int y);

    virtual void handleMovedInside(){};
    virtual void handleMovedOutside(){};
    virtual void handlePressedInside(){};
    virtual void handlePressedOutside(){};
    virtual void handleDraggedInside(){};
    virtual void handleDraggedOutside(){};
    virtual void handleReleasedInside(){};
    virtual void handleReleasedOutside(){};
    virtual void handleEventRegister(){};
    virtual void handleEventUnregister(){};

protected:

    coc::Rect rect;
    bool bEnabled;
    bool bEnabledChanged;
    bool bUseHandlers;
    bool bUpdateAsync;
    bool bRegisterEvents;

    glm::ivec2 pointPos;
    std::vector<ButtonPoint> points;
    bool bOver;
    bool bOverChanged;
    bool bDown;
    bool bDownChanged;
    
    bool bMovedInside;
    bool bMovedOutside;
    bool bPressedInside;
    bool bPressedOutside;
    bool bDraggedInside;
    bool bDraggedOutside;
    bool bReleasedInside;
    bool bReleasedOutside;
};

}
