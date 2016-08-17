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

    class Config {
        Config() {
            type = Type::Vertical;
            ease = 0.0;
        }
        Type type;
        coc::Rect rect;
        float ease;
    };

    //----------------------------------------------------------
    Scrollbar();
    ~Scrollbar();
    
    static ScrollbarRef create(const Config & config);
    
    virtual void setup(const Config & config);
    virtual void update(float timeDelta=0);
    virtual void draw() const {};

protected:

    coc::Button track;
    coc::Button thumb;
};

}
