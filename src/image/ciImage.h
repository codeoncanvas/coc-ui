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

#include "cocImage.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

namespace coc {

//--------------------------------------------------------------
class ciImage;
typedef std::shared_ptr<ciImage> ciImageRef;

class ciImage : public coc::Image {

public:

    ciImage(const ci::gl::TextureRef & texture);
    
    static ciImageRef create(const ci::gl::TextureRef & texture);
    
    void setShader(ci::gl::GlslProgRef value);
    
    virtual void update() override;
    
	virtual void draw() const override;

protected:

    ci::gl::TextureRef texture;
    ci::gl::GlslProgRef shader;

};

}
