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

#pragma once

#include "brush.hpp"
#include "canvas.hpp"
// #include <glm/vec2.hpp>

namespace mydraw
{
	enum class primitive_mode_t
	{
		point,
		line,
		triangle
	};

	//2D point
	// typedef glm::vec2 point_t;
	class canvas_t;

	class primitive{
		public:
		int mode;   /// 0 point 1 line 2 triangle
		int state;  // 0 brush 1 eraser 2 fill
		int numpoint;
		primitive(){
			mode=0;
			state=0;
			numpoint=0;
		}
		~primitive(){}
		unsigned int xpos0,xpos1,ypos0,ypos1;
		void draw(unsigned int xpos,unsigned int ypos,canvas_t* canvas);

	};

	
}