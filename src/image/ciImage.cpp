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

#include "ciImage.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace coc {

//--------------------------------------------------------------
ciImage::ciImage(const ci::gl::TextureRef & texture) :
coc::Image( texture->getSize() ) {

}

ciImage::~ciImage() {

}
    
//--------------------------------------------------------------
ciImageRef ciImage::create(const ci::gl::TextureRef & texture) {
    return ciImageRef(new ciImage(texture));
}
    
void ciImage::update() {
    coc::Image::update();
    
    //
}
    
void ciImage::draw() const {
    //
}

void ciImage::drawDebug() const {
    //
}

}
