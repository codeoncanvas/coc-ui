/**
 *
 *      ┌─┐╔═╗┌┬┐┌─┐
 *      │  ║ ║ ││├┤
 *      └─┘╚═╝─┴┘└─┘
 *   ┌─┐┌─┐╔╗╔┬  ┬┌─┐┌─┐
 *   │  ├─┤║║║└┐┌┘├─┤└─┐
 *   └─┘┴ ┴╝╚╝ └┘ ┴ ┴└─┘
 *
 * Copyright (c) 2016 Code on Canvas Pty Ltd, http://CodeOnCanvas.cc
 *
 * This software is distributed under the MIT license
 * https://tldrlegal.com/license/mit-license
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code
 *
 **/


#pragma once

#include "ciButton.h"
#include "cinder/gl/Texture.h"

// TODO: hover states

namespace coc {

class ciButtonTexture : public ciButton {

public:

	void setTexture( ci::gl::TextureRef _tex );
	ci::gl::TextureRef getTexture() { return tex; }

	void draw() const override;


protected:

	ci::gl::TextureRef	tex;

};//class ciButtonTexture

}//namespace coc
