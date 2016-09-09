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

#ifdef COC_CI

#include "cocButton.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

namespace coc {

class ciButton;
typedef std::shared_ptr<ciButton> ciButtonRef;

class ciButton : public coc::Button {

public:

    ciButton(coc::Rect rect = coc::Rect());
    
    static ciButtonRef create(const coc::Rect & rect = coc::Rect());

    void mouseMoved(ci::app::MouseEvent & mouse);
    void mousePressed(ci::app::MouseEvent & mouse);
    void mouseDragged(ci::app::MouseEvent & mouse);
    void mouseReleased(ci::app::MouseEvent & mouse);

	virtual void draw() const override;
    virtual void drawDebug() const override;

    virtual void handleMovedInside() override;
    virtual void handleMovedOutside() override;
    virtual void handlePressedInside() override;
    virtual void handleDraggedOutside() override;
    virtual void handleReleasedInside() override;
    virtual void handleReleasedOutside() override;

    virtual void handleEventRegister() override;
    virtual void handleEventUnregister() override;

	ci::signals::Signal<void()>& getSignalOnMovedInside() 	{ return signalOnMovedInside; }
	ci::signals::Signal<void()>& getSignalOnMovedOutside() 	{ return signalOnMovedOutside; }
	ci::signals::Signal<void()>& getSignalOnPressedInside() { return signalOnPressedInside; }
	ci::signals::Signal<void()>& getSignalOnDraggedOutside(){ return signalOnDraggedOutside; }
	ci::signals::Signal<void()>& getSignalOnReleasedInside(){ return signalOnReleasedInside; }
	ci::signals::Signal<void()>& getSignalOnReleasedOutside(){return signalOnReleasedOutside; }

private:

	ci::signals::Signal<void()>  signalOnMovedInside;
	ci::signals::Signal<void()>  signalOnMovedOutside;
	ci::signals::Signal<void()>  signalOnPressedInside;
	ci::signals::Signal<void()>  signalOnDraggedOutside;
	ci::signals::Signal<void()>  signalOnReleasedInside;
	ci::signals::Signal<void()>  signalOnReleasedOutside;

	ci::signals::ScopedConnection  cbMouseDown, cbMouseDrag, cbMouseUp, cbMouseMove;

};

}

#endif
