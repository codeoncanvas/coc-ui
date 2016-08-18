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

Scrollbar::Scrollbar() {
    //
}

Scrollbar::~Scrollbar() {
    //
}

ScrollbarRef Scrollbar::create(const Settings & settings) {
    ScrollbarRef scrollbar = ScrollbarRef(new Scrollbar());
    scrollbar->setup(settings);
    return scrollbar;
}

void Scrollbar::setup(const Settings & value) {
    settings = value;
    
    track = initButton();
    thumb = initButton();
}

void Scrollbar::update() {

    settingsOld = settings;
    
    coc::Rect & trackRect = settings.rect;
    coc::Rect thumbRect = trackRect;
    if(settings.type == Type::Vertical) {
    
        float trackRectY = trackRect.getY();
        float trackRectH = trackRect.getH();
        float thumbRectH = trackRectH * settings.contentRatio;
        float thumbRectY = coc::map(settings.position, 0.0, 1.0, trackRectY, trackRectY + trackRectH - thumbRectH, true);
        thumbRect.setH(thumbRectH);
        thumbRect.setY(thumbRectY);
        
    } else if(settings.type == Type::Horizontal) {

        float trackRectX = trackRect.getX();
        float trackRectW = trackRect.getW();
        float thumbRectW = trackRectW * settings.contentRatio;
        float thumbRectX = coc::map(settings.position, 0.0, 1.0, trackRectX, trackRectX + trackRectW - thumbRectW, true);
        thumbRect.setW(thumbRectW);
        thumbRect.setX(thumbRectX);
    }
    
    track->setRect(trackRect);
    track->update();
    
    thumb->setRect(thumbRect);
    thumb->update();

    if(thumb->pressedInside()) {
        
        // start thumb drag.
        
    } else if(track->pressedInside()) {
    
        // jump to location.
    }
}

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