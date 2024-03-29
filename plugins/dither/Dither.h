/*
 * Copyright (C) 2011 Gabor Papp
 * http://mndl.hu/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DITHER_H
#define DITHER_H

#include "FFGLPlugin.h"
//#define DEBUG_GL
#include "DebugGL.h"
#include "GLSLProg.h"

class Dither : public FFGLPlugin
{
	public:
		Dither();
		Dither(FFGLViewportStruct *vps);
		~Dither();

		unsigned process_opengl(ProcessOpenGLStruct *pgl);

	private:
		static GLSLProg *shader;
		static const char *vertex_shader;
		static const char *fragment_shader;

		enum {
			PARAM_THR = 0,
			PARAM_PIXEL_WIDTH,
			PARAM_PIXEL_HEIGHT
		};
};

#endif

