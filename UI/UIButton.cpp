/*
    UIButton.h - Library for UI buttons.
    Created by Daniel Esteban, December 24, 2012.
    Released into the public domain.
*/

#include "UIButton.h"

UIButton::UIButton(int gx, int gy, int w, int h, ByteCallback oc, ByteCallback od) {
	width = w;
	height = h;
	x = gx;
	y = gy;
	onClick = oc;
	onDown = od;
	next = NULL;
}
