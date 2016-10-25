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
    enum Scale {
        ScaleNone=0,
        ScaleStretch,
        ScaleFit,
        ScaleFill,
        ScaleTotal
    };
    
    //----------------------------------------------------------
    enum Alignment {
        AlignmentCenter=0,
        AlignmentTopLeft,
        AlignmentTopCenter,
        AlignmentTopRight,
        AlignmentBottomLeft,
        AlignmentBottomCenter,
        AlignmentBottomRight,
        AlignmentLeftCenter,
        AlignmentRightCenter,
        AlignmentTotal
    };
    
    //----------------------------------------------------------
    enum Crop {
        CropNone=0,
        CropRect,
        CropCircle,
        CropTotal
    };
    
    //----------------------------------------------------------
    class Shape {
    public:
        std::vector<glm::vec2> vertices;
        std::vector<glm::vec2> texcoords;
    };

    //----------------------------------------------------------
    Image(const glm::vec2 & size);
    
    static ImageRef create(const glm::vec2 & size);
    
    //----------------------------------------------------------
    void setPos(const glm::vec2 & value);
    const glm::vec2 & getPos() const;
    
    void setSize(const glm::vec2 & value);
    const glm::vec2 & getSize() const;
    
    void setRect(const coc::Rect & value);
    coc::Rect getRect() const;
    
    void setScale(Scale value);
    Scale getScale() const;
    
    void setAlignment(Alignment value);
    Alignment getAlignment();
    
    void setCrop(Crop value);
    Crop getCrop() const;
    
    void setCropCircleRes(float value);
    float getCropCircleRes();
    
    void setColor(const glm::vec4 & value);
    const glm::vec4 & getColor() const;

    //----------------------------------------------------------
    void setInset(float value);
    float getInsetMin() const;
    float getInsetMax() const;
    
    void setInsetFromLeft(float value);
    float getInsetFromLeft() const;
    
    void setInsetFromTop(float value);
    float getInsetFromTop() const;
    
    void setInsetFromRight(float value);
    float getInsetFromRight() const;
    
    void setInsetFromBottom(float value);
    float getInsetFromBottom() const;

    void setInsetRect(const coc::Rect & value);
    coc::Rect getInsetRect() const;
    
    //----------------------------------------------------------
    std::vector<Shape> & getShapes() { return shapes; }
    
    //----------------------------------------------------------
    virtual void update();
    
	virtual void draw() const {}
    virtual void drawDebug() const {}

protected:

    Shape getShapeRect(const glm::vec2 & vert0,
                       const glm::vec2 & vert1,
                       const glm::vec2 & tex0,
                       const glm::vec2 & tex1);
    
    Shape getShapeCircle(const glm::vec2 & vert0,
                         const glm::vec2 & vert1,
                         const glm::vec2 & tex0,
                         const glm::vec2 & tex1);
    
    glm::vec2 sourceSize;
    
    glm::vec2 targetSize;
    glm::vec2 targetPos;
    bool bTargetChanged;
    
    Scale scale;
    bool bScaleChanged;
    
    Alignment alignment;
    bool bAlignmentChanged;
    
    Crop crop;
    bool bCropChanged;
    float cropCircleRes;
    bool bCropCircleResChanged;
    
    glm::vec2 insetPos0;
    glm::vec2 insetPos1;
    bool bInsetChanged;
    
    std::vector<Shape> shapes;
    glm::vec4 color;
};

}
