/*
    UIButton.h - Library for UI buttons.
    Created by Daniel Esteban, December 24, 2012.
    Released into the public domain.
*/

#include "UIButton.h"

UIButton::UIButton(String l, int gx, int gy, int w, int h, TouchEvent oc, TouchEvent od) {
	label = l;
	width = w;
	height = h;
	x = gx;
	y = gy;
	onClick = oc;
	onDown = od;
	next = NULL;
}
