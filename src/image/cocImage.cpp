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
scaleMode(ScaleModeNone),
bScaleModeChanged(false),
crop(CropNone),
bCropChanged(false),
insetUpperLeft(0, 0),
insetLowerRight(size),
bInsetChanged(false) {
    //
}

Image::~Image() {

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
void Image::setScaleMode(ScaleMode value) {
    bScaleModeChanged = bScaleModeChanged || (scaleMode != value);
    scaleMode = value;
}

Image::ScaleMode Image::getScaleMode() const {
    return scaleMode;
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
void Image::setInsetUpperLeft(const glm::vec2 & value) {
    setInsetLeft( value.x );
    setInsetUpper( value.y );
}

void Image::setInsetLowerRight(const glm::vec2 & value) {
    setInsetRight( value.x );
    setInsetLower( value.y );
}

void Image::setInsetRect(const coc::Rect & value) {
    setInsetLeft( value.getX() );
    setInsetUpper( value.getY() );
    setInsetRight( sourceSize.x - value.getX() - value.getW() );
    setInsetLower( sourceSize.y - value.getY() - value.getH() );
}

void Image::setInset(float value) {
    setInsetLeft( value );
    setInsetUpper( value );
    setInsetRight( value );
    setInsetLower( value );
}

void Image::setInsetLeft(float value) {
    bInsetChanged = bInsetChanged || (insetUpperLeft.x != value);
    insetUpperLeft.x = value;
}

void Image::setInsetUpper(float value) {
    bInsetChanged = bInsetChanged || (insetUpperLeft.y != value);
    insetUpperLeft.y = value;
}

void Image::setInsetRight(float value) {
    bInsetChanged = bInsetChanged || (insetLowerRight.x != value);
    insetLowerRight.x = value;
}

void Image::setInsetLower(float value) {
    bInsetChanged = bInsetChanged || (insetLowerRight.y != value);
    insetLowerRight.y = value;
}

//--------------------------------------------------------------    
void Image::update() {
    
    bool bUpdate = false;
    bUpdate = bUpdate || bTargetChanged;
    bUpdate = bUpdate || bScaleModeChanged;
    bUpdate = bUpdate || bCropChanged;
    bUpdate = bUpdate || bInsetChanged;
    if(bUpdate == false) {
        return;
    }
    
    if(bTargetChanged) {
    
    }
    
    if(bScaleModeChanged) {
        //
    }
    
    if(bInsetChanged) {
        //
    }
    
    bTargetChanged = false;
    bScaleModeChanged = false;
    bCropChanged = false;
    bInsetChanged = false;
}

}
