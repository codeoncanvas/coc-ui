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

    //----------------------------------------------------------
    enum Type {
        Vertical = 0,
        Horizontal
    };

    class Settings {
    public:
        Settings():
        type(Type::Vertical),
        position(0),
        contentRatio(0.5),
        ease(0) {}
        
        Type type;
        coc::Rect rect;
        float position;
        float contentRatio;
        float ease;
    };

    //----------------------------------------------------------
    Scrollbar();
    ~Scrollbar();
    
    static ScrollbarRef create(const Settings & settings);
    
    virtual void setup(const Settings & settings);
    virtual coc::ButtonRef initButton() { return coc::Button::create(); }
    
    void setType(Type value) { settings.type = value; }
    void setRect(coc::Rect value) { settings.rect = value; }
    void setContentRatio(float value) { settings.contentRatio = value; }
    void setEase(float value) { settings.ease = value; }
    void setPosition(float value) { settings.position = value; }
    
    virtual void update();
    
    virtual void draw() const {};
    virtual void drawDebug() const {};
    
	virtual void pointMoved(int x, int y);
    virtual void pointPressed(int x, int y);
	virtual void pointDragged(int x, int y);
	virtual void pointReleased(int x, int y);

protected:

    Settings settingsOld;
    Settings settings;
    
    coc::ButtonRef track;
    coc::ButtonRef thumb;
    glm::ivec2 thumbPressStartPos;
    glm::ivec2 thumbPressInsidePos;
    bool bThumbPressed;
};

}
