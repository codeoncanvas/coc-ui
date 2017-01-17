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
#include "cocButton.h"

namespace coc {

//--------------------------------------------------------------
class Scrollbar;
typedef std::shared_ptr<Scrollbar> ScrollbarRef;

//--------------------------------------------------------------
class Scrollbar {
public:

    enum Type {
        Vertical = 0,
        Horizontal
    };

    Scrollbar();
    ~Scrollbar();
    
    static ScrollbarRef create();
    
    virtual void setup();
    virtual coc::ButtonRef initButton() const { return coc::Button::create(); }
    
    void setType(Type value);
    Type getType() const;
    
    void setRect(coc::Rect value);
    const coc::Rect & getRect() const;
    
    void setContentRatio(float value);
    float getContentRatio() const;
    
    void setThumbOffset(float value);
    float getThumbOffset() const;
    
    void setEase(float value);
    float getEase() const;
    
    void setPosition(float value);
    float getPosition() const;
    bool hasPositionChanged() const { return bPositionChangeInternal; }
    
    void setEnabled(bool value);
    
    virtual void update();
    
    virtual void draw() const {};
    virtual void drawDebug() const {};
    
	virtual void pointMoved(int x, int y);
    virtual void pointPressed(int x, int y);
	virtual void pointDragged(int x, int y);
	virtual void pointReleased(int x, int y);

protected:

    Type type;
    coc::Rect rect;
    float position;
    float contentRatio;
    float ease;
    float thumbOffset;
    
    coc::ButtonRef track;
    coc::ButtonRef thumb;
    glm::ivec2 thumbPressStartPos;
    glm::ivec2 thumbPressInsidePos;
    bool bThumbPressed;
    
    bool bPositionChangeInternal;
    bool bPositionChangeExternal;
};

}
