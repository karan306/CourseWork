/*
    This file is part of the mydraw.

    mydraw is a simple, interactive drawing program written using OpenGL. 
    
    This code base is meant to serve as a starter code for an assignment in a 
    Computer Graphics course.

    Copyright (c) 2018 by Parag Chaudhuri

    mydraw is free software; you can redistribute it and/or modify it under the 
    terms of the MIT License.

    Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include "brush.hpp"
#include "canvas.hpp"

namespace mydraw 
{
 void point_brush_t::stroke (const point_t &pt, canvas_t &canvas)
{
	
 }
 void point_brush_t::stroke (unsigned int xpos, unsigned int ypos, canvas_t *canvas)
 {
	int r=get_size()-1;
	unsigned int w=canvas->get_width();
	unsigned int h=canvas->get_height();
	for(int i=-1*r;i<=r;i++){
		for(int j=-1*r;j<=r;j++){
			if(i*i+j*j<=r*r){
				if(xpos+i>0&&xpos+i<w&&ypos+j>0&&ypos+j<h)
					canvas->set_pixel(xpos+i,ypos+j);
			}
		}
	}
 }

 void point_brush_t::stroke (unsigned int xpos, unsigned int ypos, unsigned int xpos1, unsigned int ypos1, canvas_t *canvas)
 {

 }
  
 void eraser_point_brush_t::stroke (const point_t &pt, canvas_t &canvas)
{
	
 }
 void eraser_point_brush_t::stroke (unsigned int xpos, unsigned int ypos, canvas_t *canvas)
 {
	int r=get_size()-1;
	unsigned int w=canvas->get_width();
	unsigned int h=canvas->get_height();
	for(int i=-1*r;i<=r;i++){
		for(int j=-1*r;j<=r;j++){
			if(i*i+j*j<=r*r){
				if(xpos+i>0&&xpos+i<w&&ypos+j>0&&ypos+j<h)
					canvas->erase_pixel(xpos+i,ypos+j);
			}
		}
	}
 }

 void eraser_point_brush_t::stroke (unsigned int xpos, unsigned int ypos, unsigned int xpos1, unsigned int ypos1, canvas_t *canvas)
 {

 }

 void smooth_brush_t::stroke (const point_t &pt, canvas_t &canvas)
		{
			
		}
 void smooth_brush_t::stroke (unsigned int xpos, unsigned int ypos, canvas_t *canvas)
 {
   
 }

 void smooth_brush_t::stroke (unsigned int xpos, unsigned int ypos, unsigned int xpos1, unsigned int ypos1, canvas_t *canvas)
 {
//    int r=get_size();
//    if (get_size()==1) canvas->set_pixel(xpos,ypos);
	int dx, dy, i, e;
	int incx, incy, inc1, inc2;
	int x,y;
	int r=get_size()-1;
	int w=canvas->get_width();
	int h=canvas->get_height();
	dx = xpos1-xpos;
	dy = ypos1-ypos;

	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	incx = 1;
	if (xpos1 < xpos) incx = -1;
	incy = 1;
	if (ypos1 < ypos) incy = -1;
	x = xpos; y = ypos;
	if (dx > dy) {
		for(int i=-1*r;i<=r;i++){
		for(int j=-1*r;j<=r;j++){
			if(i*i+j*j<=r*r){
				if(x+i>0&&x+i<w&&y+j>0&&y+j<h)
					canvas->set_pixel(x+i,y+j);
			}
		}
		}		
		e = 2 * dy-dx;
		inc1 = 2*(dy-dx);
		inc2 = 2*dy;
		for (i=0; i<dx; i++) {
			if (e >= 0) {
				y += incy;
				e += inc1;
			}
			else
				e += inc2;
			x += incx;
			for(int i=-1*r;i<=r;i++){
				for(int j=-1*r;j<=r;j++){
					if(i*i+j*j<=r*r){
						if(x+i>0&&x+i<w&&y+j>0&&y+j<h)
							canvas->set_pixel(x+i,y+j);
					}
				}
				}	
		}

	} else {
		for(int i=-1*r;i<=r;i++){
		for(int j=-1*r;j<=r;j++){
			if(i*i+j*j<=r*r){
				if(x+i>0&&x+i<w&&y+j>0&&y+j<h)
					canvas->set_pixel(x+i,y+j);
			}
		}
		}	
		e = 2*dx-dy;
		inc1 = 2*(dx-dy);
		inc2 = 2*dx;
		for (i=0; i<dy; i++) {
			if (e >= 0) {
				x += incx;
				e += inc1;
			}
			else
				e += inc2;
			y += incy;
			for(int i=-1*r;i<=r;i++){
			for(int j=-1*r;j<=r;j++){
				if(i*i+j*j<=r*r){
					if(x+i>0&&x+i<w&&y+j>0&&y+j<h)
						canvas->set_pixel(x+i,y+j);
				}
			}
			}	
		}
	}
 }

 void eraser_smooth_brush_t::stroke (const point_t &pt, canvas_t &canvas)
		{
			
		}
 void eraser_smooth_brush_t::stroke (unsigned int xpos, unsigned int ypos, canvas_t *canvas)
 {
   
 }

 void eraser_smooth_brush_t::stroke (unsigned int xpos, unsigned int ypos, unsigned int xpos1, unsigned int ypos1, canvas_t *canvas)
 {
	 int dx, dy, i, e;
	int incx, incy, inc1, inc2;
	int x,y;
	int r=get_size()-1;
	int w=canvas->get_width();
	int h=canvas->get_height();
	dx = xpos1-xpos;
	dy = ypos1-ypos;

	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	incx = 1;
	if (xpos1 < xpos) incx = -1;
	incy = 1;
	if (ypos1 < ypos) incy = -1;
	x = xpos; y = ypos;
	if (dx > dy) {
		for(int i=-1*r;i<=r;i++){
		for(int j=-1*r;j<=r;j++){
			if(i*i+j*j<=r*r){
				if(x+i>0&&x+i<w&&y+j>0&&y+j<h)
					canvas->erase_pixel(x+i,y+j);
			}
		}
		}		
		e = 2 * dy-dx;
		inc1 = 2*(dy-dx);
		inc2 = 2*dy;
		for (i=0; i<dx; i++) {
			if (e >= 0) {
				y += incy;
				e += inc1;
			}
			else
				e += inc2;
			x += incx;
			for(int i=-1*r;i<=r;i++){
				for(int j=-1*r;j<=r;j++){
					if(i*i+j*j<=r*r){
						if(x+i>0&&x+i<w&&y+j>0&&y+j<h)
							canvas->erase_pixel(x+i,y+j);
					}
				}
				}	
		}

	} else {
		for(int i=-1*r;i<=r;i++){
		for(int j=-1*r;j<=r;j++){
			if(i*i+j*j<=r*r){
				if(x+i>0&&x+i<w&&y+j>0&&y+j<h)
					canvas->erase_pixel(x+i,y+j);
			}
		}
		}	
		e = 2*dx-dy;
		inc1 = 2*(dx-dy);
		inc2 = 2*dx;
		for (i=0; i<dy; i++) {
			if (e >= 0) {
				x += incx;
				e += inc1;
			}
			else
				e += inc2;
			y += incy;
			for(int i=-1*r;i<=r;i++){
			for(int j=-1*r;j<=r;j++){
				if(i*i+j*j<=r*r){
					if(x+i>0&&x+i<w&&y+j>0&&y+j<h)
						canvas->erase_pixel(x+i,y+j);
				}
			}
			}	
		}
	}
 }
  
}