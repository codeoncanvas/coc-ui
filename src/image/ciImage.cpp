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
    
    shader = gl::getStockShader( gl::ShaderDef().texture().color() );
}

ciImage::~ciImage() {

}
    
//--------------------------------------------------------------
ciImageRef ciImage::create(const ci::gl::TextureRef & texture) {
    return ciImageRef(new ciImage(texture));
}

//--------------------------------------------------------------
void ciImage::update() {
    coc::Image::update();
    
    //
}

//--------------------------------------------------------------
void ciImage::draw() const {

    gl::ScopedGlslProg scopedShader(shader);
    gl::ScopedTextureBind textureBind(texture);
    
    for(Shape shape : shapes) {

        gl::VertBatch vb( GL_TRIANGLE_STRIP );
        for(glm::vec2 vert : shape.vertices) {
            vb.vertex(vert);
        }
        for(glm::vec2 tex : shape.texcoords) {
            vb.texCoord(tex);
        }
        for(glm::vec4 col : shape.colors) {
            vb.color(ColorA(col));
        }
        vb.draw();
    }
}

}
