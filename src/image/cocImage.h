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

namespace coc {

//--------------------------------------------------------------
class Image;
typedef std::shared_ptr<Image> ImageRef;

class Image {

public:

    //----------------------------------------------------------
    enum ScaleMode {
        ScaleModeNone=0,
        ScaleModeFit,
        ScaleModeFill
    };
    
    //----------------------------------------------------------
    enum Crop {
        CropNone=0,
        CropRect,
        CropCircle,
        CropEllipse
    };
    
    //----------------------------------------------------------
    class Shape {
    public:
        std::vector<glm::vec2> vertices;
        std::vector<glm::vec2> texcoords;
        std::vector<glm::vec4> colors;
    };

    //----------------------------------------------------------
    Image(const glm::vec2 & size);
    ~Image();
    
    static ImageRef create(const glm::vec2 & size);
    
    void setPos(const glm::vec2 & value);
    const glm::vec2 & getPos() const;
    
    void setSize(const glm::vec2 & value);
    const glm::vec2 & getSize() const;
    
    void setRect(const coc::Rect & value);
    coc::Rect getRect() const;
    
    void setScaleMode(ScaleMode value);
    ScaleMode getScaleMode() const;
    
    void setCrop(Crop value);
    Crop getCrop() const;

    void setInsetUpperLeft(const glm::vec2 & value);
    void setInsetLowerRight(const glm::vec2 & value);
    void setInsetRect(const coc::Rect & value);
    void setInset(float value);
    void setInsetLeft(float value);
    void setInsetUpper(float value);
    void setInsetRight(float value);
    void setInsetLower(float value);
    
    std::vector<Shape> & getShapes() { return shapes; }
    
    virtual void update();
    
	virtual void draw() const {}
    virtual void drawDebug() const {}

protected:

    glm::vec2 sourceSize;
    
    glm::vec2 targetSize;
    glm::vec2 targetPos;
    bool bTargetChanged;
    
    ScaleMode scaleMode;
    bool bScaleModeChanged;
    
    Crop crop;
    bool bCropChanged;
    
    glm::vec2 insetUpperLeft;
    glm::vec2 insetLowerRight;
    bool bInsetChanged;
    
    std::vector<Shape> shapes;

};

}
