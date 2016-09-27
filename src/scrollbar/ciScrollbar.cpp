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

#include "ciScrollbar.h"

namespace coc {

//--------------------------------------------------------------
ciScrollbar::ciScrollbar() :
coc::Scrollbar() {
    //
}

ciScrollbar::~ciScrollbar() {
    //
}

//--------------------------------------------------------------
ciScrollbarRef ciScrollbar::create() {
    ciScrollbarRef scrollbar = ciScrollbarRef(new ciScrollbar());
    scrollbar->setup();
    return scrollbar;
}

//--------------------------------------------------------------
void ciScrollbar::draw() const {
    if(texTrack) {
        ci::Rectf rectTract = rect;
        ci::gl::draw(texTrack, rectTract);
    }
    if(texProgress) {
        ci::Rectf rectProgress = rect;
        if(type == Type::Vertical) {
            rectProgress.y2 = coc::map(position, 0.0, 1.0, rectProgress.y1, rectProgress.y2);
        } else if(type == Type::Horizontal) {
            rectProgress.x2 = coc::map(position, 0.0, 1.0, rectProgress.x1, rectProgress.x2);
        }
        ci::gl::draw(texProgress, rectProgress);
    }
    if(texThumb) {
        ci::gl::draw(texThumb, thumb->getRect());
    }
}

void ciScrollbar::drawDebug() const {
    track->drawDebug();
    thumb->drawDebug();
}

}