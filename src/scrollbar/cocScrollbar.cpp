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

ScrollbarRef Scrollbar::create(const Config & config) {
    ScrollbarRef scrollbar = ScrollbarRef(new Scrollbar());
    scrollbar->setup(config);
    return scrollbar;
}

void Scrollbar::setup(const Config & config) {
    //
}

void Scrollbar::update(float timeDelta) {
    //
}

}