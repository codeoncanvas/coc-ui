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

#include "cocImage.h"

namespace coc {

//--------------------------------------------------------------
Image::Image(const glm::vec2 & size) :
sourceSize(size),
targetSize(size),
targetPos(0, 0),
bTargetChanged(true),
alignment(AlignmentCenter),
bAlignmentChanged(false),
scale(ScaleNone),
bScaleChanged(false),
crop(CropNone),
bCropChanged(false),
insetPos0(0, 0),
insetPos1(size),
bInsetChanged(false) {
    //
}

//--------------------------------------------------------------
ImageRef Image::create(const glm::vec2 & size) {
    return ImageRef(new Image(size));
}

//--------------------------------------------------------------
void Image::setPos(const glm::vec2 & value) {
    bTargetChanged = bTargetChanged || (targetPos != value);
    targetPos = value;
}

const glm::vec2 & Image::getPos() const {
    return targetPos;
}

//--------------------------------------------------------------
void Image::setSize(const glm::vec2 & value) {
    bTargetChanged = bTargetChanged || (targetSize != value);
    targetSize = value;
}

const glm::vec2 & Image::getSize() const {
    return targetSize;
}

//--------------------------------------------------------------
void Image::setRect(const coc::Rect & value) {
    setPos( glm::vec2(value.getX(), value.getY()) );
    setSize( glm::vec2(value.getW(), value.getH()) );
}

coc::Rect Image::getRect() const {
    return coc::Rect(targetPos.x, targetPos.y, targetPos.x + targetSize.x, targetPos.y + targetSize.y);
}

//--------------------------------------------------------------
void Image::setAlignment(Alignment value) {
    bAlignmentChanged = bAlignmentChanged || alignment != value;
    alignment = value;
}

Image::Alignment Image::getAlignment() {
    return alignment;
}

//--------------------------------------------------------------
void Image::setScale(Scale value) {
    bScaleChanged = bScaleChanged || (scale != value);
    scale = value;
}

Image::Scale Image::getScale() const {
    return scale;
}

//--------------------------------------------------------------
void Image::setCrop(Crop value) {
    bCropChanged = bCropChanged || (crop != value);
    crop = value;
}

Image::Crop Image::getCrop() const {
    return crop;
}

//--------------------------------------------------------------
void Image::setInset(float value) {
    setInsetFromLeft( value );
    setInsetFromTop( value );
    setInsetFromRight( value );
    setInsetFromBottom( value );
}

float Image::getInsetMin() const {
    float inset = getInsetFromLeft();
    inset = coc::min(inset, getInsetFromTop());
    inset = coc::min(inset, getInsetFromRight());
    inset = coc::min(inset, getInsetFromBottom());
    return inset;
}

float Image::getInsetMax() const {
    float inset = getInsetFromLeft();
    inset = coc::max(inset, getInsetFromTop());
    inset = coc::max(inset, getInsetFromRight());
    inset = coc::max(inset, getInsetFromBottom());
    return inset;
}

//--------------------------------------------------------------
void Image::setInsetFromLeft(float value) {
    float x = value;
    bInsetChanged = bInsetChanged || (insetPos0.x != x);
    insetPos0.x = x;
}

float Image::getInsetFromLeft() const {
    return insetPos0.x;
}

//--------------------------------------------------------------
void Image::setInsetFromTop(float value) {
    float y = value;
    bInsetChanged = bInsetChanged || (insetPos0.y != y);
    insetPos0.y = y;
}

float Image::getInsetFromTop() const {
    return insetPos0.y;
}

//--------------------------------------------------------------
void Image::setInsetFromRight(float value) {
    float x = sourceSize.x - value;
    bInsetChanged = bInsetChanged || (insetPos1.x != x);
    insetPos1.x = x;
}

float Image::getInsetFromRight() const {
    return sourceSize.x - insetPos1.x;
}

//--------------------------------------------------------------
void Image::setInsetFromBottom(float value) {
    float y = sourceSize.y - value;
    bInsetChanged = bInsetChanged || (insetPos1.y != y);
    insetPos1.y = y;
}

float Image::getInsetFromBottom() const {
    return sourceSize.y - insetPos1.y;
}

//--------------------------------------------------------------
void Image::setInsetRect(const coc::Rect & value) {
    insetPos0.x = value.getX();
    insetPos0.y = value.getY();
    insetPos1.x = value.getX() + value.getW();
    insetPos1.y = value.getY() + value.getH();
}

coc::Rect Image::getInsetRect() const {
    return coc::Rect(insetPos0.x,
                     insetPos0.y,
                     insetPos0.x + insetPos1.x,
                     insetPos0.y + insetPos1.y);
}

//--------------------------------------------------------------
void Image::update() {
    
    bool bUpdate = false;
    bUpdate = bUpdate || bTargetChanged;
    bUpdate = bUpdate || bAlignmentChanged;
    bUpdate = bUpdate || bScaleChanged;
    bUpdate = bUpdate || bCropChanged;
    bUpdate = bUpdate || bInsetChanged;
    if(bUpdate == false) {
        return;
    }
    
    shapes.clear();

    //---------------------------------------------------------- scale.
    coc::Rect rectTarget = getRect();
    coc::Rect rectScaled(glm::vec2(0,0), sourceSize);
    
    if(scale == ScaleNone) {
        rectScaled = rectTarget;
    } else if(scale == ScaleFit) {
        rectScaled.fitInto(rectTarget);
    } else if(scale == ScaleFill) {
        rectScaled.fitInto(rectTarget, true);
    }
    
    glm::vec2 rectTarget0, rectTarget1;
    rectTarget0.x = rectTarget.getX();
    rectTarget0.y = rectTarget.getY();
    rectTarget1.x = rectTarget.getX() + rectTarget.getW();
    rectTarget1.y = rectTarget.getY() + rectTarget.getH();
    
    glm::vec2 rectScaled0, rectScaled1;
    rectScaled0.x = rectScaled.getX();
    rectScaled0.y = rectScaled.getY();
    rectScaled1.x = rectScaled.getX() + rectScaled.getW();
    rectScaled1.y = rectScaled.getY() + rectScaled.getH();

    glm::vec2 vert0, vert1;
    glm::vec2 tex0, tex1;
    
    bool bInset = false;
    bInset = bInset || (insetPos0 != glm::vec2(0, 0));
    bInset = bInset || (insetPos1 != sourceSize);
    if(bInset) {
    
        glm::vec2 insetVert0, insetVert1;
        insetVert0.x = rectScaled0.x + getInsetFromLeft();
        insetVert0.y = rectScaled0.y + getInsetFromTop();
        insetVert1.x = rectScaled1.x - getInsetFromRight();
        insetVert1.y = rectScaled1.y - getInsetFromBottom();
        
        glm::vec2 insetTex0, insetTex1;
        insetTex0.x = coc::map(insetPos0.x, 0, sourceSize.x, 0.0, 1.0);
        insetTex0.y = coc::map(insetPos0.y, 0, sourceSize.y, 0.0, 1.0);
        insetTex1.x = coc::map(insetPos1.x, 0, sourceSize.x, 0.0, 1.0);
        insetTex1.y = coc::map(insetPos1.y, 0, sourceSize.y, 0.0, 1.0);
        
        bool bUpperLeftCorner = true;
        if(bUpperLeftCorner) {
            
            vert0.x = rectScaled0.x;
            vert0.y = rectScaled0.y;
            vert1.x = insetVert0.x;
            vert1.y = insetVert0.y;
            
            tex0.x = 0.0;
            tex0.y = 0.0;
            tex1.x = insetTex0.x;
            tex1.y = insetTex0.y;
            
            shapes.push_back( getShapeRect(vert0, vert1, tex0, tex1) );
        }
        
        bool bUpperRightCorner = true;
        if(bUpperRightCorner) {

            vert0.x = insetVert1.x;
            vert0.y = rectScaled0.y;
            vert1.x = rectScaled1.x;
            vert1.y = insetVert0.y;

            tex0.x = insetTex1.x;
            tex0.y = 0.0;
            tex1.x = 1.0;
            tex1.y = insetTex0.y;
            
            shapes.push_back( getShapeRect(vert0, vert1, tex0, tex1) );
        }
        
        bool bLowerLeftCorner = true;
        if(bLowerLeftCorner) {

            vert0.x = rectScaled0.x;
            vert0.y = insetVert1.y;
            vert1.x = insetVert0.x;
            vert1.y = rectScaled1.y;

            tex0.x = 0.0;
            tex0.y = insetTex1.y;
            tex1.x = insetTex0.x;
            tex1.y = 1.0;
            
            shapes.push_back( getShapeRect(vert0, vert1, tex0, tex1) );
        }
        
        bool bLowerRightCorner = true;
        if(bLowerRightCorner) {
        
            vert0.x = insetVert1.x;
            vert0.y = insetVert1.y;
            vert1.x = rectScaled1.x;
            vert1.y = rectScaled1.y;

            tex0.x = insetTex1.x;
            tex0.y = insetTex1.y;
            tex1.x = 1.0;
            tex1.y = 1.0;
            
            shapes.push_back( getShapeRect(vert0, vert1, tex0, tex1) );
        }
        
        bool bLeftEdge = true;
        if(bLeftEdge) {
            
            vert0.x = rectScaled0.x;
            vert0.y = insetVert0.y;
            vert1.x = insetVert0.x;
            vert1.y = insetVert1.y;
            
            tex0.x = 0.0;
            tex0.y = insetTex0.y;
            tex1.x = insetTex0.x;
            tex1.y = insetTex1.y;
            
            shapes.push_back( getShapeRect(vert0, vert1, tex0, tex1) );
        }
        
        bool bTopEdge = true;
        if(bTopEdge) {

            vert0.x = insetVert0.x;
            vert0.y = rectScaled0.y;
            vert1.x = insetVert1.x;
            vert1.y = insetVert0.y;

            tex0.x = insetTex0.x;
            tex0.y = 0.0;
            tex1.x = insetTex1.x;
            tex1.y = insetTex0.y;
            
            shapes.push_back( getShapeRect(vert0, vert1, tex0, tex1) );
        }
        
        bool bRightEdge = true;
        if(bRightEdge) {
        
            vert0.x = insetVert1.x;
            vert0.y = insetVert0.y;
            vert1.x = rectScaled1.x;
            vert1.y = insetVert1.y;

            tex0.x = insetTex1.x;
            tex0.y = insetTex0.y;
            tex1.x = 1.0;
            tex1.y = insetTex1.y;
            
            shapes.push_back( getShapeRect(vert0, vert1, tex0, tex1) );
        }
        
        bool bBottomEdge = true;
        if(bBottomEdge) {
        
            vert0.x = insetVert0.x;
            vert0.y = insetVert1.y;
            vert1.x = insetVert1.x;
            vert1.y = rectScaled1.y;

            tex0.x = insetTex0.x;
            tex0.y = insetTex1.y;
            tex1.x = insetTex1.x;
            tex1.y = 1.0;
            
            shapes.push_back( getShapeRect(vert0, vert1, tex0, tex1) );
        }
        
        bool bMiddle = true;
        if(bMiddle) {

            vert0.x = insetVert0.x;
            vert0.y = insetVert0.y;
            vert1.x = insetVert1.x;
            vert1.y = insetVert1.y;

            tex0.x = insetTex0.x;
            tex0.y = insetTex0.y;
            tex1.x = insetTex1.x;
            tex1.y = insetTex1.y;
            
            shapes.push_back( getShapeRect(vert0, vert1, tex0, tex1) );
        }
        
    } else {
    
        vert0 = rectScaled0;
        vert1 = rectScaled1;
        
        tex0 = glm::vec2(0, 0);
        tex1 = glm::vec2(1, 1);
        
        if(crop == CropRect) {
            vert0.x = coc::clamp(vert0.x, rectTarget0.x, rectTarget1.x);
            vert0.y = coc::clamp(vert0.y, rectTarget0.y, rectTarget1.y);
            vert1.x = coc::clamp(vert1.x, rectTarget0.x, rectTarget1.x);
            vert1.y = coc::clamp(vert1.y, rectTarget0.y, rectTarget1.y);
            
            tex0.x = coc::map(vert0.x, rectScaled0.x, rectScaled1.x, 0.0, 1.0);
            tex0.y = coc::map(vert0.y, rectScaled0.y, rectScaled1.y, 0.0, 1.0);
            tex1.x = coc::map(vert1.x, rectScaled0.x, rectScaled1.x, 0.0, 1.0);
            tex1.y = coc::map(vert1.y, rectScaled0.y, rectScaled1.y, 0.0, 1.0);
        }
        
        shapes.push_back( getShapeRect(vert0, vert1, tex0, tex1) );
    }
    
    bTargetChanged = false;
    bAlignmentChanged = false;
    bScaleChanged = false;
    bCropChanged = false;
    bInsetChanged = false;
}

//--------------------------------------------------------------
Image::Shape Image::getShapeRect(const glm::vec2 & vert0,
                                 const glm::vec2 & vert1,
                                 const glm::vec2 & tex0,
                                 const glm::vec2 & tex1) {
    Shape shape;
    
    shape.vertices.push_back( glm::vec2(vert0.x, vert0.y) );
    shape.vertices.push_back( glm::vec2(vert0.x, vert1.y) );
    shape.vertices.push_back( glm::vec2(vert1.x, vert0.y) );
    shape.vertices.push_back( glm::vec2(vert1.x, vert1.y) );
    
    shape.texcoords.push_back( glm::vec2(tex0.x, tex0.y) );
    shape.texcoords.push_back( glm::vec2(tex0.x, tex1.y) );
    shape.texcoords.push_back( glm::vec2(tex1.x, tex0.y) );
    shape.texcoords.push_back( glm::vec2(tex1.x, tex1.y) );
    
    glm::vec4 colorWhite(1, 1, 1, 1);
    shape.colors.push_back( colorWhite );
    shape.colors.push_back( colorWhite );
    shape.colors.push_back( colorWhite );
    shape.colors.push_back( colorWhite );
    
    return shape;
}

}
