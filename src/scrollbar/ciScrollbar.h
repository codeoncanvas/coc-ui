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

#include "cocScrollbar.h"
#include "ciButton.h"

namespace coc {
namespace ci {

//--------------------------------------------------------------
class Scrollbar;
typedef std::shared_ptr<Scrollbar> ScrollbarRef;

//--------------------------------------------------------------
class Scrollbar : public coc::Scrollbar {
public:

    Scrollbar();
    ~Scrollbar();
    
    virtual coc::ButtonRef initButton() override { return coc::ciButton::create(); }
    
    virtual void draw() const override;
    virtual void drawDebug() const override;
    
protected:

    //
};

}
}
