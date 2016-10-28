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
scale(ScaleNone),
bScaleChanged(false),
alignment(AlignmentCenter),
bAlignmentChanged(false),
crop(CropNone),
bCropChanged(false),
cropCircleRes(100),
bCropCircleResChanged(false),
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
void Image::setScale(Scale value) {
    bScaleChanged = bScaleChanged || (scale != value);
    scale = value;
}

Image::Scale Image::getScale() const {
    return scale;
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
void Image::setCrop(Crop value) {
    bCropChanged = bCropChanged || (crop != value);
    crop = value;
}

Image::Crop Image::getCrop() const {
    return crop;
}

//--------------------------------------------------------------
void Image::setCropCircleRes(float value) {
    bCropCircleResChanged = bCropCircleResChanged || (cropCircleRes != value);
    cropCircleRes = value;
}

float Image::getCropCircleRes() {
    return cropCircleRes;
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
    bUpdate = bUpdate || bCropCircleResChanged;
    bUpdate = bUpdate || bInsetChanged;
    if(bUpdate == false) {
        return;
    }
    
    shapes.clear();

    //---------------------------------------------------------- scale.
    coc::Rect rectTarget = getRect();
    coc::Rect rectScaled(glm::vec2(0,0), sourceSize);
    
    if(scale == ScaleStretch) {
    
        rectScaled = rectTarget;
        
    } else if(scale == ScaleFit) {
    
        rectScaled.fitInto(rectTarget);
        
    } else if(scale == ScaleFill) {
    
        rectScaled.fitInto(rectTarget, true);
    
    } else { // no scale - center image by default.
    
        float x = rectTarget.getX() + (rectTarget.getW() - rectScaled.getW()) * 0.5;
        float y = rectTarget.getY() + (rectTarget.getH() - rectScaled.getH()) * 0.5;
        rectScaled.setX(x);
        rectScaled.setY(y);
    }
    
    //---------------------------------------------------------- alignment.
    glm::vec2 alignPos0, alignPos1;
    alignPos0.x = rectTarget.getX();
    alignPos0.y = rectTarget.getY();
    alignPos1.x = rectTarget.getX() + rectTarget.getW() - rectScaled.getW();
    alignPos1.y = rectTarget.getY() + rectTarget.getH() - rectScaled.getH();
    
    if(alignment == Image::AlignmentTopLeft) {
    
        rectScaled.setX(alignPos0.x);
        rectScaled.setY(alignPos0.y);
        
    } else if(alignment == Image::AlignmentTopCenter) {
    
        rectScaled.setY(alignPos0.y);
        
    } else if(alignment == Image::AlignmentTopRight) {
    
        rectScaled.setX(alignPos1.x);
        rectScaled.setY(alignPos0.y);
        
    } else if(alignment == Image::AlignmentBottomLeft) {
    
        rectScaled.setX(alignPos0.x);
        rectScaled.setY(alignPos1.y);
    
    } else if(alignment == Image::AlignmentBottomCenter) {
    
        rectScaled.setY(alignPos1.y);
    
    } else if(alignment == Image::AlignmentBottomRight) {
    
        rectScaled.setX(alignPos1.x);
        rectScaled.setY(alignPos1.y);
    
    } else if(alignment == Image::AlignmentLeftCenter) {
    
        rectScaled.setX(alignPos0.x);
    
    } else if(alignment == Image::AlignmentRightCenter) {
    
        rectScaled.setX(alignPos1.x);
    }
    
    //---------------------------------------------------------- inset and crop.
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
    
        if(crop == CropRect) {
        
            vert0.x = coc::clamp(rectScaled0.x, rectTarget0.x, rectTarget1.x);
            vert0.y = coc::clamp(rectScaled0.y, rectTarget0.y, rectTarget1.y);
            vert1.x = coc::clamp(rectScaled1.x, rectTarget0.x, rectTarget1.x);
            vert1.y = coc::clamp(rectScaled1.y, rectTarget0.y, rectTarget1.y);
            
            tex0.x = coc::map(vert0.x, rectScaled0.x, rectScaled1.x, 0.0, 1.0);
            tex0.y = coc::map(vert0.y, rectScaled0.y, rectScaled1.y, 0.0, 1.0);
            tex1.x = coc::map(vert1.x, rectScaled0.x, rectScaled1.x, 0.0, 1.0);
            tex1.y = coc::map(vert1.y, rectScaled0.y, rectScaled1.y, 0.0, 1.0);
            
            shapes.push_back( getShapeRect(vert0, vert1, tex0, tex1) );
        
        } else if(crop == CropCircle) {

            vert0.x = coc::max(rectScaled0.x, rectTarget0.x);
            vert0.y = coc::max(rectScaled0.y, rectTarget0.y);
            vert1.x = coc::min(rectScaled1.x, rectTarget1.x);
            vert1.y = coc::min(rectScaled1.y, rectTarget1.y);
            
            tex0.x = coc::map(vert0.x, rectScaled0.x, rectScaled1.x, 0.0, 1.0);
            tex0.y = coc::map(vert0.y, rectScaled0.y, rectScaled1.y, 0.0, 1.0);
            tex1.x = coc::map(vert1.x, rectScaled0.x, rectScaled1.x, 0.0, 1.0);
            tex1.y = coc::map(vert1.y, rectScaled0.y, rectScaled1.y, 0.0, 1.0);
            
            shapes.push_back( getShapeCircle(vert0, vert1, tex0, tex1) );
        
        } else { // no crop.
        
            vert0 = rectScaled0;
            vert1 = rectScaled1;
            
            tex0 = glm::vec2(0, 0);
            tex1 = glm::vec2(1, 1);
            
            shapes.push_back( getShapeRect(vert0, vert1, tex0, tex1) );
        }
    }
    
    bTargetChanged = false;
    bAlignmentChanged = false;
    bScaleChanged = false;
    bCropChanged = false;
    bCropCircleResChanged = false;
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
    
    return shape;
}

Image::Shape Image::getShapeCircle(const glm::vec2 & vert0,
                                   const glm::vec2 & vert1,
                                   const glm::vec2 & tex0,
                                   const glm::vec2 & tex1) {
    Shape shape;
    
    glm::vec2 circleSizeHalf = (vert1 - vert0) * 0.5f;
    glm::vec2 circleCenter = vert0 + circleSizeHalf;
    
    for(int i=0; i<cropCircleRes; i++) {
        float p = coc::map(i, 0, cropCircleRes-1, 0.0, 1.0);
        float a = p * M_PI * 2;
        
        glm::vec2 circleVert;
        circleVert.x = circleCenter.x + sin(a) * circleSizeHalf.x;
        circleVert.y = circleCenter.y + cos(a) * circleSizeHalf.y;
        
        glm::vec2 circleTex0, circleTex1;
        circleTex0.x = coc::map(circleCenter.x, vert0.x, vert1.x, tex0.x, tex1.x);
        circleTex0.y = coc::map(circleCenter.y, vert0.y, vert1.y, tex0.y, tex1.y);
        circleTex1.x = coc::map(circleVert.x, vert0.x, vert1.x, tex0.x, tex1.x);
        circleTex1.y = coc::map(circleVert.y, vert0.y, vert1.y, tex0.y, tex1.y);
        
        shape.vertices.push_back(circleCenter);
        shape.vertices.push_back(circleVert);

        shape.texcoords.push_back(circleTex0);
        shape.texcoords.push_back(circleTex1);
    }
    
    return shape;

}

}
