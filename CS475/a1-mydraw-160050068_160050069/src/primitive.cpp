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
#include "primitive.hpp"
namespace mydraw 
{
	void primitive::draw(unsigned int xpos,unsigned int ypos,canvas_t* canvas)
	{
		// if(mode==0)
		// {

		// // }
		if(mode==1)
		{
			if(numpoint==0)
			{
				numpoint=1;
				xpos0=xpos;
				ypos0=ypos;
				if(state==0)
					canvas->get_context()->current_brush->stroke((unsigned int)xpos, (unsigned int)ypos, canvas);
				else if(state==1)
					canvas->get_context()->current_eraser->stroke((unsigned int)xpos, (unsigned int)ypos,canvas);
			}
			else if(numpoint==1){
				// numpoint=2;
				if(state==0)
					canvas->get_context()->current_smooth_brush->stroke((unsigned int)xpos0, (unsigned int)ypos0,(unsigned int)xpos, (unsigned int)ypos, canvas);
				else if(state==1)
					canvas->get_context()->current_smooth_eraser->stroke((unsigned int)xpos0, (unsigned int)ypos0,(unsigned int)xpos, (unsigned int)ypos,canvas);
				xpos0=xpos;
				ypos0=ypos;
			}
		}
		else if(mode==2)
		{
			if(numpoint==0)
			{
				numpoint=1;
				xpos0=xpos;
				ypos0=ypos;
				if(state==0)
					canvas->get_context()->current_brush->stroke((unsigned int)xpos, (unsigned int)ypos, canvas);
				else if(state==1)
					canvas->get_context()->current_eraser->stroke((unsigned int)xpos, (unsigned int)ypos,canvas);
			}
			else if(numpoint==1){
				numpoint=2;
				if(state==0)
					canvas->get_context()->current_brush->stroke((unsigned int)xpos, (unsigned int)ypos, canvas);
				else if(state==1)
					canvas->get_context()->current_eraser->stroke((unsigned int)xpos, (unsigned int)ypos,canvas);
				xpos1=xpos;
				ypos1=ypos;
			}
			else if(numpoint==2){
				numpoint=3;
				if(state==0){					
					canvas->get_context()->current_smooth_brush->stroke((unsigned int)xpos0, (unsigned int)ypos0,(unsigned int)xpos1, (unsigned int)ypos1, canvas);
					canvas->get_context()->current_smooth_brush->stroke((unsigned int)xpos0, (unsigned int)ypos0,(unsigned int)xpos, (unsigned int)ypos, canvas);
					canvas->get_context()->current_smooth_brush->stroke((unsigned int)xpos1, (unsigned int)ypos1,(unsigned int)xpos, (unsigned int)ypos, canvas);
				}
				else if(state==1){
					canvas->get_context()->current_smooth_eraser->stroke((unsigned int)xpos0, (unsigned int)ypos0,(unsigned int)xpos1, (unsigned int)ypos1, canvas);
					canvas->get_context()->current_smooth_eraser->stroke((unsigned int)xpos0, (unsigned int)ypos0,(unsigned int)xpos, (unsigned int)ypos, canvas);
					canvas->get_context()->current_smooth_eraser->stroke((unsigned int)xpos1, (unsigned int)ypos1,(unsigned int)xpos, (unsigned int)ypos, canvas);
				}
				xpos0=xpos1;ypos0=ypos1;
				xpos1=xpos;ypos1=ypos;
			}
			else if(numpoint==3){
				if(state==0){					
					canvas->get_context()->current_smooth_brush->stroke((unsigned int)xpos0, (unsigned int)ypos0,(unsigned int)xpos, (unsigned int)ypos, canvas);
					canvas->get_context()->current_smooth_brush->stroke((unsigned int)xpos1, (unsigned int)ypos1,(unsigned int)xpos, (unsigned int)ypos, canvas);
				}
				else if(state==1){
					canvas->get_context()->current_smooth_eraser->stroke((unsigned int)xpos0, (unsigned int)ypos0,(unsigned int)xpos, (unsigned int)ypos, canvas);
					canvas->get_context()->current_smooth_eraser->stroke((unsigned int)xpos1, (unsigned int)ypos1,(unsigned int)xpos, (unsigned int)ypos, canvas);
				}
				xpos0=xpos1;ypos0=ypos1;
				xpos1=xpos;ypos1=ypos;
			}
		}
	}
}


