// Copyright (C) 2009 Gabor Papp
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

#include <escheme.h>
#include <iostream>
#include <string>
#include <map>

#include "Video.h"

using namespace std;

map<int, Video *> Videos;

Scheme_Object *clear(int argc, Scheme_Object **argv)
{
	for (map<int, Video *>::iterator i = Videos.begin(); i != Videos.end(); ++i)
	{
		delete i->second;
	}
	Videos.clear();

	return scheme_void;
}

Scheme_Object *load(int argc, Scheme_Object **argv)
{
	char *filename = NULL;
	MZ_GC_DECL_REG(2);
	MZ_GC_VAR_IN_REG(0, argv);
	MZ_GC_VAR_IN_REG(1, filename);
	MZ_GC_REG();

	if (!SCHEME_CHAR_STRINGP(argv[0]))
		scheme_wrong_type("video-load", "string", 0, argc, argv);

	filename = scheme_utf8_encode_to_buffer(SCHEME_CHAR_STR_VAL(argv[0]),
			SCHEME_CHAR_STRLEN_VAL(argv[0]), NULL, 0);

	Video *v = new Video(filename);
	Videos[v->get_texture_id()] = v;

	MZ_GC_UNREG();
	return scheme_make_integer_value(v->get_texture_id());
}

Video *find_video(string func, Scheme_Object *sid)
{
	unsigned id = (unsigned)scheme_real_to_double(sid);
	map<int, Video *>::iterator i = Videos.find(id);
	if (i != Videos.end())
		return i->second;
	else
	{
		cerr << func << ": video " << id << " not found." << endl;
		return NULL;
	}
}

Scheme_Object *scheme_vector(float v0, float v1, float v2)
{
    Scheme_Object *ret = NULL;
    Scheme_Object *tmp = NULL;
    MZ_GC_DECL_REG(2);
    MZ_GC_VAR_IN_REG(0, ret);
    MZ_GC_VAR_IN_REG(1, tmp);
    MZ_GC_REG();
    ret = scheme_make_vector(3, scheme_void);
	SCHEME_VEC_ELS(ret)[0] = scheme_make_double(v0);
	SCHEME_VEC_ELS(ret)[1] = scheme_make_double(v1);
	SCHEME_VEC_ELS(ret)[2] = scheme_make_double(v2);

    MZ_GC_UNREG();
    return ret;
}

Scheme_Object *video_tcoords(int argc, Scheme_Object **argv)
{
	Scheme_Object *ret = NULL;
	MZ_GC_DECL_REG(1);
	MZ_GC_VAR_IN_REG(0, argv);
	MZ_GC_REG();
	if (!SCHEME_NUMBERP(argv[0]))
		scheme_wrong_type("video-tcoords", "number", 0, argc, argv);

	Video *v = find_video("video-tcoords", argv[0]);
	if (v != NULL)
	{
		Scheme_Object **coord_list = (Scheme_Object **)scheme_malloc(4 *
				sizeof(Scheme_Object *));

		float *coords  = v->video_tcoords();

		coord_list[0] = scheme_vector(coords[0], coords[4], coords[2]);
		coord_list[1] = scheme_vector(coords[3], coords[4], coords[5]);
		coord_list[2] = scheme_vector(coords[3], coords[1], coords[5]);
		coord_list[3] = scheme_vector(coords[0], coords[1], coords[2]);

		ret = scheme_build_list(4, coord_list);
	}
	else
	{
		ret = scheme_void;
	}

	MZ_GC_UNREG();
	return ret;
}

Scheme_Object *update(int argc, Scheme_Object **argv)
{
	MZ_GC_DECL_REG(1);
	MZ_GC_VAR_IN_REG(0, argv);
	MZ_GC_REG();
	if (!SCHEME_NUMBERP(argv[0]))
		scheme_wrong_type("video-update", "number", 0, argc, argv);

	Video *v = find_video("video-update", argv[0]);
	if (v != NULL)
		v->update();

	MZ_GC_UNREG();
    return scheme_void;
}

Scheme_Object *play(int argc, Scheme_Object **argv)
{
	MZ_GC_DECL_REG(1);
	MZ_GC_VAR_IN_REG(0, argv);
	MZ_GC_REG();
	if (!SCHEME_NUMBERP(argv[0]))
		scheme_wrong_type("video-play", "number", 0, argc, argv);

	Video *v = find_video("video-play", argv[0]);
	if (v != NULL)
		v->play();

	MZ_GC_UNREG();
    return scheme_void;
}

Scheme_Object *stop(int argc, Scheme_Object **argv)
{
	MZ_GC_DECL_REG(1);
	MZ_GC_VAR_IN_REG(0, argv);
	MZ_GC_REG();
	if (!SCHEME_NUMBERP(argv[0]))
		scheme_wrong_type("video-stop", "number", 0, argc, argv);

	Video *v = find_video("video-stop", argv[0]);
	if (v != NULL)
		v->stop();

	MZ_GC_UNREG();
    return scheme_void;
}

Scheme_Object *seek(int argc, Scheme_Object **argv)
{
	MZ_GC_DECL_REG(1);
	MZ_GC_VAR_IN_REG(0, argv);
	MZ_GC_REG();
	if (!SCHEME_NUMBERP(argv[0]))
		scheme_wrong_type("video-seek", "number", 0, argc, argv);
	if (!SCHEME_NUMBERP(argv[1]))
		scheme_wrong_type("video-seek", "number", 1, argc, argv);

	Video *v = find_video("video-seek", argv[0]);
	float pos = scheme_real_to_double(argv[1]);
	if (v != NULL)
		v->seek(pos);

	MZ_GC_UNREG();
    return scheme_void;
}

Scheme_Object *scheme_reload(Scheme_Env *env)
{
	Scheme_Env *menv = NULL;
	MZ_GC_DECL_REG(2);
	MZ_GC_VAR_IN_REG(0, env);
	MZ_GC_VAR_IN_REG(1, menv);
	MZ_GC_REG();

	// add all the modules from this extension
	menv = scheme_primitive_module(scheme_intern_symbol("fluxus-video"), env);

	scheme_add_global("video-clear-cache", scheme_make_prim_w_arity(clear, "video-clear-cache", 0, 0), menv);
	scheme_add_global("video-load", scheme_make_prim_w_arity(load, "load", 1, 1), menv);
	scheme_add_global("video-update", scheme_make_prim_w_arity(update, "video-update", 1, 1), menv);
	scheme_add_global("video-tcoords",
			scheme_make_prim_w_arity(video_tcoords, "video-tcoords", 1, 1), menv);
	scheme_add_global("video-play", scheme_make_prim_w_arity(play, "video-play", 1, 1), menv);
	scheme_add_global("video-stop", scheme_make_prim_w_arity(stop, "video-stop", 1, 1), menv);
	scheme_add_global("video-seek", scheme_make_prim_w_arity(seek, "video-seek", 2, 2), menv);

	scheme_finish_primitive_module(menv);
	MZ_GC_UNREG();

	return scheme_void;
}

Scheme_Object *scheme_initialize(Scheme_Env *env)
{
	return scheme_reload(env);
}

Scheme_Object *scheme_module_name()
{
	return scheme_intern_symbol("fluxus-video");
}

