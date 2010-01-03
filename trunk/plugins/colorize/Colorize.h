/*
 * Copyright (C) 2010 Gabor Papp
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

#ifndef COLORIZE_H
#define COLORIZE_H

#include "FFGLPlugin.h"

class Colorize : public FFGLPlugin
{
	public:
		Colorize();
		Colorize(FFGLViewportStruct *vps);
		~Colorize();

		unsigned process_opengl(ProcessOpenGLStruct *pgl);
};

#endif

