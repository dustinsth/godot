/**************************************************************************/
/*  godot_content_view.h                                                  */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#ifndef GODOT_CONTENT_VIEW_H
#define GODOT_CONTENT_VIEW_H

#include "servers/display_server.h"

#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

#if defined(GLES3_ENABLED)
#import <AppKit/NSOpenGLView.h>
#define RootView NSOpenGLView
#else
#define RootView NSView
#endif

#import <QuartzCore/CAMetalLayer.h>

@interface GodotContentLayerDelegate : NSObject <CALayerDelegate> {
	DisplayServer::WindowID window_id;
}

- (void)setWindowID:(DisplayServer::WindowID)wid;

@end

@interface GodotContentView : RootView <NSTextInputClient> {
	DisplayServer::WindowID window_id;
	NSTrackingArea *tracking_area;
	NSMutableAttributedString *marked_text;
	bool ime_input_event_in_progress;
	bool mouse_down_control;
	bool ignore_momentum_scroll;
	bool last_pen_inverted;
	id layer_delegate;
}

- (void)processScrollEvent:(NSEvent *)event button:(MouseButton)button factor:(double)factor;
- (void)processPanEvent:(NSEvent *)event dx:(double)dx dy:(double)dy;
- (void)processMouseEvent:(NSEvent *)event index:(MouseButton)index pressed:(bool)pressed;
- (void)setWindowID:(DisplayServer::WindowID)wid;
- (void)updateLayerDelegate;
- (void)cancelComposition;

@end

#endif // GODOT_CONTENT_VIEW_H
