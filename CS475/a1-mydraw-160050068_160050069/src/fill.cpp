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
#include "fill.hpp"
#include <vector>
#include <list>
namespace mydraw{
	void floodfill_t::fill(color_t c,unsigned int wid,unsigned int hit,unsigned int x,unsigned int y,canvas_t * canvas)
	{
		std::vector<bool> v(hit+1,0);
		std::vector<std::vector<bool> > visited(wid+1,v);
		std::list<unsigned int> qx;
		std::list<unsigned int> qy;
		qx.push_back(x);
		qy.push_back(y);
		unsigned int x1,y1;
		while(!qx.empty())
		{
			x1=qx.front();
			y1=qy.front();
			visited[x1][y1]=1;
			if(canvas->get_pixel(x1,y1)==c && canvas->get_context()->brush_color!=c)
			{
				canvas->set_pixel(x1,y1);
				if(x1-1>0 && !visited[x1-1][y1])
				{
					qx.push_back(x1-1);
					qy.push_back(y1);
					
				}
				if(x1+1<wid && !visited[x1+1][y1])
				{
					qx.push_back(x1+1);
					qy.push_back(y1);
				}
				if(y1-1>0 && !visited[x1][y1-1])
				{
					qx.push_back(x1);
					qy.push_back(y1-1);
				}
				if(y+1<hit && !visited[x1][y1+1])
				{
					qx.push_back(x1);
					qy.push_back(y1+1);
				}
			}
			qx.pop_front();
			qy.pop_front();
		}
		// if(canvas->get_pixel(x,y)==c)
		// {
		// 	canvas->set_pixel(x,y);
		// 	if(x-1>0 && !visited[x-1][y])
		// 		fill(c,wid,hit,x-1,y,canvas,visited);
		// 	if(x+1<wid && !visited[x+1][y])
		// 		fill(c,wid,hit,x+1,y,canvas,visited);
		// 	if(y-1>0 && !visited[x][y-1])
		// 		fill(c,wid,hit,x,y-1,canvas,visited);
		// 	if(y+1<hit && !visited[x][y+1])
		// 		fill(c,wid,hit,x,y+1,canvas,visited);
		// }
	}
}