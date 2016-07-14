
/*----------------------------------------------------------------------------
  chugl
  Chuck OpenGL library module

  Copyright (c) 2014 Spencer Salazar.  All rights reserved.
  https://ccrma.stanford.edu/~spencer/

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
  U.S.A.
-----------------------------------------------------------------------------*/

#include "chugl.h"
#include "chugl_opengl.h"

#include "chuck_dl.h"
#include "chuck_def.h"
#include "chuck_type.h"

#include "chugl_util.h"

#include "glplat.h"

// general includes
#include <stdio.h>
#include <limits.h>

t_CKINT Chuck_OpenGL_offset_chugl = 0;

CK_DLL_CTOR(Chuck_OpenGL_ctor)
{
    OBJ_MEMBER_OBJECT(SELF, Chuck_OpenGL_offset_chugl) = NULL;
}

static const t_CKINT Chuck_OpenGL_DEPTH_BUFFER_BIT = GL_DEPTH_BUFFER_BIT;
static const t_CKINT Chuck_OpenGL_STENCIL_BUFFER_BIT = GL_STENCIL_BUFFER_BIT;
static const t_CKINT Chuck_OpenGL_COLOR_BUFFER_BIT = GL_COLOR_BUFFER_BIT;
static const t_CKINT Chuck_OpenGL_FALSE = GL_FALSE;
static const t_CKINT Chuck_OpenGL_TRUE = GL_TRUE;
static const t_CKINT Chuck_OpenGL_POINTS = GL_POINTS;
static const t_CKINT Chuck_OpenGL_LINES = GL_LINES;
static const t_CKINT Chuck_OpenGL_LINE_LOOP = GL_LINE_LOOP;
static const t_CKINT Chuck_OpenGL_LINE_STRIP = GL_LINE_STRIP;
static const t_CKINT Chuck_OpenGL_TRIANGLES = GL_TRIANGLES;
static const t_CKINT Chuck_OpenGL_TRIANGLE_STRIP = GL_TRIANGLE_STRIP;
static const t_CKINT Chuck_OpenGL_TRIANGLE_FAN = GL_TRIANGLE_FAN;
static const t_CKINT Chuck_OpenGL_ZERO = GL_ZERO;
static const t_CKINT Chuck_OpenGL_ONE = GL_ONE;
static const t_CKINT Chuck_OpenGL_SRC_COLOR = GL_SRC_COLOR;
static const t_CKINT Chuck_OpenGL_ONE_MINUS_SRC_COLOR = GL_ONE_MINUS_SRC_COLOR;
static const t_CKINT Chuck_OpenGL_SRC_ALPHA = GL_SRC_ALPHA;
static const t_CKINT Chuck_OpenGL_ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA;
static const t_CKINT Chuck_OpenGL_DST_ALPHA = GL_DST_ALPHA;
static const t_CKINT Chuck_OpenGL_ONE_MINUS_DST_ALPHA = GL_ONE_MINUS_DST_ALPHA;
static const t_CKINT Chuck_OpenGL_DST_COLOR = GL_DST_COLOR;
static const t_CKINT Chuck_OpenGL_ONE_MINUS_DST_COLOR = GL_ONE_MINUS_DST_COLOR;
static const t_CKINT Chuck_OpenGL_SRC_ALPHA_SATURATE = GL_SRC_ALPHA_SATURATE;
static const t_CKINT Chuck_OpenGL_FUNC_ADD = GL_FUNC_ADD;
static const t_CKINT Chuck_OpenGL_BLEND_EQUATION = GL_BLEND_EQUATION;
static const t_CKINT Chuck_OpenGL_BLEND_EQUATION_RGB = GL_BLEND_EQUATION_RGB;
static const t_CKINT Chuck_OpenGL_BLEND_EQUATION_ALPHA = GL_BLEND_EQUATION_ALPHA;
static const t_CKINT Chuck_OpenGL_FUNC_SUBTRACT = GL_FUNC_SUBTRACT;
static const t_CKINT Chuck_OpenGL_FUNC_REVERSE_SUBTRACT = GL_FUNC_REVERSE_SUBTRACT;
static const t_CKINT Chuck_OpenGL_BLEND_DST_RGB = GL_BLEND_DST_RGB;
static const t_CKINT Chuck_OpenGL_BLEND_SRC_RGB = GL_BLEND_SRC_RGB;
static const t_CKINT Chuck_OpenGL_BLEND_DST_ALPHA = GL_BLEND_DST_ALPHA;
static const t_CKINT Chuck_OpenGL_BLEND_SRC_ALPHA = GL_BLEND_SRC_ALPHA;
static const t_CKINT Chuck_OpenGL_CONSTANT_COLOR = GL_CONSTANT_COLOR;
static const t_CKINT Chuck_OpenGL_ONE_MINUS_CONSTANT_COLOR = GL_ONE_MINUS_CONSTANT_COLOR;
static const t_CKINT Chuck_OpenGL_CONSTANT_ALPHA = GL_CONSTANT_ALPHA;
static const t_CKINT Chuck_OpenGL_ONE_MINUS_CONSTANT_ALPHA = GL_ONE_MINUS_CONSTANT_ALPHA;
static const t_CKINT Chuck_OpenGL_BLEND_COLOR = GL_BLEND_COLOR;
static const t_CKINT Chuck_OpenGL_ARRAY_BUFFER = GL_ARRAY_BUFFER;
static const t_CKINT Chuck_OpenGL_ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER;
static const t_CKINT Chuck_OpenGL_ARRAY_BUFFER_BINDING = GL_ARRAY_BUFFER_BINDING;
static const t_CKINT Chuck_OpenGL_ELEMENT_ARRAY_BUFFER_BINDING = GL_ELEMENT_ARRAY_BUFFER_BINDING;
static const t_CKINT Chuck_OpenGL_STREAM_DRAW = GL_STREAM_DRAW;
static const t_CKINT Chuck_OpenGL_STATIC_DRAW = GL_STATIC_DRAW;
static const t_CKINT Chuck_OpenGL_DYNAMIC_DRAW = GL_DYNAMIC_DRAW;
static const t_CKINT Chuck_OpenGL_BUFFER_SIZE = GL_BUFFER_SIZE;
static const t_CKINT Chuck_OpenGL_BUFFER_USAGE = GL_BUFFER_USAGE;
static const t_CKINT Chuck_OpenGL_CURRENT_VERTEX_ATTRIB = GL_CURRENT_VERTEX_ATTRIB;
static const t_CKINT Chuck_OpenGL_FRONT = GL_FRONT;
static const t_CKINT Chuck_OpenGL_BACK = GL_BACK;
static const t_CKINT Chuck_OpenGL_FRONT_AND_BACK = GL_FRONT_AND_BACK;
static const t_CKINT Chuck_OpenGL_TEXTURE_2D = GL_TEXTURE_2D;
static const t_CKINT Chuck_OpenGL_CULL_FACE = GL_CULL_FACE;
static const t_CKINT Chuck_OpenGL_BLEND = GL_BLEND;
static const t_CKINT Chuck_OpenGL_DITHER = GL_DITHER;
static const t_CKINT Chuck_OpenGL_STENCIL_TEST = GL_STENCIL_TEST;
static const t_CKINT Chuck_OpenGL_DEPTH_TEST = GL_DEPTH_TEST;
static const t_CKINT Chuck_OpenGL_SCISSOR_TEST = GL_SCISSOR_TEST;
static const t_CKINT Chuck_OpenGL_POLYGON_OFFSET_FILL = GL_POLYGON_OFFSET_FILL;
static const t_CKINT Chuck_OpenGL_SAMPLE_ALPHA_TO_COVERAGE = GL_SAMPLE_ALPHA_TO_COVERAGE;
static const t_CKINT Chuck_OpenGL_SAMPLE_COVERAGE = GL_SAMPLE_COVERAGE;
static const t_CKINT Chuck_OpenGL_NO_ERROR = GL_NO_ERROR;
static const t_CKINT Chuck_OpenGL_INVALID_ENUM = GL_INVALID_ENUM;
static const t_CKINT Chuck_OpenGL_INVALID_VALUE = GL_INVALID_VALUE;
static const t_CKINT Chuck_OpenGL_INVALID_OPERATION = GL_INVALID_OPERATION;
static const t_CKINT Chuck_OpenGL_OUT_OF_MEMORY = GL_OUT_OF_MEMORY;
static const t_CKINT Chuck_OpenGL_CW = GL_CW;
static const t_CKINT Chuck_OpenGL_CCW = GL_CCW;
static const t_CKINT Chuck_OpenGL_LINE_WIDTH = GL_LINE_WIDTH;
static const t_CKINT Chuck_OpenGL_ALIASED_POINT_SIZE_RANGE = GL_ALIASED_POINT_SIZE_RANGE;
static const t_CKINT Chuck_OpenGL_ALIASED_LINE_WIDTH_RANGE = GL_ALIASED_LINE_WIDTH_RANGE;
static const t_CKINT Chuck_OpenGL_CULL_FACE_MODE = GL_CULL_FACE_MODE;
static const t_CKINT Chuck_OpenGL_FRONT_FACE = GL_FRONT_FACE;
static const t_CKINT Chuck_OpenGL_DEPTH_RANGE = GL_DEPTH_RANGE;
static const t_CKINT Chuck_OpenGL_DEPTH_WRITEMASK = GL_DEPTH_WRITEMASK;
static const t_CKINT Chuck_OpenGL_DEPTH_CLEAR_VALUE = GL_DEPTH_CLEAR_VALUE;
static const t_CKINT Chuck_OpenGL_DEPTH_FUNC = GL_DEPTH_FUNC;
static const t_CKINT Chuck_OpenGL_STENCIL_CLEAR_VALUE = GL_STENCIL_CLEAR_VALUE;
static const t_CKINT Chuck_OpenGL_STENCIL_FUNC = GL_STENCIL_FUNC;
static const t_CKINT Chuck_OpenGL_STENCIL_FAIL = GL_STENCIL_FAIL;
static const t_CKINT Chuck_OpenGL_STENCIL_PASS_DEPTH_FAIL = GL_STENCIL_PASS_DEPTH_FAIL;
static const t_CKINT Chuck_OpenGL_STENCIL_PASS_DEPTH_PASS = GL_STENCIL_PASS_DEPTH_PASS;
static const t_CKINT Chuck_OpenGL_STENCIL_REF = GL_STENCIL_REF;
static const t_CKINT Chuck_OpenGL_STENCIL_VALUE_MASK = GL_STENCIL_VALUE_MASK;
static const t_CKINT Chuck_OpenGL_STENCIL_WRITEMASK = GL_STENCIL_WRITEMASK;
static const t_CKINT Chuck_OpenGL_STENCIL_BACK_FUNC = GL_STENCIL_BACK_FUNC;
static const t_CKINT Chuck_OpenGL_STENCIL_BACK_FAIL = GL_STENCIL_BACK_FAIL;
static const t_CKINT Chuck_OpenGL_STENCIL_BACK_PASS_DEPTH_FAIL = GL_STENCIL_BACK_PASS_DEPTH_FAIL;
static const t_CKINT Chuck_OpenGL_STENCIL_BACK_PASS_DEPTH_PASS = GL_STENCIL_BACK_PASS_DEPTH_PASS;
static const t_CKINT Chuck_OpenGL_STENCIL_BACK_REF = GL_STENCIL_BACK_REF;
static const t_CKINT Chuck_OpenGL_STENCIL_BACK_VALUE_MASK = GL_STENCIL_BACK_VALUE_MASK;
static const t_CKINT Chuck_OpenGL_STENCIL_BACK_WRITEMASK = GL_STENCIL_BACK_WRITEMASK;
static const t_CKINT Chuck_OpenGL_VIEWPORT = GL_VIEWPORT;
static const t_CKINT Chuck_OpenGL_SCISSOR_BOX = GL_SCISSOR_BOX;
static const t_CKINT Chuck_OpenGL_COLOR_CLEAR_VALUE = GL_COLOR_CLEAR_VALUE;
static const t_CKINT Chuck_OpenGL_COLOR_WRITEMASK = GL_COLOR_WRITEMASK;
static const t_CKINT Chuck_OpenGL_UNPACK_ALIGNMENT = GL_UNPACK_ALIGNMENT;
static const t_CKINT Chuck_OpenGL_PACK_ALIGNMENT = GL_PACK_ALIGNMENT;
static const t_CKINT Chuck_OpenGL_MAX_TEXTURE_SIZE = GL_MAX_TEXTURE_SIZE;
static const t_CKINT Chuck_OpenGL_MAX_VIEWPORT_DIMS = GL_MAX_VIEWPORT_DIMS;
static const t_CKINT Chuck_OpenGL_SUBPIXEL_BITS = GL_SUBPIXEL_BITS;
static const t_CKINT Chuck_OpenGL_RED_BITS = GL_RED_BITS;
static const t_CKINT Chuck_OpenGL_GREEN_BITS = GL_GREEN_BITS;
static const t_CKINT Chuck_OpenGL_BLUE_BITS = GL_BLUE_BITS;
static const t_CKINT Chuck_OpenGL_ALPHA_BITS = GL_ALPHA_BITS;
static const t_CKINT Chuck_OpenGL_DEPTH_BITS = GL_DEPTH_BITS;
static const t_CKINT Chuck_OpenGL_STENCIL_BITS = GL_STENCIL_BITS;
static const t_CKINT Chuck_OpenGL_POLYGON_OFFSET_UNITS = GL_POLYGON_OFFSET_UNITS;
static const t_CKINT Chuck_OpenGL_POLYGON_OFFSET_FACTOR = GL_POLYGON_OFFSET_FACTOR;
static const t_CKINT Chuck_OpenGL_TEXTURE_BINDING_2D = GL_TEXTURE_BINDING_2D;
static const t_CKINT Chuck_OpenGL_SAMPLE_BUFFERS = GL_SAMPLE_BUFFERS;
static const t_CKINT Chuck_OpenGL_SAMPLES = GL_SAMPLES;
static const t_CKINT Chuck_OpenGL_SAMPLE_COVERAGE_VALUE = GL_SAMPLE_COVERAGE_VALUE;
static const t_CKINT Chuck_OpenGL_SAMPLE_COVERAGE_INVERT = GL_SAMPLE_COVERAGE_INVERT;
static const t_CKINT Chuck_OpenGL_NUM_COMPRESSED_TEXTURE_FORMATS = GL_NUM_COMPRESSED_TEXTURE_FORMATS;
static const t_CKINT Chuck_OpenGL_COMPRESSED_TEXTURE_FORMATS = GL_COMPRESSED_TEXTURE_FORMATS;
static const t_CKINT Chuck_OpenGL_DONT_CARE = GL_DONT_CARE;
static const t_CKINT Chuck_OpenGL_FASTEST = GL_FASTEST;
static const t_CKINT Chuck_OpenGL_NICEST = GL_NICEST;
static const t_CKINT Chuck_OpenGL_GENERATE_MIPMAP_HINT = GL_GENERATE_MIPMAP_HINT;
static const t_CKINT Chuck_OpenGL_BYTE = GL_BYTE;
static const t_CKINT Chuck_OpenGL_UNSIGNED_BYTE = GL_UNSIGNED_BYTE;
static const t_CKINT Chuck_OpenGL_SHORT = GL_SHORT;
static const t_CKINT Chuck_OpenGL_UNSIGNED_SHORT = GL_UNSIGNED_SHORT;
static const t_CKINT Chuck_OpenGL_INT = GL_INT;
static const t_CKINT Chuck_OpenGL_UNSIGNED_INT = GL_UNSIGNED_INT;
static const t_CKINT Chuck_OpenGL_FLOAT = GL_FLOAT;
static const t_CKINT Chuck_OpenGL_FIXED = GL_FIXED;
static const t_CKINT Chuck_OpenGL_DEPTH_COMPONENT = GL_DEPTH_COMPONENT;
static const t_CKINT Chuck_OpenGL_ALPHA = GL_ALPHA;
static const t_CKINT Chuck_OpenGL_RGB = GL_RGB;
static const t_CKINT Chuck_OpenGL_RGBA = GL_RGBA;
static const t_CKINT Chuck_OpenGL_LUMINANCE = GL_LUMINANCE;
static const t_CKINT Chuck_OpenGL_LUMINANCE_ALPHA = GL_LUMINANCE_ALPHA;
static const t_CKINT Chuck_OpenGL_UNSIGNED_SHORT_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4;
static const t_CKINT Chuck_OpenGL_UNSIGNED_SHORT_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1;
static const t_CKINT Chuck_OpenGL_UNSIGNED_SHORT_5_6_5 = GL_UNSIGNED_SHORT_5_6_5;
static const t_CKINT Chuck_OpenGL_FRAGMENT_SHADER = GL_FRAGMENT_SHADER;
static const t_CKINT Chuck_OpenGL_VERTEX_SHADER = GL_VERTEX_SHADER;
static const t_CKINT Chuck_OpenGL_MAX_VERTEX_ATTRIBS = GL_MAX_VERTEX_ATTRIBS;
static const t_CKINT Chuck_OpenGL_MAX_VERTEX_UNIFORM_VECTORS = GL_MAX_VERTEX_UNIFORM_VECTORS;
static const t_CKINT Chuck_OpenGL_MAX_VARYING_VECTORS = GL_MAX_VARYING_VECTORS;
static const t_CKINT Chuck_OpenGL_MAX_COMBINED_TEXTURE_IMAGE_UNITS = GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS;
static const t_CKINT Chuck_OpenGL_MAX_VERTEX_TEXTURE_IMAGE_UNITS = GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS;
static const t_CKINT Chuck_OpenGL_MAX_TEXTURE_IMAGE_UNITS = GL_MAX_TEXTURE_IMAGE_UNITS;
static const t_CKINT Chuck_OpenGL_MAX_FRAGMENT_UNIFORM_VECTORS = GL_MAX_FRAGMENT_UNIFORM_VECTORS;
static const t_CKINT Chuck_OpenGL_SHADER_TYPE = GL_SHADER_TYPE;
static const t_CKINT Chuck_OpenGL_DELETE_STATUS = GL_DELETE_STATUS;
static const t_CKINT Chuck_OpenGL_LINK_STATUS = GL_LINK_STATUS;
static const t_CKINT Chuck_OpenGL_VALIDATE_STATUS = GL_VALIDATE_STATUS;
static const t_CKINT Chuck_OpenGL_ATTACHED_SHADERS = GL_ATTACHED_SHADERS;
static const t_CKINT Chuck_OpenGL_ACTIVE_UNIFORMS = GL_ACTIVE_UNIFORMS;
static const t_CKINT Chuck_OpenGL_ACTIVE_UNIFORM_MAX_LENGTH = GL_ACTIVE_UNIFORM_MAX_LENGTH;
static const t_CKINT Chuck_OpenGL_ACTIVE_ATTRIBUTES = GL_ACTIVE_ATTRIBUTES;
static const t_CKINT Chuck_OpenGL_ACTIVE_ATTRIBUTE_MAX_LENGTH = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH;
static const t_CKINT Chuck_OpenGL_SHADING_LANGUAGE_VERSION = GL_SHADING_LANGUAGE_VERSION;
static const t_CKINT Chuck_OpenGL_CURRENT_PROGRAM = GL_CURRENT_PROGRAM;
static const t_CKINT Chuck_OpenGL_NEVER = GL_NEVER;
static const t_CKINT Chuck_OpenGL_LESS = GL_LESS;
static const t_CKINT Chuck_OpenGL_EQUAL = GL_EQUAL;
static const t_CKINT Chuck_OpenGL_LEQUAL = GL_LEQUAL;
static const t_CKINT Chuck_OpenGL_GREATER = GL_GREATER;
static const t_CKINT Chuck_OpenGL_NOTEQUAL = GL_NOTEQUAL;
static const t_CKINT Chuck_OpenGL_GEQUAL = GL_GEQUAL;
static const t_CKINT Chuck_OpenGL_ALWAYS = GL_ALWAYS;
static const t_CKINT Chuck_OpenGL_KEEP = GL_KEEP;
static const t_CKINT Chuck_OpenGL_REPLACE = GL_REPLACE;
static const t_CKINT Chuck_OpenGL_INCR = GL_INCR;
static const t_CKINT Chuck_OpenGL_DECR = GL_DECR;
static const t_CKINT Chuck_OpenGL_INVERT = GL_INVERT;
static const t_CKINT Chuck_OpenGL_INCR_WRAP = GL_INCR_WRAP;
static const t_CKINT Chuck_OpenGL_DECR_WRAP = GL_DECR_WRAP;
static const t_CKINT Chuck_OpenGL_VENDOR = GL_VENDOR;
static const t_CKINT Chuck_OpenGL_RENDERER = GL_RENDERER;
static const t_CKINT Chuck_OpenGL_VERSION = GL_VERSION;
static const t_CKINT Chuck_OpenGL_EXTENSIONS = GL_EXTENSIONS;
static const t_CKINT Chuck_OpenGL_NEAREST = GL_NEAREST;
static const t_CKINT Chuck_OpenGL_LINEAR = GL_LINEAR;
static const t_CKINT Chuck_OpenGL_NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST;
static const t_CKINT Chuck_OpenGL_LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST;
static const t_CKINT Chuck_OpenGL_NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR;
static const t_CKINT Chuck_OpenGL_LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR;
static const t_CKINT Chuck_OpenGL_TEXTURE_MAG_FILTER = GL_TEXTURE_MAG_FILTER;
static const t_CKINT Chuck_OpenGL_TEXTURE_MIN_FILTER = GL_TEXTURE_MIN_FILTER;
static const t_CKINT Chuck_OpenGL_TEXTURE_WRAP_S = GL_TEXTURE_WRAP_S;
static const t_CKINT Chuck_OpenGL_TEXTURE_WRAP_T = GL_TEXTURE_WRAP_T;
static const t_CKINT Chuck_OpenGL_TEXTURE = GL_TEXTURE;
static const t_CKINT Chuck_OpenGL_TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP;
static const t_CKINT Chuck_OpenGL_TEXTURE_BINDING_CUBE_MAP = GL_TEXTURE_BINDING_CUBE_MAP;
static const t_CKINT Chuck_OpenGL_TEXTURE_CUBE_MAP_POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
static const t_CKINT Chuck_OpenGL_TEXTURE_CUBE_MAP_NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
static const t_CKINT Chuck_OpenGL_TEXTURE_CUBE_MAP_POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
static const t_CKINT Chuck_OpenGL_TEXTURE_CUBE_MAP_NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
static const t_CKINT Chuck_OpenGL_TEXTURE_CUBE_MAP_POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
static const t_CKINT Chuck_OpenGL_TEXTURE_CUBE_MAP_NEGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
static const t_CKINT Chuck_OpenGL_MAX_CUBE_MAP_TEXTURE_SIZE = GL_MAX_CUBE_MAP_TEXTURE_SIZE;
static const t_CKINT Chuck_OpenGL_TEXTURE0 = GL_TEXTURE0;
static const t_CKINT Chuck_OpenGL_TEXTURE1 = GL_TEXTURE1;
static const t_CKINT Chuck_OpenGL_TEXTURE2 = GL_TEXTURE2;
static const t_CKINT Chuck_OpenGL_TEXTURE3 = GL_TEXTURE3;
static const t_CKINT Chuck_OpenGL_TEXTURE4 = GL_TEXTURE4;
static const t_CKINT Chuck_OpenGL_TEXTURE5 = GL_TEXTURE5;
static const t_CKINT Chuck_OpenGL_TEXTURE6 = GL_TEXTURE6;
static const t_CKINT Chuck_OpenGL_TEXTURE7 = GL_TEXTURE7;
static const t_CKINT Chuck_OpenGL_TEXTURE8 = GL_TEXTURE8;
static const t_CKINT Chuck_OpenGL_TEXTURE9 = GL_TEXTURE9;
static const t_CKINT Chuck_OpenGL_TEXTURE10 = GL_TEXTURE10;
static const t_CKINT Chuck_OpenGL_TEXTURE11 = GL_TEXTURE11;
static const t_CKINT Chuck_OpenGL_TEXTURE12 = GL_TEXTURE12;
static const t_CKINT Chuck_OpenGL_TEXTURE13 = GL_TEXTURE13;
static const t_CKINT Chuck_OpenGL_TEXTURE14 = GL_TEXTURE14;
static const t_CKINT Chuck_OpenGL_TEXTURE15 = GL_TEXTURE15;
static const t_CKINT Chuck_OpenGL_TEXTURE16 = GL_TEXTURE16;
static const t_CKINT Chuck_OpenGL_TEXTURE17 = GL_TEXTURE17;
static const t_CKINT Chuck_OpenGL_TEXTURE18 = GL_TEXTURE18;
static const t_CKINT Chuck_OpenGL_TEXTURE19 = GL_TEXTURE19;
static const t_CKINT Chuck_OpenGL_TEXTURE20 = GL_TEXTURE20;
static const t_CKINT Chuck_OpenGL_TEXTURE21 = GL_TEXTURE21;
static const t_CKINT Chuck_OpenGL_TEXTURE22 = GL_TEXTURE22;
static const t_CKINT Chuck_OpenGL_TEXTURE23 = GL_TEXTURE23;
static const t_CKINT Chuck_OpenGL_TEXTURE24 = GL_TEXTURE24;
static const t_CKINT Chuck_OpenGL_TEXTURE25 = GL_TEXTURE25;
static const t_CKINT Chuck_OpenGL_TEXTURE26 = GL_TEXTURE26;
static const t_CKINT Chuck_OpenGL_TEXTURE27 = GL_TEXTURE27;
static const t_CKINT Chuck_OpenGL_TEXTURE28 = GL_TEXTURE28;
static const t_CKINT Chuck_OpenGL_TEXTURE29 = GL_TEXTURE29;
static const t_CKINT Chuck_OpenGL_TEXTURE30 = GL_TEXTURE30;
static const t_CKINT Chuck_OpenGL_TEXTURE31 = GL_TEXTURE31;
static const t_CKINT Chuck_OpenGL_ACTIVE_TEXTURE = GL_ACTIVE_TEXTURE;
static const t_CKINT Chuck_OpenGL_REPEAT = GL_REPEAT;
static const t_CKINT Chuck_OpenGL_CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE;
static const t_CKINT Chuck_OpenGL_MIRRORED_REPEAT = GL_MIRRORED_REPEAT;
static const t_CKINT Chuck_OpenGL_FLOAT_VEC2 = GL_FLOAT_VEC2;
static const t_CKINT Chuck_OpenGL_FLOAT_VEC3 = GL_FLOAT_VEC3;
static const t_CKINT Chuck_OpenGL_FLOAT_VEC4 = GL_FLOAT_VEC4;
static const t_CKINT Chuck_OpenGL_INT_VEC2 = GL_INT_VEC2;
static const t_CKINT Chuck_OpenGL_INT_VEC3 = GL_INT_VEC3;
static const t_CKINT Chuck_OpenGL_INT_VEC4 = GL_INT_VEC4;
static const t_CKINT Chuck_OpenGL_BOOL = GL_BOOL;
static const t_CKINT Chuck_OpenGL_BOOL_VEC2 = GL_BOOL_VEC2;
static const t_CKINT Chuck_OpenGL_BOOL_VEC3 = GL_BOOL_VEC3;
static const t_CKINT Chuck_OpenGL_BOOL_VEC4 = GL_BOOL_VEC4;
static const t_CKINT Chuck_OpenGL_FLOAT_MAT2 = GL_FLOAT_MAT2;
static const t_CKINT Chuck_OpenGL_FLOAT_MAT3 = GL_FLOAT_MAT3;
static const t_CKINT Chuck_OpenGL_FLOAT_MAT4 = GL_FLOAT_MAT4;
static const t_CKINT Chuck_OpenGL_SAMPLER_2D = GL_SAMPLER_2D;
static const t_CKINT Chuck_OpenGL_SAMPLER_CUBE = GL_SAMPLER_CUBE;
static const t_CKINT Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_ENABLED = GL_VERTEX_ATTRIB_ARRAY_ENABLED;
static const t_CKINT Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_SIZE = GL_VERTEX_ATTRIB_ARRAY_SIZE;
static const t_CKINT Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_STRIDE = GL_VERTEX_ATTRIB_ARRAY_STRIDE;
static const t_CKINT Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_TYPE = GL_VERTEX_ATTRIB_ARRAY_TYPE;
static const t_CKINT Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_NORMALIZED = GL_VERTEX_ATTRIB_ARRAY_NORMALIZED;
static const t_CKINT Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_POINTER = GL_VERTEX_ATTRIB_ARRAY_POINTER;
static const t_CKINT Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING = GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING;
static const t_CKINT Chuck_OpenGL_IMPLEMENTATION_COLOR_READ_TYPE = GL_IMPLEMENTATION_COLOR_READ_TYPE;
static const t_CKINT Chuck_OpenGL_IMPLEMENTATION_COLOR_READ_FORMAT = GL_IMPLEMENTATION_COLOR_READ_FORMAT;
static const t_CKINT Chuck_OpenGL_COMPILE_STATUS = GL_COMPILE_STATUS;
static const t_CKINT Chuck_OpenGL_INFO_LOG_LENGTH = GL_INFO_LOG_LENGTH;
static const t_CKINT Chuck_OpenGL_SHADER_SOURCE_LENGTH = GL_SHADER_SOURCE_LENGTH;
static const t_CKINT Chuck_OpenGL_SHADER_COMPILER = GL_SHADER_COMPILER;
static const t_CKINT Chuck_OpenGL_SHADER_BINARY_FORMATS = GL_SHADER_BINARY_FORMATS;
static const t_CKINT Chuck_OpenGL_NUM_SHADER_BINARY_FORMATS = GL_NUM_SHADER_BINARY_FORMATS;
static const t_CKINT Chuck_OpenGL_LOW_FLOAT = GL_LOW_FLOAT;
static const t_CKINT Chuck_OpenGL_MEDIUM_FLOAT = GL_MEDIUM_FLOAT;
static const t_CKINT Chuck_OpenGL_HIGH_FLOAT = GL_HIGH_FLOAT;
static const t_CKINT Chuck_OpenGL_LOW_INT = GL_LOW_INT;
static const t_CKINT Chuck_OpenGL_MEDIUM_INT = GL_MEDIUM_INT;
static const t_CKINT Chuck_OpenGL_HIGH_INT = GL_HIGH_INT;
static const t_CKINT Chuck_OpenGL_FRAMEBUFFER = GL_FRAMEBUFFER;
static const t_CKINT Chuck_OpenGL_RENDERBUFFER = GL_RENDERBUFFER;
static const t_CKINT Chuck_OpenGL_RGBA4 = GL_RGBA4;
static const t_CKINT Chuck_OpenGL_RGB5_A1 = GL_RGB5_A1;
static const t_CKINT Chuck_OpenGL_RGB565 = GL_RGB565;
static const t_CKINT Chuck_OpenGL_DEPTH_COMPONENT16 = GL_DEPTH_COMPONENT16;
static const t_CKINT Chuck_OpenGL_STENCIL_INDEX8 = GL_STENCIL_INDEX8;
static const t_CKINT Chuck_OpenGL_RENDERBUFFER_WIDTH = GL_RENDERBUFFER_WIDTH;
static const t_CKINT Chuck_OpenGL_RENDERBUFFER_HEIGHT = GL_RENDERBUFFER_HEIGHT;
static const t_CKINT Chuck_OpenGL_RENDERBUFFER_INTERNAL_FORMAT = GL_RENDERBUFFER_INTERNAL_FORMAT;
static const t_CKINT Chuck_OpenGL_RENDERBUFFER_RED_SIZE = GL_RENDERBUFFER_RED_SIZE;
static const t_CKINT Chuck_OpenGL_RENDERBUFFER_GREEN_SIZE = GL_RENDERBUFFER_GREEN_SIZE;
static const t_CKINT Chuck_OpenGL_RENDERBUFFER_BLUE_SIZE = GL_RENDERBUFFER_BLUE_SIZE;
static const t_CKINT Chuck_OpenGL_RENDERBUFFER_ALPHA_SIZE = GL_RENDERBUFFER_ALPHA_SIZE;
static const t_CKINT Chuck_OpenGL_RENDERBUFFER_DEPTH_SIZE = GL_RENDERBUFFER_DEPTH_SIZE;
static const t_CKINT Chuck_OpenGL_RENDERBUFFER_STENCIL_SIZE = GL_RENDERBUFFER_STENCIL_SIZE;
static const t_CKINT Chuck_OpenGL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE = GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE;
static const t_CKINT Chuck_OpenGL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME = GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME;
static const t_CKINT Chuck_OpenGL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL = GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL;
static const t_CKINT Chuck_OpenGL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE = GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE;
static const t_CKINT Chuck_OpenGL_COLOR_ATTACHMENT0 = GL_COLOR_ATTACHMENT0;
static const t_CKINT Chuck_OpenGL_DEPTH_ATTACHMENT = GL_DEPTH_ATTACHMENT;
static const t_CKINT Chuck_OpenGL_STENCIL_ATTACHMENT = GL_STENCIL_ATTACHMENT;
static const t_CKINT Chuck_OpenGL_NONE = GL_NONE;
static const t_CKINT Chuck_OpenGL_FRAMEBUFFER_COMPLETE = GL_FRAMEBUFFER_COMPLETE;
static const t_CKINT Chuck_OpenGL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT;
static const t_CKINT Chuck_OpenGL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT;
static const t_CKINT Chuck_OpenGL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS = GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS;
static const t_CKINT Chuck_OpenGL_FRAMEBUFFER_UNSUPPORTED = GL_FRAMEBUFFER_UNSUPPORTED;
static const t_CKINT Chuck_OpenGL_FRAMEBUFFER_BINDING = GL_FRAMEBUFFER_BINDING;
static const t_CKINT Chuck_OpenGL_RENDERBUFFER_BINDING = GL_RENDERBUFFER_BINDING;
static const t_CKINT Chuck_OpenGL_MAX_RENDERBUFFER_SIZE = GL_MAX_RENDERBUFFER_SIZE;
static const t_CKINT Chuck_OpenGL_INVALID_FRAMEBUFFER_OPERATION = GL_INVALID_FRAMEBUFFER_OPERATION;

CK_DLL_MFUN(Chuck_OpenGL_ActiveTexture)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_texture = GET_NEXT_INT(ARGS);

    glActiveTexture(arg_texture);
}


CK_DLL_MFUN(Chuck_OpenGL_AttachShader)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);
    t_CKINT arg_shader = GET_NEXT_INT(ARGS);

    glAttachShader(arg_program, arg_shader);
}


CK_DLL_MFUN(Chuck_OpenGL_BindAttribLocation)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_name_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLchar *arg_name = new GLchar[arg_name_arr->size()];
    chgl->scheduleDataForCleanup(arg_name);
    copy_ckarray4_to_array(arg_name, arg_name_arr);

    glBindAttribLocation(arg_program, arg_index, arg_name);
}


CK_DLL_MFUN(Chuck_OpenGL_BindBuffer)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_buffer = GET_NEXT_INT(ARGS);

    glBindBuffer(arg_target, arg_buffer);
}


CK_DLL_MFUN(Chuck_OpenGL_BindFramebuffer)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_framebuffer = GET_NEXT_INT(ARGS);

    glBindFramebuffer(arg_target, arg_framebuffer);
}


CK_DLL_MFUN(Chuck_OpenGL_BindRenderbuffer)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_renderbuffer = GET_NEXT_INT(ARGS);

    glBindRenderbuffer(arg_target, arg_renderbuffer);
}


CK_DLL_MFUN(Chuck_OpenGL_BindTexture)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_texture = GET_NEXT_INT(ARGS);

    glBindTexture(arg_target, arg_texture);
}


CK_DLL_MFUN(Chuck_OpenGL_BlendColor)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKFLOAT arg_red = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_green = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_blue = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_alpha = GET_NEXT_FLOAT(ARGS);

    glBlendColor(arg_red, arg_green, arg_blue, arg_alpha);
}


CK_DLL_MFUN(Chuck_OpenGL_BlendEquation)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_mode = GET_NEXT_INT(ARGS);

    glBlendEquation(arg_mode);
}


CK_DLL_MFUN(Chuck_OpenGL_BlendEquationSeparate)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_modeRGB = GET_NEXT_INT(ARGS);
    t_CKINT arg_modeAlpha = GET_NEXT_INT(ARGS);

    glBlendEquationSeparate(arg_modeRGB, arg_modeAlpha);
}


CK_DLL_MFUN(Chuck_OpenGL_BlendFunc)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_sfactor = GET_NEXT_INT(ARGS);
    t_CKINT arg_dfactor = GET_NEXT_INT(ARGS);

    glBlendFunc(arg_sfactor, arg_dfactor);
}


CK_DLL_MFUN(Chuck_OpenGL_BlendFuncSeparate)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_sfactorRGB = GET_NEXT_INT(ARGS);
    t_CKINT arg_dfactorRGB = GET_NEXT_INT(ARGS);
    t_CKINT arg_sfactorAlpha = GET_NEXT_INT(ARGS);
    t_CKINT arg_dfactorAlpha = GET_NEXT_INT(ARGS);

    glBlendFuncSeparate(arg_sfactorRGB, arg_dfactorRGB, arg_sfactorAlpha, arg_dfactorAlpha);
}


CK_DLL_MFUN(Chuck_OpenGL_CheckFramebufferStatus)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);

    RETURN->v_int = glCheckFramebufferStatus(arg_target);
}


CK_DLL_MFUN(Chuck_OpenGL_Clear)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_mask = GET_NEXT_INT(ARGS);

    glClear(arg_mask);
}


CK_DLL_MFUN(Chuck_OpenGL_ClearColor)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKFLOAT arg_red = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_green = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_blue = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_alpha = GET_NEXT_FLOAT(ARGS);

    glClearColor(arg_red, arg_green, arg_blue, arg_alpha);
}


CK_DLL_MFUN(Chuck_OpenGL_ClearDepthf)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKFLOAT arg_d = GET_NEXT_FLOAT(ARGS);

    glClearDepthf(arg_d);
}


CK_DLL_MFUN(Chuck_OpenGL_ClearStencil)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_s = GET_NEXT_INT(ARGS);

    glClearStencil(arg_s);
}


CK_DLL_MFUN(Chuck_OpenGL_ColorMask)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_red = GET_NEXT_INT(ARGS);
    t_CKINT arg_green = GET_NEXT_INT(ARGS);
    t_CKINT arg_blue = GET_NEXT_INT(ARGS);
    t_CKINT arg_alpha = GET_NEXT_INT(ARGS);

    glColorMask(arg_red, arg_green, arg_blue, arg_alpha);
}


CK_DLL_MFUN(Chuck_OpenGL_CompileShader)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_shader = GET_NEXT_INT(ARGS);

    glCompileShader(arg_shader);
}


CK_DLL_MFUN(Chuck_OpenGL_CompressedTexImage2D)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);
    t_CKINT arg_internalformat = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_height = GET_NEXT_INT(ARGS);
    t_CKINT arg_border = GET_NEXT_INT(ARGS);
    t_CKINT arg_imageSize = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_data_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_data;
    if(_arg_data_arr->data_type_kind() == CHUCK_ARRAY4_DATAKIND)
    {
        Chuck_Array4 *arg_data_arr = (Chuck_Array4 *) _arg_data_arr;
        GLubyte *arg_data_v = new GLubyte[arg_data_arr->size()];
        chgl->scheduleDataForCleanup(arg_data_v);
        copy_ckarray4_to_array(arg_data_v, arg_data_arr);
        arg_data = (void *) arg_data_v;
    }
    else if(_arg_data_arr->data_type_kind() == CHUCK_ARRAY8_DATAKIND)
    {
        Chuck_Array4 *arg_data_arr = (Chuck_Array4 *) _arg_data_arr;
        arg_data_arr->add_ref();
        chgl->scheduleArrayForCleanup(arg_data_arr);
        arg_data = (void *) &(arg_data_arr->m_vector.front());
    }
    else
    {
        assert(0);
    }

    glCompressedTexImage2D(arg_target, arg_level, arg_internalformat, arg_width, arg_height, arg_border, arg_imageSize, arg_data);
}


CK_DLL_MFUN(Chuck_OpenGL_CompressedTexSubImage2D)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);
    t_CKINT arg_xoffset = GET_NEXT_INT(ARGS);
    t_CKINT arg_yoffset = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_height = GET_NEXT_INT(ARGS);
    t_CKINT arg_format = GET_NEXT_INT(ARGS);
    t_CKINT arg_imageSize = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_data_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_data;
    if(_arg_data_arr->data_type_kind() == CHUCK_ARRAY4_DATAKIND)
    {
        Chuck_Array4 *arg_data_arr = (Chuck_Array4 *) _arg_data_arr;
        GLubyte *arg_data_v = new GLubyte[arg_data_arr->size()];
        chgl->scheduleDataForCleanup(arg_data_v);
        copy_ckarray4_to_array(arg_data_v, arg_data_arr);
        arg_data = (void *) arg_data_v;
    }
    else if(_arg_data_arr->data_type_kind() == CHUCK_ARRAY8_DATAKIND)
    {
        Chuck_Array4 *arg_data_arr = (Chuck_Array4 *) _arg_data_arr;
        arg_data_arr->add_ref();
        chgl->scheduleArrayForCleanup(arg_data_arr);
        arg_data = (void *) &(arg_data_arr->m_vector.front());
    }
    else
    {
        assert(0);
    }

    glCompressedTexSubImage2D(arg_target, arg_level, arg_xoffset, arg_yoffset, arg_width, arg_height, arg_format, arg_imageSize, arg_data);
}


CK_DLL_MFUN(Chuck_OpenGL_CopyTexImage2D)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);
    t_CKINT arg_internalformat = GET_NEXT_INT(ARGS);
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_height = GET_NEXT_INT(ARGS);
    t_CKINT arg_border = GET_NEXT_INT(ARGS);

    glCopyTexImage2D(arg_target, arg_level, arg_internalformat, arg_x, arg_y, arg_width, arg_height, arg_border);
}


CK_DLL_MFUN(Chuck_OpenGL_CopyTexSubImage2D)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);
    t_CKINT arg_xoffset = GET_NEXT_INT(ARGS);
    t_CKINT arg_yoffset = GET_NEXT_INT(ARGS);
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_height = GET_NEXT_INT(ARGS);

    glCopyTexSubImage2D(arg_target, arg_level, arg_xoffset, arg_yoffset, arg_x, arg_y, arg_width, arg_height);
}


CK_DLL_MFUN(Chuck_OpenGL_CreateProgram)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    

    RETURN->v_int = glCreateProgram();
}


CK_DLL_MFUN(Chuck_OpenGL_CreateShader)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_type = GET_NEXT_INT(ARGS);

    RETURN->v_int = glCreateShader(arg_type);
}


CK_DLL_MFUN(Chuck_OpenGL_CullFace)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_mode = GET_NEXT_INT(ARGS);

    glCullFace(arg_mode);
}


CK_DLL_MFUN(Chuck_OpenGL_DeleteBuffers)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_n = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_buffers_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_buffers = new GLuint[arg_buffers_arr->size()];
    chgl->scheduleDataForCleanup(arg_buffers);
    copy_ckarray4_to_array(arg_buffers, arg_buffers_arr);

    glDeleteBuffers(arg_n, arg_buffers);
}


CK_DLL_MFUN(Chuck_OpenGL_DeleteFramebuffers)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_n = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_framebuffers_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_framebuffers = new GLuint[arg_framebuffers_arr->size()];
    chgl->scheduleDataForCleanup(arg_framebuffers);
    copy_ckarray4_to_array(arg_framebuffers, arg_framebuffers_arr);

    glDeleteFramebuffers(arg_n, arg_framebuffers);
}


CK_DLL_MFUN(Chuck_OpenGL_DeleteProgram)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);

    glDeleteProgram(arg_program);
}


CK_DLL_MFUN(Chuck_OpenGL_DeleteRenderbuffers)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_n = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_renderbuffers_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_renderbuffers = new GLuint[arg_renderbuffers_arr->size()];
    chgl->scheduleDataForCleanup(arg_renderbuffers);
    copy_ckarray4_to_array(arg_renderbuffers, arg_renderbuffers_arr);

    glDeleteRenderbuffers(arg_n, arg_renderbuffers);
}


CK_DLL_MFUN(Chuck_OpenGL_DeleteShader)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_shader = GET_NEXT_INT(ARGS);

    glDeleteShader(arg_shader);
}


CK_DLL_MFUN(Chuck_OpenGL_DeleteTextures)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_n = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_textures_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_textures = new GLuint[arg_textures_arr->size()];
    chgl->scheduleDataForCleanup(arg_textures);
    copy_ckarray4_to_array(arg_textures, arg_textures_arr);

    glDeleteTextures(arg_n, arg_textures);
}


CK_DLL_MFUN(Chuck_OpenGL_DepthFunc)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_func = GET_NEXT_INT(ARGS);

    glDepthFunc(arg_func);
}


CK_DLL_MFUN(Chuck_OpenGL_DepthMask)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_flag = GET_NEXT_INT(ARGS);

    glDepthMask(arg_flag);
}


CK_DLL_MFUN(Chuck_OpenGL_DepthRangef)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKFLOAT arg_n = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_f = GET_NEXT_FLOAT(ARGS);

    glDepthRangef(arg_n, arg_f);
}


CK_DLL_MFUN(Chuck_OpenGL_DetachShader)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);
    t_CKINT arg_shader = GET_NEXT_INT(ARGS);

    glDetachShader(arg_program, arg_shader);
}


CK_DLL_MFUN(Chuck_OpenGL_Disable)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_cap = GET_NEXT_INT(ARGS);

    glDisable(arg_cap);
}


CK_DLL_MFUN(Chuck_OpenGL_DisableVertexAttribArray)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);

    glDisableVertexAttribArray(arg_index);
}


CK_DLL_MFUN(Chuck_OpenGL_DrawArrays)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_mode = GET_NEXT_INT(ARGS);
    t_CKINT arg_first = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);

    glDrawArrays(arg_mode, arg_first, arg_count);
}


CK_DLL_MFUN(Chuck_OpenGL_DrawElements)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_mode = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    t_CKINT arg_type = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_indices_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_indices;
    if(_arg_indices_arr->data_type_kind() == CHUCK_ARRAY4_DATAKIND)
    {
        Chuck_Array4 *arg_indices_arr = (Chuck_Array4 *) _arg_indices_arr;
        GLubyte *arg_indices_v = new GLubyte[arg_indices_arr->size()];
        chgl->scheduleDataForCleanup(arg_indices_v);
        copy_ckarray4_to_array(arg_indices_v, arg_indices_arr);
        arg_indices = (void *) arg_indices_v;
    }
    else if(_arg_indices_arr->data_type_kind() == CHUCK_ARRAY8_DATAKIND)
    {
        Chuck_Array4 *arg_indices_arr = (Chuck_Array4 *) _arg_indices_arr;
        arg_indices_arr->add_ref();
        chgl->scheduleArrayForCleanup(arg_indices_arr);
        arg_indices = (void *) &(arg_indices_arr->m_vector.front());
    }
    else
    {
        assert(0);
    }

    glDrawElements(arg_mode, arg_count, arg_type, arg_indices);
}


CK_DLL_MFUN(Chuck_OpenGL_Enable)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_cap = GET_NEXT_INT(ARGS);

    glEnable(arg_cap);
}


CK_DLL_MFUN(Chuck_OpenGL_EnableVertexAttribArray)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);

    glEnableVertexAttribArray(arg_index);
}


CK_DLL_MFUN(Chuck_OpenGL_Finish)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    

    glFinish();
}


CK_DLL_MFUN(Chuck_OpenGL_Flush)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    

    glFlush();
}


CK_DLL_MFUN(Chuck_OpenGL_FramebufferRenderbuffer)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_attachment = GET_NEXT_INT(ARGS);
    t_CKINT arg_renderbuffertarget = GET_NEXT_INT(ARGS);
    t_CKINT arg_renderbuffer = GET_NEXT_INT(ARGS);

    glFramebufferRenderbuffer(arg_target, arg_attachment, arg_renderbuffertarget, arg_renderbuffer);
}


CK_DLL_MFUN(Chuck_OpenGL_FramebufferTexture2D)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_attachment = GET_NEXT_INT(ARGS);
    t_CKINT arg_textarget = GET_NEXT_INT(ARGS);
    t_CKINT arg_texture = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);

    glFramebufferTexture2D(arg_target, arg_attachment, arg_textarget, arg_texture, arg_level);
}


CK_DLL_MFUN(Chuck_OpenGL_FrontFace)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_mode = GET_NEXT_INT(ARGS);

    glFrontFace(arg_mode);
}


CK_DLL_MFUN(Chuck_OpenGL_GenBuffers)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_n = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_buffers_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_buffers = new GLuint[arg_buffers_arr->size()];
    chgl->scheduleDataForCleanup(arg_buffers);
    copy_ckarray4_to_array(arg_buffers, arg_buffers_arr);

    glGenBuffers(arg_n, arg_buffers);
}


CK_DLL_MFUN(Chuck_OpenGL_GenerateMipmap)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);

    glGenerateMipmap(arg_target);
}


CK_DLL_MFUN(Chuck_OpenGL_GenFramebuffers)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_n = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_framebuffers_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_framebuffers = new GLuint[arg_framebuffers_arr->size()];
    chgl->scheduleDataForCleanup(arg_framebuffers);
    copy_ckarray4_to_array(arg_framebuffers, arg_framebuffers_arr);

    glGenFramebuffers(arg_n, arg_framebuffers);
}


CK_DLL_MFUN(Chuck_OpenGL_GenRenderbuffers)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_n = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_renderbuffers_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_renderbuffers = new GLuint[arg_renderbuffers_arr->size()];
    chgl->scheduleDataForCleanup(arg_renderbuffers);
    copy_ckarray4_to_array(arg_renderbuffers, arg_renderbuffers_arr);

    glGenRenderbuffers(arg_n, arg_renderbuffers);
}


CK_DLL_MFUN(Chuck_OpenGL_GenTextures)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_n = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_textures_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_textures = new GLuint[arg_textures_arr->size()];
    chgl->scheduleDataForCleanup(arg_textures);
    copy_ckarray4_to_array(arg_textures, arg_textures_arr);

    glGenTextures(arg_n, arg_textures);
}


CK_DLL_MFUN(Chuck_OpenGL_GetActiveAttrib)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKINT arg_bufSize = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_length_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLsizei *arg_length = new GLsizei[arg_length_arr->size()];
    chgl->scheduleDataForCleanup(arg_length);
    copy_ckarray4_to_array(arg_length, arg_length_arr);
    Chuck_Array4 *arg_size_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_size = new GLint[arg_size_arr->size()];
    chgl->scheduleDataForCleanup(arg_size);
    copy_ckarray4_to_array(arg_size, arg_size_arr);
    Chuck_Array4 *arg_type_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLenum *arg_type = new GLenum[arg_type_arr->size()];
    chgl->scheduleDataForCleanup(arg_type);
    copy_ckarray4_to_array(arg_type, arg_type_arr);
    Chuck_Array4 *arg_name_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLchar *arg_name = new GLchar[arg_name_arr->size()];
    chgl->scheduleDataForCleanup(arg_name);
    copy_ckarray4_to_array(arg_name, arg_name_arr);

    glGetActiveAttrib(arg_program, arg_index, arg_bufSize, arg_length, arg_size, arg_type, arg_name);
}


CK_DLL_MFUN(Chuck_OpenGL_GetActiveUniform)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKINT arg_bufSize = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_length_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLsizei *arg_length = new GLsizei[arg_length_arr->size()];
    chgl->scheduleDataForCleanup(arg_length);
    copy_ckarray4_to_array(arg_length, arg_length_arr);
    Chuck_Array4 *arg_size_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_size = new GLint[arg_size_arr->size()];
    chgl->scheduleDataForCleanup(arg_size);
    copy_ckarray4_to_array(arg_size, arg_size_arr);
    Chuck_Array4 *arg_type_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLenum *arg_type = new GLenum[arg_type_arr->size()];
    chgl->scheduleDataForCleanup(arg_type);
    copy_ckarray4_to_array(arg_type, arg_type_arr);
    Chuck_Array4 *arg_name_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLchar *arg_name = new GLchar[arg_name_arr->size()];
    chgl->scheduleDataForCleanup(arg_name);
    copy_ckarray4_to_array(arg_name, arg_name_arr);

    glGetActiveUniform(arg_program, arg_index, arg_bufSize, arg_length, arg_size, arg_type, arg_name);
}


CK_DLL_MFUN(Chuck_OpenGL_GetAttachedShaders)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);
    t_CKINT arg_maxCount = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_count_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLsizei *arg_count = new GLsizei[arg_count_arr->size()];
    chgl->scheduleDataForCleanup(arg_count);
    copy_ckarray4_to_array(arg_count, arg_count_arr);
    Chuck_Array4 *arg_shaders_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_shaders = new GLuint[arg_shaders_arr->size()];
    chgl->scheduleDataForCleanup(arg_shaders);
    copy_ckarray4_to_array(arg_shaders, arg_shaders_arr);

    glGetAttachedShaders(arg_program, arg_maxCount, arg_count, arg_shaders);
}


CK_DLL_MFUN(Chuck_OpenGL_GetAttribLocation)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_name_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLchar *arg_name = new GLchar[arg_name_arr->size()];
    chgl->scheduleDataForCleanup(arg_name);
    copy_ckarray4_to_array(arg_name, arg_name_arr);

    RETURN->v_int = glGetAttribLocation(arg_program, arg_name);
}


CK_DLL_MFUN(Chuck_OpenGL_GetBooleanv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_data_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLboolean *arg_data = new GLboolean[arg_data_arr->size()];
    chgl->scheduleDataForCleanup(arg_data);
    copy_ckarray4_to_array(arg_data, arg_data_arr);

    glGetBooleanv(arg_pname, arg_data);
}


CK_DLL_MFUN(Chuck_OpenGL_GetBufferParameteriv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleDataForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glGetBufferParameteriv(arg_target, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetError)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    

    RETURN->v_int = glGetError();
}


CK_DLL_MFUN(Chuck_OpenGL_GetFloatv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_data_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_data = new GLfloat[arg_data_arr->size()];
    chgl->scheduleDataForCleanup(arg_data);
    copy_ckarray8_to_array(arg_data, arg_data_arr);

    glGetFloatv(arg_pname, arg_data);
}


CK_DLL_MFUN(Chuck_OpenGL_GetFramebufferAttachmentParameteriv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_attachment = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleDataForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glGetFramebufferAttachmentParameteriv(arg_target, arg_attachment, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetIntegerv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_data_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_data = new GLint[arg_data_arr->size()];
    chgl->scheduleDataForCleanup(arg_data);
    copy_ckarray4_to_array(arg_data, arg_data_arr);

    glGetIntegerv(arg_pname, arg_data);
}


CK_DLL_MFUN(Chuck_OpenGL_GetProgramiv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleDataForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glGetProgramiv(arg_program, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetProgramInfoLog)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);
    t_CKINT arg_bufSize = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_length_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLsizei *arg_length = new GLsizei[arg_length_arr->size()];
    chgl->scheduleDataForCleanup(arg_length);
    copy_ckarray4_to_array(arg_length, arg_length_arr);
    Chuck_Array4 *arg_infoLog_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLchar *arg_infoLog = new GLchar[arg_infoLog_arr->size()];
    chgl->scheduleDataForCleanup(arg_infoLog);
    copy_ckarray4_to_array(arg_infoLog, arg_infoLog_arr);

    glGetProgramInfoLog(arg_program, arg_bufSize, arg_length, arg_infoLog);
}


CK_DLL_MFUN(Chuck_OpenGL_GetRenderbufferParameteriv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleDataForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glGetRenderbufferParameteriv(arg_target, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetShaderiv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_shader = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleDataForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glGetShaderiv(arg_shader, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetShaderInfoLog)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_shader = GET_NEXT_INT(ARGS);
    t_CKINT arg_bufSize = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_length_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLsizei *arg_length = new GLsizei[arg_length_arr->size()];
    chgl->scheduleDataForCleanup(arg_length);
    copy_ckarray4_to_array(arg_length, arg_length_arr);
    Chuck_Array4 *arg_infoLog_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLchar *arg_infoLog = new GLchar[arg_infoLog_arr->size()];
    chgl->scheduleDataForCleanup(arg_infoLog);
    copy_ckarray4_to_array(arg_infoLog, arg_infoLog_arr);

    glGetShaderInfoLog(arg_shader, arg_bufSize, arg_length, arg_infoLog);
}


CK_DLL_MFUN(Chuck_OpenGL_GetShaderPrecisionFormat)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_shadertype = GET_NEXT_INT(ARGS);
    t_CKINT arg_precisiontype = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_range_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_range = new GLint[arg_range_arr->size()];
    chgl->scheduleDataForCleanup(arg_range);
    copy_ckarray4_to_array(arg_range, arg_range_arr);
    Chuck_Array4 *arg_precision_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_precision = new GLint[arg_precision_arr->size()];
    chgl->scheduleDataForCleanup(arg_precision);
    copy_ckarray4_to_array(arg_precision, arg_precision_arr);

    glGetShaderPrecisionFormat(arg_shadertype, arg_precisiontype, arg_range, arg_precision);
}


CK_DLL_MFUN(Chuck_OpenGL_GetShaderSource)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_shader = GET_NEXT_INT(ARGS);
    t_CKINT arg_bufSize = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_length_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLsizei *arg_length = new GLsizei[arg_length_arr->size()];
    chgl->scheduleDataForCleanup(arg_length);
    copy_ckarray4_to_array(arg_length, arg_length_arr);
    Chuck_Array4 *arg_source_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLchar *arg_source = new GLchar[arg_source_arr->size()];
    chgl->scheduleDataForCleanup(arg_source);
    copy_ckarray4_to_array(arg_source, arg_source_arr);

    glGetShaderSource(arg_shader, arg_bufSize, arg_length, arg_source);
}


CK_DLL_MFUN(Chuck_OpenGL_GetTexParameterfv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_params_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_params = new GLfloat[arg_params_arr->size()];
    chgl->scheduleDataForCleanup(arg_params);
    copy_ckarray8_to_array(arg_params, arg_params_arr);

    glGetTexParameterfv(arg_target, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetTexParameteriv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleDataForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glGetTexParameteriv(arg_target, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetUniformfv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_params_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_params = new GLfloat[arg_params_arr->size()];
    chgl->scheduleDataForCleanup(arg_params);
    copy_ckarray8_to_array(arg_params, arg_params_arr);

    glGetUniformfv(arg_program, arg_location, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetUniformiv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleDataForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glGetUniformiv(arg_program, arg_location, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetUniformLocation)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_name_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLchar *arg_name = new GLchar[arg_name_arr->size()];
    chgl->scheduleDataForCleanup(arg_name);
    copy_ckarray4_to_array(arg_name, arg_name_arr);

    RETURN->v_int = glGetUniformLocation(arg_program, arg_name);
}


CK_DLL_MFUN(Chuck_OpenGL_GetVertexAttribfv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_params_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_params = new GLfloat[arg_params_arr->size()];
    chgl->scheduleDataForCleanup(arg_params);
    copy_ckarray8_to_array(arg_params, arg_params_arr);

    glGetVertexAttribfv(arg_index, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetVertexAttribiv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleDataForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glGetVertexAttribiv(arg_index, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_Hint)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_mode = GET_NEXT_INT(ARGS);

    glHint(arg_target, arg_mode);
}


CK_DLL_MFUN(Chuck_OpenGL_IsBuffer)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_buffer = GET_NEXT_INT(ARGS);

    RETURN->v_int = glIsBuffer(arg_buffer);
}


CK_DLL_MFUN(Chuck_OpenGL_IsEnabled)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_cap = GET_NEXT_INT(ARGS);

    RETURN->v_int = glIsEnabled(arg_cap);
}


CK_DLL_MFUN(Chuck_OpenGL_IsFramebuffer)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_framebuffer = GET_NEXT_INT(ARGS);

    RETURN->v_int = glIsFramebuffer(arg_framebuffer);
}


CK_DLL_MFUN(Chuck_OpenGL_IsProgram)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);

    RETURN->v_int = glIsProgram(arg_program);
}


CK_DLL_MFUN(Chuck_OpenGL_IsRenderbuffer)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_renderbuffer = GET_NEXT_INT(ARGS);

    RETURN->v_int = glIsRenderbuffer(arg_renderbuffer);
}


CK_DLL_MFUN(Chuck_OpenGL_IsShader)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_shader = GET_NEXT_INT(ARGS);

    RETURN->v_int = glIsShader(arg_shader);
}


CK_DLL_MFUN(Chuck_OpenGL_IsTexture)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_texture = GET_NEXT_INT(ARGS);

    RETURN->v_int = glIsTexture(arg_texture);
}


CK_DLL_MFUN(Chuck_OpenGL_LineWidth)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKFLOAT arg_width = GET_NEXT_FLOAT(ARGS);

    glLineWidth(arg_width);
}


CK_DLL_MFUN(Chuck_OpenGL_LinkProgram)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);

    glLinkProgram(arg_program);
}


CK_DLL_MFUN(Chuck_OpenGL_PixelStorei)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    t_CKINT arg_param = GET_NEXT_INT(ARGS);

    glPixelStorei(arg_pname, arg_param);
}


CK_DLL_MFUN(Chuck_OpenGL_PolygonOffset)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKFLOAT arg_factor = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_units = GET_NEXT_FLOAT(ARGS);

    glPolygonOffset(arg_factor, arg_units);
}


CK_DLL_MFUN(Chuck_OpenGL_ReadPixels)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_height = GET_NEXT_INT(ARGS);
    t_CKINT arg_format = GET_NEXT_INT(ARGS);
    t_CKINT arg_type = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_pixels_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_pixels;
    if(_arg_pixels_arr->data_type_kind() == CHUCK_ARRAY4_DATAKIND)
    {
        Chuck_Array4 *arg_pixels_arr = (Chuck_Array4 *) _arg_pixels_arr;
        GLubyte *arg_pixels_v = new GLubyte[arg_pixels_arr->size()];
        chgl->scheduleDataForCleanup(arg_pixels_v);
        copy_ckarray4_to_array(arg_pixels_v, arg_pixels_arr);
        arg_pixels = (void *) arg_pixels_v;
    }
    else if(_arg_pixels_arr->data_type_kind() == CHUCK_ARRAY8_DATAKIND)
    {
        Chuck_Array4 *arg_pixels_arr = (Chuck_Array4 *) _arg_pixels_arr;
        arg_pixels_arr->add_ref();
        chgl->scheduleArrayForCleanup(arg_pixels_arr);
        arg_pixels = (void *) &(arg_pixels_arr->m_vector.front());
    }
    else
    {
        assert(0);
    }

    glReadPixels(arg_x, arg_y, arg_width, arg_height, arg_format, arg_type, arg_pixels);
}


CK_DLL_MFUN(Chuck_OpenGL_ReleaseShaderCompiler)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    

    glReleaseShaderCompiler();
}


CK_DLL_MFUN(Chuck_OpenGL_RenderbufferStorage)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_internalformat = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_height = GET_NEXT_INT(ARGS);

    glRenderbufferStorage(arg_target, arg_internalformat, arg_width, arg_height);
}


CK_DLL_MFUN(Chuck_OpenGL_SampleCoverage)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKFLOAT arg_value = GET_NEXT_FLOAT(ARGS);
    t_CKINT arg_invert = GET_NEXT_INT(ARGS);

    glSampleCoverage(arg_value, arg_invert);
}


CK_DLL_MFUN(Chuck_OpenGL_Scissor)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_height = GET_NEXT_INT(ARGS);

    glScissor(arg_x, arg_y, arg_width, arg_height);
}


CK_DLL_MFUN(Chuck_OpenGL_ShaderBinary)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_shaders_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_shaders = new GLuint[arg_shaders_arr->size()];
    chgl->scheduleDataForCleanup(arg_shaders);
    copy_ckarray4_to_array(arg_shaders, arg_shaders_arr);
    t_CKINT arg_binaryformat = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_binary_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_binary;
    if(_arg_binary_arr->data_type_kind() == CHUCK_ARRAY4_DATAKIND)
    {
        Chuck_Array4 *arg_binary_arr = (Chuck_Array4 *) _arg_binary_arr;
        GLubyte *arg_binary_v = new GLubyte[arg_binary_arr->size()];
        chgl->scheduleDataForCleanup(arg_binary_v);
        copy_ckarray4_to_array(arg_binary_v, arg_binary_arr);
        arg_binary = (void *) arg_binary_v;
    }
    else if(_arg_binary_arr->data_type_kind() == CHUCK_ARRAY8_DATAKIND)
    {
        Chuck_Array4 *arg_binary_arr = (Chuck_Array4 *) _arg_binary_arr;
        arg_binary_arr->add_ref();
        chgl->scheduleArrayForCleanup(arg_binary_arr);
        arg_binary = (void *) &(arg_binary_arr->m_vector.front());
    }
    else
    {
        assert(0);
    }
    t_CKINT arg_length = GET_NEXT_INT(ARGS);

    glShaderBinary(arg_count, arg_shaders, arg_binaryformat, arg_binary, arg_length);
}


CK_DLL_MFUN(Chuck_OpenGL_StencilFunc)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_func = GET_NEXT_INT(ARGS);
    t_CKINT arg_ref = GET_NEXT_INT(ARGS);
    t_CKINT arg_mask = GET_NEXT_INT(ARGS);

    glStencilFunc(arg_func, arg_ref, arg_mask);
}


CK_DLL_MFUN(Chuck_OpenGL_StencilFuncSeparate)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_face = GET_NEXT_INT(ARGS);
    t_CKINT arg_func = GET_NEXT_INT(ARGS);
    t_CKINT arg_ref = GET_NEXT_INT(ARGS);
    t_CKINT arg_mask = GET_NEXT_INT(ARGS);

    glStencilFuncSeparate(arg_face, arg_func, arg_ref, arg_mask);
}


CK_DLL_MFUN(Chuck_OpenGL_StencilMask)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_mask = GET_NEXT_INT(ARGS);

    glStencilMask(arg_mask);
}


CK_DLL_MFUN(Chuck_OpenGL_StencilMaskSeparate)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_face = GET_NEXT_INT(ARGS);
    t_CKINT arg_mask = GET_NEXT_INT(ARGS);

    glStencilMaskSeparate(arg_face, arg_mask);
}


CK_DLL_MFUN(Chuck_OpenGL_StencilOp)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_fail = GET_NEXT_INT(ARGS);
    t_CKINT arg_zfail = GET_NEXT_INT(ARGS);
    t_CKINT arg_zpass = GET_NEXT_INT(ARGS);

    glStencilOp(arg_fail, arg_zfail, arg_zpass);
}


CK_DLL_MFUN(Chuck_OpenGL_StencilOpSeparate)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_face = GET_NEXT_INT(ARGS);
    t_CKINT arg_sfail = GET_NEXT_INT(ARGS);
    t_CKINT arg_dpfail = GET_NEXT_INT(ARGS);
    t_CKINT arg_dppass = GET_NEXT_INT(ARGS);

    glStencilOpSeparate(arg_face, arg_sfail, arg_dpfail, arg_dppass);
}


CK_DLL_MFUN(Chuck_OpenGL_TexImage2D)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);
    t_CKINT arg_internalformat = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_height = GET_NEXT_INT(ARGS);
    t_CKINT arg_border = GET_NEXT_INT(ARGS);
    t_CKINT arg_format = GET_NEXT_INT(ARGS);
    t_CKINT arg_type = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_pixels_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_pixels;
    if(_arg_pixels_arr->data_type_kind() == CHUCK_ARRAY4_DATAKIND)
    {
        Chuck_Array4 *arg_pixels_arr = (Chuck_Array4 *) _arg_pixels_arr;
        GLubyte *arg_pixels_v = new GLubyte[arg_pixels_arr->size()];
        chgl->scheduleDataForCleanup(arg_pixels_v);
        copy_ckarray4_to_array(arg_pixels_v, arg_pixels_arr);
        arg_pixels = (void *) arg_pixels_v;
    }
    else if(_arg_pixels_arr->data_type_kind() == CHUCK_ARRAY8_DATAKIND)
    {
        Chuck_Array4 *arg_pixels_arr = (Chuck_Array4 *) _arg_pixels_arr;
        arg_pixels_arr->add_ref();
        chgl->scheduleArrayForCleanup(arg_pixels_arr);
        arg_pixels = (void *) &(arg_pixels_arr->m_vector.front());
    }
    else
    {
        assert(0);
    }

    glTexImage2D(arg_target, arg_level, arg_internalformat, arg_width, arg_height, arg_border, arg_format, arg_type, arg_pixels);
}


CK_DLL_MFUN(Chuck_OpenGL_TexParameterf)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_param = GET_NEXT_FLOAT(ARGS);

    glTexParameterf(arg_target, arg_pname, arg_param);
}


CK_DLL_MFUN(Chuck_OpenGL_TexParameterfv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_params_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_params = new GLfloat[arg_params_arr->size()];
    chgl->scheduleDataForCleanup(arg_params);
    copy_ckarray8_to_array(arg_params, arg_params_arr);

    glTexParameterfv(arg_target, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_TexParameteri)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    t_CKINT arg_param = GET_NEXT_INT(ARGS);

    glTexParameteri(arg_target, arg_pname, arg_param);
}


CK_DLL_MFUN(Chuck_OpenGL_TexParameteriv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleDataForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glTexParameteriv(arg_target, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_TexSubImage2D)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);
    t_CKINT arg_xoffset = GET_NEXT_INT(ARGS);
    t_CKINT arg_yoffset = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_height = GET_NEXT_INT(ARGS);
    t_CKINT arg_format = GET_NEXT_INT(ARGS);
    t_CKINT arg_type = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_pixels_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_pixels;
    if(_arg_pixels_arr->data_type_kind() == CHUCK_ARRAY4_DATAKIND)
    {
        Chuck_Array4 *arg_pixels_arr = (Chuck_Array4 *) _arg_pixels_arr;
        GLubyte *arg_pixels_v = new GLubyte[arg_pixels_arr->size()];
        chgl->scheduleDataForCleanup(arg_pixels_v);
        copy_ckarray4_to_array(arg_pixels_v, arg_pixels_arr);
        arg_pixels = (void *) arg_pixels_v;
    }
    else if(_arg_pixels_arr->data_type_kind() == CHUCK_ARRAY8_DATAKIND)
    {
        Chuck_Array4 *arg_pixels_arr = (Chuck_Array4 *) _arg_pixels_arr;
        arg_pixels_arr->add_ref();
        chgl->scheduleArrayForCleanup(arg_pixels_arr);
        arg_pixels = (void *) &(arg_pixels_arr->m_vector.front());
    }
    else
    {
        assert(0);
    }

    glTexSubImage2D(arg_target, arg_level, arg_xoffset, arg_yoffset, arg_width, arg_height, arg_format, arg_type, arg_pixels);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform1f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_v0 = GET_NEXT_FLOAT(ARGS);

    glUniform1f(arg_location, arg_v0);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform1fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_value_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_value = new GLfloat[arg_value_arr->size()];
    chgl->scheduleDataForCleanup(arg_value);
    copy_ckarray8_to_array(arg_value, arg_value_arr);

    glUniform1fv(arg_location, arg_count, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform1i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_v0 = GET_NEXT_INT(ARGS);

    glUniform1i(arg_location, arg_v0);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform1iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_value_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_value = new GLint[arg_value_arr->size()];
    chgl->scheduleDataForCleanup(arg_value);
    copy_ckarray4_to_array(arg_value, arg_value_arr);

    glUniform1iv(arg_location, arg_count, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform2f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_v0 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_v1 = GET_NEXT_FLOAT(ARGS);

    glUniform2f(arg_location, arg_v0, arg_v1);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform2fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_value_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_value = new GLfloat[arg_value_arr->size()];
    chgl->scheduleDataForCleanup(arg_value);
    copy_ckarray8_to_array(arg_value, arg_value_arr);

    glUniform2fv(arg_location, arg_count, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform2i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_v0 = GET_NEXT_INT(ARGS);
    t_CKINT arg_v1 = GET_NEXT_INT(ARGS);

    glUniform2i(arg_location, arg_v0, arg_v1);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform2iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_value_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_value = new GLint[arg_value_arr->size()];
    chgl->scheduleDataForCleanup(arg_value);
    copy_ckarray4_to_array(arg_value, arg_value_arr);

    glUniform2iv(arg_location, arg_count, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform3f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_v0 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_v1 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_v2 = GET_NEXT_FLOAT(ARGS);

    glUniform3f(arg_location, arg_v0, arg_v1, arg_v2);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform3fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_value_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_value = new GLfloat[arg_value_arr->size()];
    chgl->scheduleDataForCleanup(arg_value);
    copy_ckarray8_to_array(arg_value, arg_value_arr);

    glUniform3fv(arg_location, arg_count, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform3i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_v0 = GET_NEXT_INT(ARGS);
    t_CKINT arg_v1 = GET_NEXT_INT(ARGS);
    t_CKINT arg_v2 = GET_NEXT_INT(ARGS);

    glUniform3i(arg_location, arg_v0, arg_v1, arg_v2);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform3iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_value_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_value = new GLint[arg_value_arr->size()];
    chgl->scheduleDataForCleanup(arg_value);
    copy_ckarray4_to_array(arg_value, arg_value_arr);

    glUniform3iv(arg_location, arg_count, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform4f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_v0 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_v1 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_v2 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_v3 = GET_NEXT_FLOAT(ARGS);

    glUniform4f(arg_location, arg_v0, arg_v1, arg_v2, arg_v3);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform4fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_value_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_value = new GLfloat[arg_value_arr->size()];
    chgl->scheduleDataForCleanup(arg_value);
    copy_ckarray8_to_array(arg_value, arg_value_arr);

    glUniform4fv(arg_location, arg_count, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform4i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_v0 = GET_NEXT_INT(ARGS);
    t_CKINT arg_v1 = GET_NEXT_INT(ARGS);
    t_CKINT arg_v2 = GET_NEXT_INT(ARGS);
    t_CKINT arg_v3 = GET_NEXT_INT(ARGS);

    glUniform4i(arg_location, arg_v0, arg_v1, arg_v2, arg_v3);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform4iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_value_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_value = new GLint[arg_value_arr->size()];
    chgl->scheduleDataForCleanup(arg_value);
    copy_ckarray4_to_array(arg_value, arg_value_arr);

    glUniform4iv(arg_location, arg_count, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_UniformMatrix2fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    t_CKINT arg_transpose = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_value_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_value = new GLfloat[arg_value_arr->size()];
    chgl->scheduleDataForCleanup(arg_value);
    copy_ckarray8_to_array(arg_value, arg_value_arr);

    glUniformMatrix2fv(arg_location, arg_count, arg_transpose, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_UniformMatrix3fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    t_CKINT arg_transpose = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_value_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_value = new GLfloat[arg_value_arr->size()];
    chgl->scheduleDataForCleanup(arg_value);
    copy_ckarray8_to_array(arg_value, arg_value_arr);

    glUniformMatrix3fv(arg_location, arg_count, arg_transpose, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_UniformMatrix4fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    t_CKINT arg_transpose = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_value_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_value = new GLfloat[arg_value_arr->size()];
    chgl->scheduleDataForCleanup(arg_value);
    copy_ckarray8_to_array(arg_value, arg_value_arr);

    glUniformMatrix4fv(arg_location, arg_count, arg_transpose, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_UseProgram)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);

    glUseProgram(arg_program);
}


CK_DLL_MFUN(Chuck_OpenGL_ValidateProgram)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);

    glValidateProgram(arg_program);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib1f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);

    glVertexAttrib1f(arg_index, arg_x);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib1fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleDataForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glVertexAttrib1fv(arg_index, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib2f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);

    glVertexAttrib2f(arg_index, arg_x, arg_y);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib2fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleDataForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glVertexAttrib2fv(arg_index, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib3f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_z = GET_NEXT_FLOAT(ARGS);

    glVertexAttrib3f(arg_index, arg_x, arg_y, arg_z);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib3fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleDataForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glVertexAttrib3fv(arg_index, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib4f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_z = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_w = GET_NEXT_FLOAT(ARGS);

    glVertexAttrib4f(arg_index, arg_x, arg_y, arg_z, arg_w);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib4fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleDataForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glVertexAttrib4fv(arg_index, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttribPointer)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKINT arg_size = GET_NEXT_INT(ARGS);
    t_CKINT arg_type = GET_NEXT_INT(ARGS);
    t_CKINT arg_normalized = GET_NEXT_INT(ARGS);
    t_CKINT arg_stride = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_pointer_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_pointer;
    if(_arg_pointer_arr->data_type_kind() == CHUCK_ARRAY4_DATAKIND)
    {
        Chuck_Array4 *arg_pointer_arr = (Chuck_Array4 *) _arg_pointer_arr;
        GLubyte *arg_pointer_v = new GLubyte[arg_pointer_arr->size()];
        chgl->scheduleDataForCleanup(arg_pointer_v);
        copy_ckarray4_to_array(arg_pointer_v, arg_pointer_arr);
        arg_pointer = (void *) arg_pointer_v;
    }
    else if(_arg_pointer_arr->data_type_kind() == CHUCK_ARRAY8_DATAKIND)
    {
        Chuck_Array4 *arg_pointer_arr = (Chuck_Array4 *) _arg_pointer_arr;
        arg_pointer_arr->add_ref();
        chgl->scheduleArrayForCleanup(arg_pointer_arr);
        arg_pointer = (void *) &(arg_pointer_arr->m_vector.front());
    }
    else
    {
        assert(0);
    }

    glVertexAttribPointer(arg_index, arg_size, arg_type, arg_normalized, arg_stride, arg_pointer);
}


CK_DLL_MFUN(Chuck_OpenGL_Viewport)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_height = GET_NEXT_INT(ARGS);

    glViewport(arg_x, arg_y, arg_width, arg_height);
}



t_CKBOOL OpenGL_query(Chuck_DL_Query *QUERY)
{
    // hmm, don't change this...
    QUERY->setname(QUERY, "OpenGL");
    
    // begin the class definition
    // can change the second argument to extend a different ChucK class
    QUERY->begin_class(QUERY, "OpenGL", "Object");
    
    Chuck_OpenGL_offset_chugl = QUERY->add_mvar(QUERY, "int", "@chugl_data", FALSE);
    
    QUERY->add_ctor(QUERY, Chuck_OpenGL_ctor);
    
    QUERY->add_svar( QUERY, "int", "DEPTH_BUFFER_BIT", TRUE, (void *)&Chuck_OpenGL_DEPTH_BUFFER_BIT );
    QUERY->add_svar( QUERY, "int", "STENCIL_BUFFER_BIT", TRUE, (void *)&Chuck_OpenGL_STENCIL_BUFFER_BIT );
    QUERY->add_svar( QUERY, "int", "COLOR_BUFFER_BIT", TRUE, (void *)&Chuck_OpenGL_COLOR_BUFFER_BIT );
    QUERY->add_svar( QUERY, "int", "FALSE", TRUE, (void *)&Chuck_OpenGL_FALSE );
    QUERY->add_svar( QUERY, "int", "TRUE", TRUE, (void *)&Chuck_OpenGL_TRUE );
    QUERY->add_svar( QUERY, "int", "POINTS", TRUE, (void *)&Chuck_OpenGL_POINTS );
    QUERY->add_svar( QUERY, "int", "LINES", TRUE, (void *)&Chuck_OpenGL_LINES );
    QUERY->add_svar( QUERY, "int", "LINE_LOOP", TRUE, (void *)&Chuck_OpenGL_LINE_LOOP );
    QUERY->add_svar( QUERY, "int", "LINE_STRIP", TRUE, (void *)&Chuck_OpenGL_LINE_STRIP );
    QUERY->add_svar( QUERY, "int", "TRIANGLES", TRUE, (void *)&Chuck_OpenGL_TRIANGLES );
    QUERY->add_svar( QUERY, "int", "TRIANGLE_STRIP", TRUE, (void *)&Chuck_OpenGL_TRIANGLE_STRIP );
    QUERY->add_svar( QUERY, "int", "TRIANGLE_FAN", TRUE, (void *)&Chuck_OpenGL_TRIANGLE_FAN );
    QUERY->add_svar( QUERY, "int", "ZERO", TRUE, (void *)&Chuck_OpenGL_ZERO );
    QUERY->add_svar( QUERY, "int", "ONE", TRUE, (void *)&Chuck_OpenGL_ONE );
    QUERY->add_svar( QUERY, "int", "SRC_COLOR", TRUE, (void *)&Chuck_OpenGL_SRC_COLOR );
    QUERY->add_svar( QUERY, "int", "ONE_MINUS_SRC_COLOR", TRUE, (void *)&Chuck_OpenGL_ONE_MINUS_SRC_COLOR );
    QUERY->add_svar( QUERY, "int", "SRC_ALPHA", TRUE, (void *)&Chuck_OpenGL_SRC_ALPHA );
    QUERY->add_svar( QUERY, "int", "ONE_MINUS_SRC_ALPHA", TRUE, (void *)&Chuck_OpenGL_ONE_MINUS_SRC_ALPHA );
    QUERY->add_svar( QUERY, "int", "DST_ALPHA", TRUE, (void *)&Chuck_OpenGL_DST_ALPHA );
    QUERY->add_svar( QUERY, "int", "ONE_MINUS_DST_ALPHA", TRUE, (void *)&Chuck_OpenGL_ONE_MINUS_DST_ALPHA );
    QUERY->add_svar( QUERY, "int", "DST_COLOR", TRUE, (void *)&Chuck_OpenGL_DST_COLOR );
    QUERY->add_svar( QUERY, "int", "ONE_MINUS_DST_COLOR", TRUE, (void *)&Chuck_OpenGL_ONE_MINUS_DST_COLOR );
    QUERY->add_svar( QUERY, "int", "SRC_ALPHA_SATURATE", TRUE, (void *)&Chuck_OpenGL_SRC_ALPHA_SATURATE );
    QUERY->add_svar( QUERY, "int", "FUNC_ADD", TRUE, (void *)&Chuck_OpenGL_FUNC_ADD );
    QUERY->add_svar( QUERY, "int", "BLEND_EQUATION", TRUE, (void *)&Chuck_OpenGL_BLEND_EQUATION );
    QUERY->add_svar( QUERY, "int", "BLEND_EQUATION_RGB", TRUE, (void *)&Chuck_OpenGL_BLEND_EQUATION_RGB );
    QUERY->add_svar( QUERY, "int", "BLEND_EQUATION_ALPHA", TRUE, (void *)&Chuck_OpenGL_BLEND_EQUATION_ALPHA );
    QUERY->add_svar( QUERY, "int", "FUNC_SUBTRACT", TRUE, (void *)&Chuck_OpenGL_FUNC_SUBTRACT );
    QUERY->add_svar( QUERY, "int", "FUNC_REVERSE_SUBTRACT", TRUE, (void *)&Chuck_OpenGL_FUNC_REVERSE_SUBTRACT );
    QUERY->add_svar( QUERY, "int", "BLEND_DST_RGB", TRUE, (void *)&Chuck_OpenGL_BLEND_DST_RGB );
    QUERY->add_svar( QUERY, "int", "BLEND_SRC_RGB", TRUE, (void *)&Chuck_OpenGL_BLEND_SRC_RGB );
    QUERY->add_svar( QUERY, "int", "BLEND_DST_ALPHA", TRUE, (void *)&Chuck_OpenGL_BLEND_DST_ALPHA );
    QUERY->add_svar( QUERY, "int", "BLEND_SRC_ALPHA", TRUE, (void *)&Chuck_OpenGL_BLEND_SRC_ALPHA );
    QUERY->add_svar( QUERY, "int", "CONSTANT_COLOR", TRUE, (void *)&Chuck_OpenGL_CONSTANT_COLOR );
    QUERY->add_svar( QUERY, "int", "ONE_MINUS_CONSTANT_COLOR", TRUE, (void *)&Chuck_OpenGL_ONE_MINUS_CONSTANT_COLOR );
    QUERY->add_svar( QUERY, "int", "CONSTANT_ALPHA", TRUE, (void *)&Chuck_OpenGL_CONSTANT_ALPHA );
    QUERY->add_svar( QUERY, "int", "ONE_MINUS_CONSTANT_ALPHA", TRUE, (void *)&Chuck_OpenGL_ONE_MINUS_CONSTANT_ALPHA );
    QUERY->add_svar( QUERY, "int", "BLEND_COLOR", TRUE, (void *)&Chuck_OpenGL_BLEND_COLOR );
    QUERY->add_svar( QUERY, "int", "ARRAY_BUFFER", TRUE, (void *)&Chuck_OpenGL_ARRAY_BUFFER );
    QUERY->add_svar( QUERY, "int", "ELEMENT_ARRAY_BUFFER", TRUE, (void *)&Chuck_OpenGL_ELEMENT_ARRAY_BUFFER );
    QUERY->add_svar( QUERY, "int", "ARRAY_BUFFER_BINDING", TRUE, (void *)&Chuck_OpenGL_ARRAY_BUFFER_BINDING );
    QUERY->add_svar( QUERY, "int", "ELEMENT_ARRAY_BUFFER_BINDING", TRUE, (void *)&Chuck_OpenGL_ELEMENT_ARRAY_BUFFER_BINDING );
    QUERY->add_svar( QUERY, "int", "STREAM_DRAW", TRUE, (void *)&Chuck_OpenGL_STREAM_DRAW );
    QUERY->add_svar( QUERY, "int", "STATIC_DRAW", TRUE, (void *)&Chuck_OpenGL_STATIC_DRAW );
    QUERY->add_svar( QUERY, "int", "DYNAMIC_DRAW", TRUE, (void *)&Chuck_OpenGL_DYNAMIC_DRAW );
    QUERY->add_svar( QUERY, "int", "BUFFER_SIZE", TRUE, (void *)&Chuck_OpenGL_BUFFER_SIZE );
    QUERY->add_svar( QUERY, "int", "BUFFER_USAGE", TRUE, (void *)&Chuck_OpenGL_BUFFER_USAGE );
    QUERY->add_svar( QUERY, "int", "CURRENT_VERTEX_ATTRIB", TRUE, (void *)&Chuck_OpenGL_CURRENT_VERTEX_ATTRIB );
    QUERY->add_svar( QUERY, "int", "FRONT", TRUE, (void *)&Chuck_OpenGL_FRONT );
    QUERY->add_svar( QUERY, "int", "BACK", TRUE, (void *)&Chuck_OpenGL_BACK );
    QUERY->add_svar( QUERY, "int", "FRONT_AND_BACK", TRUE, (void *)&Chuck_OpenGL_FRONT_AND_BACK );
    QUERY->add_svar( QUERY, "int", "TEXTURE_2D", TRUE, (void *)&Chuck_OpenGL_TEXTURE_2D );
    QUERY->add_svar( QUERY, "int", "CULL_FACE", TRUE, (void *)&Chuck_OpenGL_CULL_FACE );
    QUERY->add_svar( QUERY, "int", "BLEND", TRUE, (void *)&Chuck_OpenGL_BLEND );
    QUERY->add_svar( QUERY, "int", "DITHER", TRUE, (void *)&Chuck_OpenGL_DITHER );
    QUERY->add_svar( QUERY, "int", "STENCIL_TEST", TRUE, (void *)&Chuck_OpenGL_STENCIL_TEST );
    QUERY->add_svar( QUERY, "int", "DEPTH_TEST", TRUE, (void *)&Chuck_OpenGL_DEPTH_TEST );
    QUERY->add_svar( QUERY, "int", "SCISSOR_TEST", TRUE, (void *)&Chuck_OpenGL_SCISSOR_TEST );
    QUERY->add_svar( QUERY, "int", "POLYGON_OFFSET_FILL", TRUE, (void *)&Chuck_OpenGL_POLYGON_OFFSET_FILL );
    QUERY->add_svar( QUERY, "int", "SAMPLE_ALPHA_TO_COVERAGE", TRUE, (void *)&Chuck_OpenGL_SAMPLE_ALPHA_TO_COVERAGE );
    QUERY->add_svar( QUERY, "int", "SAMPLE_COVERAGE", TRUE, (void *)&Chuck_OpenGL_SAMPLE_COVERAGE );
    QUERY->add_svar( QUERY, "int", "NO_ERROR", TRUE, (void *)&Chuck_OpenGL_NO_ERROR );
    QUERY->add_svar( QUERY, "int", "INVALID_ENUM", TRUE, (void *)&Chuck_OpenGL_INVALID_ENUM );
    QUERY->add_svar( QUERY, "int", "INVALID_VALUE", TRUE, (void *)&Chuck_OpenGL_INVALID_VALUE );
    QUERY->add_svar( QUERY, "int", "INVALID_OPERATION", TRUE, (void *)&Chuck_OpenGL_INVALID_OPERATION );
    QUERY->add_svar( QUERY, "int", "OUT_OF_MEMORY", TRUE, (void *)&Chuck_OpenGL_OUT_OF_MEMORY );
    QUERY->add_svar( QUERY, "int", "CW", TRUE, (void *)&Chuck_OpenGL_CW );
    QUERY->add_svar( QUERY, "int", "CCW", TRUE, (void *)&Chuck_OpenGL_CCW );
    QUERY->add_svar( QUERY, "int", "LINE_WIDTH", TRUE, (void *)&Chuck_OpenGL_LINE_WIDTH );
    QUERY->add_svar( QUERY, "int", "ALIASED_POINT_SIZE_RANGE", TRUE, (void *)&Chuck_OpenGL_ALIASED_POINT_SIZE_RANGE );
    QUERY->add_svar( QUERY, "int", "ALIASED_LINE_WIDTH_RANGE", TRUE, (void *)&Chuck_OpenGL_ALIASED_LINE_WIDTH_RANGE );
    QUERY->add_svar( QUERY, "int", "CULL_FACE_MODE", TRUE, (void *)&Chuck_OpenGL_CULL_FACE_MODE );
    QUERY->add_svar( QUERY, "int", "FRONT_FACE", TRUE, (void *)&Chuck_OpenGL_FRONT_FACE );
    QUERY->add_svar( QUERY, "int", "DEPTH_RANGE", TRUE, (void *)&Chuck_OpenGL_DEPTH_RANGE );
    QUERY->add_svar( QUERY, "int", "DEPTH_WRITEMASK", TRUE, (void *)&Chuck_OpenGL_DEPTH_WRITEMASK );
    QUERY->add_svar( QUERY, "int", "DEPTH_CLEAR_VALUE", TRUE, (void *)&Chuck_OpenGL_DEPTH_CLEAR_VALUE );
    QUERY->add_svar( QUERY, "int", "DEPTH_FUNC", TRUE, (void *)&Chuck_OpenGL_DEPTH_FUNC );
    QUERY->add_svar( QUERY, "int", "STENCIL_CLEAR_VALUE", TRUE, (void *)&Chuck_OpenGL_STENCIL_CLEAR_VALUE );
    QUERY->add_svar( QUERY, "int", "STENCIL_FUNC", TRUE, (void *)&Chuck_OpenGL_STENCIL_FUNC );
    QUERY->add_svar( QUERY, "int", "STENCIL_FAIL", TRUE, (void *)&Chuck_OpenGL_STENCIL_FAIL );
    QUERY->add_svar( QUERY, "int", "STENCIL_PASS_DEPTH_FAIL", TRUE, (void *)&Chuck_OpenGL_STENCIL_PASS_DEPTH_FAIL );
    QUERY->add_svar( QUERY, "int", "STENCIL_PASS_DEPTH_PASS", TRUE, (void *)&Chuck_OpenGL_STENCIL_PASS_DEPTH_PASS );
    QUERY->add_svar( QUERY, "int", "STENCIL_REF", TRUE, (void *)&Chuck_OpenGL_STENCIL_REF );
    QUERY->add_svar( QUERY, "int", "STENCIL_VALUE_MASK", TRUE, (void *)&Chuck_OpenGL_STENCIL_VALUE_MASK );
    QUERY->add_svar( QUERY, "int", "STENCIL_WRITEMASK", TRUE, (void *)&Chuck_OpenGL_STENCIL_WRITEMASK );
    QUERY->add_svar( QUERY, "int", "STENCIL_BACK_FUNC", TRUE, (void *)&Chuck_OpenGL_STENCIL_BACK_FUNC );
    QUERY->add_svar( QUERY, "int", "STENCIL_BACK_FAIL", TRUE, (void *)&Chuck_OpenGL_STENCIL_BACK_FAIL );
    QUERY->add_svar( QUERY, "int", "STENCIL_BACK_PASS_DEPTH_FAIL", TRUE, (void *)&Chuck_OpenGL_STENCIL_BACK_PASS_DEPTH_FAIL );
    QUERY->add_svar( QUERY, "int", "STENCIL_BACK_PASS_DEPTH_PASS", TRUE, (void *)&Chuck_OpenGL_STENCIL_BACK_PASS_DEPTH_PASS );
    QUERY->add_svar( QUERY, "int", "STENCIL_BACK_REF", TRUE, (void *)&Chuck_OpenGL_STENCIL_BACK_REF );
    QUERY->add_svar( QUERY, "int", "STENCIL_BACK_VALUE_MASK", TRUE, (void *)&Chuck_OpenGL_STENCIL_BACK_VALUE_MASK );
    QUERY->add_svar( QUERY, "int", "STENCIL_BACK_WRITEMASK", TRUE, (void *)&Chuck_OpenGL_STENCIL_BACK_WRITEMASK );
    QUERY->add_svar( QUERY, "int", "VIEWPORT", TRUE, (void *)&Chuck_OpenGL_VIEWPORT );
    QUERY->add_svar( QUERY, "int", "SCISSOR_BOX", TRUE, (void *)&Chuck_OpenGL_SCISSOR_BOX );
    QUERY->add_svar( QUERY, "int", "COLOR_CLEAR_VALUE", TRUE, (void *)&Chuck_OpenGL_COLOR_CLEAR_VALUE );
    QUERY->add_svar( QUERY, "int", "COLOR_WRITEMASK", TRUE, (void *)&Chuck_OpenGL_COLOR_WRITEMASK );
    QUERY->add_svar( QUERY, "int", "UNPACK_ALIGNMENT", TRUE, (void *)&Chuck_OpenGL_UNPACK_ALIGNMENT );
    QUERY->add_svar( QUERY, "int", "PACK_ALIGNMENT", TRUE, (void *)&Chuck_OpenGL_PACK_ALIGNMENT );
    QUERY->add_svar( QUERY, "int", "MAX_TEXTURE_SIZE", TRUE, (void *)&Chuck_OpenGL_MAX_TEXTURE_SIZE );
    QUERY->add_svar( QUERY, "int", "MAX_VIEWPORT_DIMS", TRUE, (void *)&Chuck_OpenGL_MAX_VIEWPORT_DIMS );
    QUERY->add_svar( QUERY, "int", "SUBPIXEL_BITS", TRUE, (void *)&Chuck_OpenGL_SUBPIXEL_BITS );
    QUERY->add_svar( QUERY, "int", "RED_BITS", TRUE, (void *)&Chuck_OpenGL_RED_BITS );
    QUERY->add_svar( QUERY, "int", "GREEN_BITS", TRUE, (void *)&Chuck_OpenGL_GREEN_BITS );
    QUERY->add_svar( QUERY, "int", "BLUE_BITS", TRUE, (void *)&Chuck_OpenGL_BLUE_BITS );
    QUERY->add_svar( QUERY, "int", "ALPHA_BITS", TRUE, (void *)&Chuck_OpenGL_ALPHA_BITS );
    QUERY->add_svar( QUERY, "int", "DEPTH_BITS", TRUE, (void *)&Chuck_OpenGL_DEPTH_BITS );
    QUERY->add_svar( QUERY, "int", "STENCIL_BITS", TRUE, (void *)&Chuck_OpenGL_STENCIL_BITS );
    QUERY->add_svar( QUERY, "int", "POLYGON_OFFSET_UNITS", TRUE, (void *)&Chuck_OpenGL_POLYGON_OFFSET_UNITS );
    QUERY->add_svar( QUERY, "int", "POLYGON_OFFSET_FACTOR", TRUE, (void *)&Chuck_OpenGL_POLYGON_OFFSET_FACTOR );
    QUERY->add_svar( QUERY, "int", "TEXTURE_BINDING_2D", TRUE, (void *)&Chuck_OpenGL_TEXTURE_BINDING_2D );
    QUERY->add_svar( QUERY, "int", "SAMPLE_BUFFERS", TRUE, (void *)&Chuck_OpenGL_SAMPLE_BUFFERS );
    QUERY->add_svar( QUERY, "int", "SAMPLES", TRUE, (void *)&Chuck_OpenGL_SAMPLES );
    QUERY->add_svar( QUERY, "int", "SAMPLE_COVERAGE_VALUE", TRUE, (void *)&Chuck_OpenGL_SAMPLE_COVERAGE_VALUE );
    QUERY->add_svar( QUERY, "int", "SAMPLE_COVERAGE_INVERT", TRUE, (void *)&Chuck_OpenGL_SAMPLE_COVERAGE_INVERT );
    QUERY->add_svar( QUERY, "int", "NUM_COMPRESSED_TEXTURE_FORMATS", TRUE, (void *)&Chuck_OpenGL_NUM_COMPRESSED_TEXTURE_FORMATS );
    QUERY->add_svar( QUERY, "int", "COMPRESSED_TEXTURE_FORMATS", TRUE, (void *)&Chuck_OpenGL_COMPRESSED_TEXTURE_FORMATS );
    QUERY->add_svar( QUERY, "int", "DONT_CARE", TRUE, (void *)&Chuck_OpenGL_DONT_CARE );
    QUERY->add_svar( QUERY, "int", "FASTEST", TRUE, (void *)&Chuck_OpenGL_FASTEST );
    QUERY->add_svar( QUERY, "int", "NICEST", TRUE, (void *)&Chuck_OpenGL_NICEST );
    QUERY->add_svar( QUERY, "int", "GENERATE_MIPMAP_HINT", TRUE, (void *)&Chuck_OpenGL_GENERATE_MIPMAP_HINT );
    QUERY->add_svar( QUERY, "int", "BYTE", TRUE, (void *)&Chuck_OpenGL_BYTE );
    QUERY->add_svar( QUERY, "int", "UNSIGNED_BYTE", TRUE, (void *)&Chuck_OpenGL_UNSIGNED_BYTE );
    QUERY->add_svar( QUERY, "int", "SHORT", TRUE, (void *)&Chuck_OpenGL_SHORT );
    QUERY->add_svar( QUERY, "int", "UNSIGNED_SHORT", TRUE, (void *)&Chuck_OpenGL_UNSIGNED_SHORT );
    QUERY->add_svar( QUERY, "int", "INT", TRUE, (void *)&Chuck_OpenGL_INT );
    QUERY->add_svar( QUERY, "int", "UNSIGNED_INT", TRUE, (void *)&Chuck_OpenGL_UNSIGNED_INT );
    QUERY->add_svar( QUERY, "int", "FLOAT", TRUE, (void *)&Chuck_OpenGL_FLOAT );
    QUERY->add_svar( QUERY, "int", "FIXED", TRUE, (void *)&Chuck_OpenGL_FIXED );
    QUERY->add_svar( QUERY, "int", "DEPTH_COMPONENT", TRUE, (void *)&Chuck_OpenGL_DEPTH_COMPONENT );
    QUERY->add_svar( QUERY, "int", "ALPHA", TRUE, (void *)&Chuck_OpenGL_ALPHA );
    QUERY->add_svar( QUERY, "int", "RGB", TRUE, (void *)&Chuck_OpenGL_RGB );
    QUERY->add_svar( QUERY, "int", "RGBA", TRUE, (void *)&Chuck_OpenGL_RGBA );
    QUERY->add_svar( QUERY, "int", "LUMINANCE", TRUE, (void *)&Chuck_OpenGL_LUMINANCE );
    QUERY->add_svar( QUERY, "int", "LUMINANCE_ALPHA", TRUE, (void *)&Chuck_OpenGL_LUMINANCE_ALPHA );
    QUERY->add_svar( QUERY, "int", "UNSIGNED_SHORT_4_4_4_4", TRUE, (void *)&Chuck_OpenGL_UNSIGNED_SHORT_4_4_4_4 );
    QUERY->add_svar( QUERY, "int", "UNSIGNED_SHORT_5_5_5_1", TRUE, (void *)&Chuck_OpenGL_UNSIGNED_SHORT_5_5_5_1 );
    QUERY->add_svar( QUERY, "int", "UNSIGNED_SHORT_5_6_5", TRUE, (void *)&Chuck_OpenGL_UNSIGNED_SHORT_5_6_5 );
    QUERY->add_svar( QUERY, "int", "FRAGMENT_SHADER", TRUE, (void *)&Chuck_OpenGL_FRAGMENT_SHADER );
    QUERY->add_svar( QUERY, "int", "VERTEX_SHADER", TRUE, (void *)&Chuck_OpenGL_VERTEX_SHADER );
    QUERY->add_svar( QUERY, "int", "MAX_VERTEX_ATTRIBS", TRUE, (void *)&Chuck_OpenGL_MAX_VERTEX_ATTRIBS );
    QUERY->add_svar( QUERY, "int", "MAX_VERTEX_UNIFORM_VECTORS", TRUE, (void *)&Chuck_OpenGL_MAX_VERTEX_UNIFORM_VECTORS );
    QUERY->add_svar( QUERY, "int", "MAX_VARYING_VECTORS", TRUE, (void *)&Chuck_OpenGL_MAX_VARYING_VECTORS );
    QUERY->add_svar( QUERY, "int", "MAX_COMBINED_TEXTURE_IMAGE_UNITS", TRUE, (void *)&Chuck_OpenGL_MAX_COMBINED_TEXTURE_IMAGE_UNITS );
    QUERY->add_svar( QUERY, "int", "MAX_VERTEX_TEXTURE_IMAGE_UNITS", TRUE, (void *)&Chuck_OpenGL_MAX_VERTEX_TEXTURE_IMAGE_UNITS );
    QUERY->add_svar( QUERY, "int", "MAX_TEXTURE_IMAGE_UNITS", TRUE, (void *)&Chuck_OpenGL_MAX_TEXTURE_IMAGE_UNITS );
    QUERY->add_svar( QUERY, "int", "MAX_FRAGMENT_UNIFORM_VECTORS", TRUE, (void *)&Chuck_OpenGL_MAX_FRAGMENT_UNIFORM_VECTORS );
    QUERY->add_svar( QUERY, "int", "SHADER_TYPE", TRUE, (void *)&Chuck_OpenGL_SHADER_TYPE );
    QUERY->add_svar( QUERY, "int", "DELETE_STATUS", TRUE, (void *)&Chuck_OpenGL_DELETE_STATUS );
    QUERY->add_svar( QUERY, "int", "LINK_STATUS", TRUE, (void *)&Chuck_OpenGL_LINK_STATUS );
    QUERY->add_svar( QUERY, "int", "VALIDATE_STATUS", TRUE, (void *)&Chuck_OpenGL_VALIDATE_STATUS );
    QUERY->add_svar( QUERY, "int", "ATTACHED_SHADERS", TRUE, (void *)&Chuck_OpenGL_ATTACHED_SHADERS );
    QUERY->add_svar( QUERY, "int", "ACTIVE_UNIFORMS", TRUE, (void *)&Chuck_OpenGL_ACTIVE_UNIFORMS );
    QUERY->add_svar( QUERY, "int", "ACTIVE_UNIFORM_MAX_LENGTH", TRUE, (void *)&Chuck_OpenGL_ACTIVE_UNIFORM_MAX_LENGTH );
    QUERY->add_svar( QUERY, "int", "ACTIVE_ATTRIBUTES", TRUE, (void *)&Chuck_OpenGL_ACTIVE_ATTRIBUTES );
    QUERY->add_svar( QUERY, "int", "ACTIVE_ATTRIBUTE_MAX_LENGTH", TRUE, (void *)&Chuck_OpenGL_ACTIVE_ATTRIBUTE_MAX_LENGTH );
    QUERY->add_svar( QUERY, "int", "SHADING_LANGUAGE_VERSION", TRUE, (void *)&Chuck_OpenGL_SHADING_LANGUAGE_VERSION );
    QUERY->add_svar( QUERY, "int", "CURRENT_PROGRAM", TRUE, (void *)&Chuck_OpenGL_CURRENT_PROGRAM );
    QUERY->add_svar( QUERY, "int", "NEVER", TRUE, (void *)&Chuck_OpenGL_NEVER );
    QUERY->add_svar( QUERY, "int", "LESS", TRUE, (void *)&Chuck_OpenGL_LESS );
    QUERY->add_svar( QUERY, "int", "EQUAL", TRUE, (void *)&Chuck_OpenGL_EQUAL );
    QUERY->add_svar( QUERY, "int", "LEQUAL", TRUE, (void *)&Chuck_OpenGL_LEQUAL );
    QUERY->add_svar( QUERY, "int", "GREATER", TRUE, (void *)&Chuck_OpenGL_GREATER );
    QUERY->add_svar( QUERY, "int", "NOTEQUAL", TRUE, (void *)&Chuck_OpenGL_NOTEQUAL );
    QUERY->add_svar( QUERY, "int", "GEQUAL", TRUE, (void *)&Chuck_OpenGL_GEQUAL );
    QUERY->add_svar( QUERY, "int", "ALWAYS", TRUE, (void *)&Chuck_OpenGL_ALWAYS );
    QUERY->add_svar( QUERY, "int", "KEEP", TRUE, (void *)&Chuck_OpenGL_KEEP );
    QUERY->add_svar( QUERY, "int", "REPLACE", TRUE, (void *)&Chuck_OpenGL_REPLACE );
    QUERY->add_svar( QUERY, "int", "INCR", TRUE, (void *)&Chuck_OpenGL_INCR );
    QUERY->add_svar( QUERY, "int", "DECR", TRUE, (void *)&Chuck_OpenGL_DECR );
    QUERY->add_svar( QUERY, "int", "INVERT", TRUE, (void *)&Chuck_OpenGL_INVERT );
    QUERY->add_svar( QUERY, "int", "INCR_WRAP", TRUE, (void *)&Chuck_OpenGL_INCR_WRAP );
    QUERY->add_svar( QUERY, "int", "DECR_WRAP", TRUE, (void *)&Chuck_OpenGL_DECR_WRAP );
    QUERY->add_svar( QUERY, "int", "VENDOR", TRUE, (void *)&Chuck_OpenGL_VENDOR );
    QUERY->add_svar( QUERY, "int", "RENDERER", TRUE, (void *)&Chuck_OpenGL_RENDERER );
    QUERY->add_svar( QUERY, "int", "VERSION", TRUE, (void *)&Chuck_OpenGL_VERSION );
    QUERY->add_svar( QUERY, "int", "EXTENSIONS", TRUE, (void *)&Chuck_OpenGL_EXTENSIONS );
    QUERY->add_svar( QUERY, "int", "NEAREST", TRUE, (void *)&Chuck_OpenGL_NEAREST );
    QUERY->add_svar( QUERY, "int", "LINEAR", TRUE, (void *)&Chuck_OpenGL_LINEAR );
    QUERY->add_svar( QUERY, "int", "NEAREST_MIPMAP_NEAREST", TRUE, (void *)&Chuck_OpenGL_NEAREST_MIPMAP_NEAREST );
    QUERY->add_svar( QUERY, "int", "LINEAR_MIPMAP_NEAREST", TRUE, (void *)&Chuck_OpenGL_LINEAR_MIPMAP_NEAREST );
    QUERY->add_svar( QUERY, "int", "NEAREST_MIPMAP_LINEAR", TRUE, (void *)&Chuck_OpenGL_NEAREST_MIPMAP_LINEAR );
    QUERY->add_svar( QUERY, "int", "LINEAR_MIPMAP_LINEAR", TRUE, (void *)&Chuck_OpenGL_LINEAR_MIPMAP_LINEAR );
    QUERY->add_svar( QUERY, "int", "TEXTURE_MAG_FILTER", TRUE, (void *)&Chuck_OpenGL_TEXTURE_MAG_FILTER );
    QUERY->add_svar( QUERY, "int", "TEXTURE_MIN_FILTER", TRUE, (void *)&Chuck_OpenGL_TEXTURE_MIN_FILTER );
    QUERY->add_svar( QUERY, "int", "TEXTURE_WRAP_S", TRUE, (void *)&Chuck_OpenGL_TEXTURE_WRAP_S );
    QUERY->add_svar( QUERY, "int", "TEXTURE_WRAP_T", TRUE, (void *)&Chuck_OpenGL_TEXTURE_WRAP_T );
    QUERY->add_svar( QUERY, "int", "TEXTURE", TRUE, (void *)&Chuck_OpenGL_TEXTURE );
    QUERY->add_svar( QUERY, "int", "TEXTURE_CUBE_MAP", TRUE, (void *)&Chuck_OpenGL_TEXTURE_CUBE_MAP );
    QUERY->add_svar( QUERY, "int", "TEXTURE_BINDING_CUBE_MAP", TRUE, (void *)&Chuck_OpenGL_TEXTURE_BINDING_CUBE_MAP );
    QUERY->add_svar( QUERY, "int", "TEXTURE_CUBE_MAP_POSITIVE_X", TRUE, (void *)&Chuck_OpenGL_TEXTURE_CUBE_MAP_POSITIVE_X );
    QUERY->add_svar( QUERY, "int", "TEXTURE_CUBE_MAP_NEGATIVE_X", TRUE, (void *)&Chuck_OpenGL_TEXTURE_CUBE_MAP_NEGATIVE_X );
    QUERY->add_svar( QUERY, "int", "TEXTURE_CUBE_MAP_POSITIVE_Y", TRUE, (void *)&Chuck_OpenGL_TEXTURE_CUBE_MAP_POSITIVE_Y );
    QUERY->add_svar( QUERY, "int", "TEXTURE_CUBE_MAP_NEGATIVE_Y", TRUE, (void *)&Chuck_OpenGL_TEXTURE_CUBE_MAP_NEGATIVE_Y );
    QUERY->add_svar( QUERY, "int", "TEXTURE_CUBE_MAP_POSITIVE_Z", TRUE, (void *)&Chuck_OpenGL_TEXTURE_CUBE_MAP_POSITIVE_Z );
    QUERY->add_svar( QUERY, "int", "TEXTURE_CUBE_MAP_NEGATIVE_Z", TRUE, (void *)&Chuck_OpenGL_TEXTURE_CUBE_MAP_NEGATIVE_Z );
    QUERY->add_svar( QUERY, "int", "MAX_CUBE_MAP_TEXTURE_SIZE", TRUE, (void *)&Chuck_OpenGL_MAX_CUBE_MAP_TEXTURE_SIZE );
    QUERY->add_svar( QUERY, "int", "TEXTURE0", TRUE, (void *)&Chuck_OpenGL_TEXTURE0 );
    QUERY->add_svar( QUERY, "int", "TEXTURE1", TRUE, (void *)&Chuck_OpenGL_TEXTURE1 );
    QUERY->add_svar( QUERY, "int", "TEXTURE2", TRUE, (void *)&Chuck_OpenGL_TEXTURE2 );
    QUERY->add_svar( QUERY, "int", "TEXTURE3", TRUE, (void *)&Chuck_OpenGL_TEXTURE3 );
    QUERY->add_svar( QUERY, "int", "TEXTURE4", TRUE, (void *)&Chuck_OpenGL_TEXTURE4 );
    QUERY->add_svar( QUERY, "int", "TEXTURE5", TRUE, (void *)&Chuck_OpenGL_TEXTURE5 );
    QUERY->add_svar( QUERY, "int", "TEXTURE6", TRUE, (void *)&Chuck_OpenGL_TEXTURE6 );
    QUERY->add_svar( QUERY, "int", "TEXTURE7", TRUE, (void *)&Chuck_OpenGL_TEXTURE7 );
    QUERY->add_svar( QUERY, "int", "TEXTURE8", TRUE, (void *)&Chuck_OpenGL_TEXTURE8 );
    QUERY->add_svar( QUERY, "int", "TEXTURE9", TRUE, (void *)&Chuck_OpenGL_TEXTURE9 );
    QUERY->add_svar( QUERY, "int", "TEXTURE10", TRUE, (void *)&Chuck_OpenGL_TEXTURE10 );
    QUERY->add_svar( QUERY, "int", "TEXTURE11", TRUE, (void *)&Chuck_OpenGL_TEXTURE11 );
    QUERY->add_svar( QUERY, "int", "TEXTURE12", TRUE, (void *)&Chuck_OpenGL_TEXTURE12 );
    QUERY->add_svar( QUERY, "int", "TEXTURE13", TRUE, (void *)&Chuck_OpenGL_TEXTURE13 );
    QUERY->add_svar( QUERY, "int", "TEXTURE14", TRUE, (void *)&Chuck_OpenGL_TEXTURE14 );
    QUERY->add_svar( QUERY, "int", "TEXTURE15", TRUE, (void *)&Chuck_OpenGL_TEXTURE15 );
    QUERY->add_svar( QUERY, "int", "TEXTURE16", TRUE, (void *)&Chuck_OpenGL_TEXTURE16 );
    QUERY->add_svar( QUERY, "int", "TEXTURE17", TRUE, (void *)&Chuck_OpenGL_TEXTURE17 );
    QUERY->add_svar( QUERY, "int", "TEXTURE18", TRUE, (void *)&Chuck_OpenGL_TEXTURE18 );
    QUERY->add_svar( QUERY, "int", "TEXTURE19", TRUE, (void *)&Chuck_OpenGL_TEXTURE19 );
    QUERY->add_svar( QUERY, "int", "TEXTURE20", TRUE, (void *)&Chuck_OpenGL_TEXTURE20 );
    QUERY->add_svar( QUERY, "int", "TEXTURE21", TRUE, (void *)&Chuck_OpenGL_TEXTURE21 );
    QUERY->add_svar( QUERY, "int", "TEXTURE22", TRUE, (void *)&Chuck_OpenGL_TEXTURE22 );
    QUERY->add_svar( QUERY, "int", "TEXTURE23", TRUE, (void *)&Chuck_OpenGL_TEXTURE23 );
    QUERY->add_svar( QUERY, "int", "TEXTURE24", TRUE, (void *)&Chuck_OpenGL_TEXTURE24 );
    QUERY->add_svar( QUERY, "int", "TEXTURE25", TRUE, (void *)&Chuck_OpenGL_TEXTURE25 );
    QUERY->add_svar( QUERY, "int", "TEXTURE26", TRUE, (void *)&Chuck_OpenGL_TEXTURE26 );
    QUERY->add_svar( QUERY, "int", "TEXTURE27", TRUE, (void *)&Chuck_OpenGL_TEXTURE27 );
    QUERY->add_svar( QUERY, "int", "TEXTURE28", TRUE, (void *)&Chuck_OpenGL_TEXTURE28 );
    QUERY->add_svar( QUERY, "int", "TEXTURE29", TRUE, (void *)&Chuck_OpenGL_TEXTURE29 );
    QUERY->add_svar( QUERY, "int", "TEXTURE30", TRUE, (void *)&Chuck_OpenGL_TEXTURE30 );
    QUERY->add_svar( QUERY, "int", "TEXTURE31", TRUE, (void *)&Chuck_OpenGL_TEXTURE31 );
    QUERY->add_svar( QUERY, "int", "ACTIVE_TEXTURE", TRUE, (void *)&Chuck_OpenGL_ACTIVE_TEXTURE );
    QUERY->add_svar( QUERY, "int", "REPEAT", TRUE, (void *)&Chuck_OpenGL_REPEAT );
    QUERY->add_svar( QUERY, "int", "CLAMP_TO_EDGE", TRUE, (void *)&Chuck_OpenGL_CLAMP_TO_EDGE );
    QUERY->add_svar( QUERY, "int", "MIRRORED_REPEAT", TRUE, (void *)&Chuck_OpenGL_MIRRORED_REPEAT );
    QUERY->add_svar( QUERY, "int", "FLOAT_VEC2", TRUE, (void *)&Chuck_OpenGL_FLOAT_VEC2 );
    QUERY->add_svar( QUERY, "int", "FLOAT_VEC3", TRUE, (void *)&Chuck_OpenGL_FLOAT_VEC3 );
    QUERY->add_svar( QUERY, "int", "FLOAT_VEC4", TRUE, (void *)&Chuck_OpenGL_FLOAT_VEC4 );
    QUERY->add_svar( QUERY, "int", "INT_VEC2", TRUE, (void *)&Chuck_OpenGL_INT_VEC2 );
    QUERY->add_svar( QUERY, "int", "INT_VEC3", TRUE, (void *)&Chuck_OpenGL_INT_VEC3 );
    QUERY->add_svar( QUERY, "int", "INT_VEC4", TRUE, (void *)&Chuck_OpenGL_INT_VEC4 );
    QUERY->add_svar( QUERY, "int", "BOOL", TRUE, (void *)&Chuck_OpenGL_BOOL );
    QUERY->add_svar( QUERY, "int", "BOOL_VEC2", TRUE, (void *)&Chuck_OpenGL_BOOL_VEC2 );
    QUERY->add_svar( QUERY, "int", "BOOL_VEC3", TRUE, (void *)&Chuck_OpenGL_BOOL_VEC3 );
    QUERY->add_svar( QUERY, "int", "BOOL_VEC4", TRUE, (void *)&Chuck_OpenGL_BOOL_VEC4 );
    QUERY->add_svar( QUERY, "int", "FLOAT_MAT2", TRUE, (void *)&Chuck_OpenGL_FLOAT_MAT2 );
    QUERY->add_svar( QUERY, "int", "FLOAT_MAT3", TRUE, (void *)&Chuck_OpenGL_FLOAT_MAT3 );
    QUERY->add_svar( QUERY, "int", "FLOAT_MAT4", TRUE, (void *)&Chuck_OpenGL_FLOAT_MAT4 );
    QUERY->add_svar( QUERY, "int", "SAMPLER_2D", TRUE, (void *)&Chuck_OpenGL_SAMPLER_2D );
    QUERY->add_svar( QUERY, "int", "SAMPLER_CUBE", TRUE, (void *)&Chuck_OpenGL_SAMPLER_CUBE );
    QUERY->add_svar( QUERY, "int", "VERTEX_ATTRIB_ARRAY_ENABLED", TRUE, (void *)&Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_ENABLED );
    QUERY->add_svar( QUERY, "int", "VERTEX_ATTRIB_ARRAY_SIZE", TRUE, (void *)&Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_SIZE );
    QUERY->add_svar( QUERY, "int", "VERTEX_ATTRIB_ARRAY_STRIDE", TRUE, (void *)&Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_STRIDE );
    QUERY->add_svar( QUERY, "int", "VERTEX_ATTRIB_ARRAY_TYPE", TRUE, (void *)&Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_TYPE );
    QUERY->add_svar( QUERY, "int", "VERTEX_ATTRIB_ARRAY_NORMALIZED", TRUE, (void *)&Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_NORMALIZED );
    QUERY->add_svar( QUERY, "int", "VERTEX_ATTRIB_ARRAY_POINTER", TRUE, (void *)&Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_POINTER );
    QUERY->add_svar( QUERY, "int", "VERTEX_ATTRIB_ARRAY_BUFFER_BINDING", TRUE, (void *)&Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING );
    QUERY->add_svar( QUERY, "int", "IMPLEMENTATION_COLOR_READ_TYPE", TRUE, (void *)&Chuck_OpenGL_IMPLEMENTATION_COLOR_READ_TYPE );
    QUERY->add_svar( QUERY, "int", "IMPLEMENTATION_COLOR_READ_FORMAT", TRUE, (void *)&Chuck_OpenGL_IMPLEMENTATION_COLOR_READ_FORMAT );
    QUERY->add_svar( QUERY, "int", "COMPILE_STATUS", TRUE, (void *)&Chuck_OpenGL_COMPILE_STATUS );
    QUERY->add_svar( QUERY, "int", "INFO_LOG_LENGTH", TRUE, (void *)&Chuck_OpenGL_INFO_LOG_LENGTH );
    QUERY->add_svar( QUERY, "int", "SHADER_SOURCE_LENGTH", TRUE, (void *)&Chuck_OpenGL_SHADER_SOURCE_LENGTH );
    QUERY->add_svar( QUERY, "int", "SHADER_COMPILER", TRUE, (void *)&Chuck_OpenGL_SHADER_COMPILER );
    QUERY->add_svar( QUERY, "int", "SHADER_BINARY_FORMATS", TRUE, (void *)&Chuck_OpenGL_SHADER_BINARY_FORMATS );
    QUERY->add_svar( QUERY, "int", "NUM_SHADER_BINARY_FORMATS", TRUE, (void *)&Chuck_OpenGL_NUM_SHADER_BINARY_FORMATS );
    QUERY->add_svar( QUERY, "int", "LOW_FLOAT", TRUE, (void *)&Chuck_OpenGL_LOW_FLOAT );
    QUERY->add_svar( QUERY, "int", "MEDIUM_FLOAT", TRUE, (void *)&Chuck_OpenGL_MEDIUM_FLOAT );
    QUERY->add_svar( QUERY, "int", "HIGH_FLOAT", TRUE, (void *)&Chuck_OpenGL_HIGH_FLOAT );
    QUERY->add_svar( QUERY, "int", "LOW_INT", TRUE, (void *)&Chuck_OpenGL_LOW_INT );
    QUERY->add_svar( QUERY, "int", "MEDIUM_INT", TRUE, (void *)&Chuck_OpenGL_MEDIUM_INT );
    QUERY->add_svar( QUERY, "int", "HIGH_INT", TRUE, (void *)&Chuck_OpenGL_HIGH_INT );
    QUERY->add_svar( QUERY, "int", "FRAMEBUFFER", TRUE, (void *)&Chuck_OpenGL_FRAMEBUFFER );
    QUERY->add_svar( QUERY, "int", "RENDERBUFFER", TRUE, (void *)&Chuck_OpenGL_RENDERBUFFER );
    QUERY->add_svar( QUERY, "int", "RGBA4", TRUE, (void *)&Chuck_OpenGL_RGBA4 );
    QUERY->add_svar( QUERY, "int", "RGB5_A1", TRUE, (void *)&Chuck_OpenGL_RGB5_A1 );
    QUERY->add_svar( QUERY, "int", "RGB565", TRUE, (void *)&Chuck_OpenGL_RGB565 );
    QUERY->add_svar( QUERY, "int", "DEPTH_COMPONENT16", TRUE, (void *)&Chuck_OpenGL_DEPTH_COMPONENT16 );
    QUERY->add_svar( QUERY, "int", "STENCIL_INDEX8", TRUE, (void *)&Chuck_OpenGL_STENCIL_INDEX8 );
    QUERY->add_svar( QUERY, "int", "RENDERBUFFER_WIDTH", TRUE, (void *)&Chuck_OpenGL_RENDERBUFFER_WIDTH );
    QUERY->add_svar( QUERY, "int", "RENDERBUFFER_HEIGHT", TRUE, (void *)&Chuck_OpenGL_RENDERBUFFER_HEIGHT );
    QUERY->add_svar( QUERY, "int", "RENDERBUFFER_INTERNAL_FORMAT", TRUE, (void *)&Chuck_OpenGL_RENDERBUFFER_INTERNAL_FORMAT );
    QUERY->add_svar( QUERY, "int", "RENDERBUFFER_RED_SIZE", TRUE, (void *)&Chuck_OpenGL_RENDERBUFFER_RED_SIZE );
    QUERY->add_svar( QUERY, "int", "RENDERBUFFER_GREEN_SIZE", TRUE, (void *)&Chuck_OpenGL_RENDERBUFFER_GREEN_SIZE );
    QUERY->add_svar( QUERY, "int", "RENDERBUFFER_BLUE_SIZE", TRUE, (void *)&Chuck_OpenGL_RENDERBUFFER_BLUE_SIZE );
    QUERY->add_svar( QUERY, "int", "RENDERBUFFER_ALPHA_SIZE", TRUE, (void *)&Chuck_OpenGL_RENDERBUFFER_ALPHA_SIZE );
    QUERY->add_svar( QUERY, "int", "RENDERBUFFER_DEPTH_SIZE", TRUE, (void *)&Chuck_OpenGL_RENDERBUFFER_DEPTH_SIZE );
    QUERY->add_svar( QUERY, "int", "RENDERBUFFER_STENCIL_SIZE", TRUE, (void *)&Chuck_OpenGL_RENDERBUFFER_STENCIL_SIZE );
    QUERY->add_svar( QUERY, "int", "FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE", TRUE, (void *)&Chuck_OpenGL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE );
    QUERY->add_svar( QUERY, "int", "FRAMEBUFFER_ATTACHMENT_OBJECT_NAME", TRUE, (void *)&Chuck_OpenGL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME );
    QUERY->add_svar( QUERY, "int", "FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL", TRUE, (void *)&Chuck_OpenGL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL );
    QUERY->add_svar( QUERY, "int", "FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE", TRUE, (void *)&Chuck_OpenGL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE );
    QUERY->add_svar( QUERY, "int", "COLOR_ATTACHMENT0", TRUE, (void *)&Chuck_OpenGL_COLOR_ATTACHMENT0 );
    QUERY->add_svar( QUERY, "int", "DEPTH_ATTACHMENT", TRUE, (void *)&Chuck_OpenGL_DEPTH_ATTACHMENT );
    QUERY->add_svar( QUERY, "int", "STENCIL_ATTACHMENT", TRUE, (void *)&Chuck_OpenGL_STENCIL_ATTACHMENT );
    QUERY->add_svar( QUERY, "int", "NONE", TRUE, (void *)&Chuck_OpenGL_NONE );
    QUERY->add_svar( QUERY, "int", "FRAMEBUFFER_COMPLETE", TRUE, (void *)&Chuck_OpenGL_FRAMEBUFFER_COMPLETE );
    QUERY->add_svar( QUERY, "int", "FRAMEBUFFER_INCOMPLETE_ATTACHMENT", TRUE, (void *)&Chuck_OpenGL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT );
    QUERY->add_svar( QUERY, "int", "FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT", TRUE, (void *)&Chuck_OpenGL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT );
    QUERY->add_svar( QUERY, "int", "FRAMEBUFFER_INCOMPLETE_DIMENSIONS", TRUE, (void *)&Chuck_OpenGL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS );
    QUERY->add_svar( QUERY, "int", "FRAMEBUFFER_UNSUPPORTED", TRUE, (void *)&Chuck_OpenGL_FRAMEBUFFER_UNSUPPORTED );
    QUERY->add_svar( QUERY, "int", "FRAMEBUFFER_BINDING", TRUE, (void *)&Chuck_OpenGL_FRAMEBUFFER_BINDING );
    QUERY->add_svar( QUERY, "int", "RENDERBUFFER_BINDING", TRUE, (void *)&Chuck_OpenGL_RENDERBUFFER_BINDING );
    QUERY->add_svar( QUERY, "int", "MAX_RENDERBUFFER_SIZE", TRUE, (void *)&Chuck_OpenGL_MAX_RENDERBUFFER_SIZE );
    QUERY->add_svar( QUERY, "int", "INVALID_FRAMEBUFFER_OPERATION", TRUE, (void *)&Chuck_OpenGL_INVALID_FRAMEBUFFER_OPERATION );

    QUERY->add_mfun(QUERY, Chuck_OpenGL_ActiveTexture, "void", "ActiveTexture");
    QUERY->add_arg(QUERY, "int", "texture");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_AttachShader, "void", "AttachShader");
    QUERY->add_arg(QUERY, "int", "program");
    QUERY->add_arg(QUERY, "int", "shader");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_BindAttribLocation, "void", "BindAttribLocation");
    QUERY->add_arg(QUERY, "int", "program");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int[]", "name");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_BindBuffer, "void", "BindBuffer");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "buffer");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_BindFramebuffer, "void", "BindFramebuffer");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "framebuffer");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_BindRenderbuffer, "void", "BindRenderbuffer");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "renderbuffer");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_BindTexture, "void", "BindTexture");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "texture");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_BlendColor, "void", "BlendColor");
    QUERY->add_arg(QUERY, "float", "red");
    QUERY->add_arg(QUERY, "float", "green");
    QUERY->add_arg(QUERY, "float", "blue");
    QUERY->add_arg(QUERY, "float", "alpha");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_BlendEquation, "void", "BlendEquation");
    QUERY->add_arg(QUERY, "int", "mode");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_BlendEquationSeparate, "void", "BlendEquationSeparate");
    QUERY->add_arg(QUERY, "int", "modeRGB");
    QUERY->add_arg(QUERY, "int", "modeAlpha");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_BlendFunc, "void", "BlendFunc");
    QUERY->add_arg(QUERY, "int", "sfactor");
    QUERY->add_arg(QUERY, "int", "dfactor");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_BlendFuncSeparate, "void", "BlendFuncSeparate");
    QUERY->add_arg(QUERY, "int", "sfactorRGB");
    QUERY->add_arg(QUERY, "int", "dfactorRGB");
    QUERY->add_arg(QUERY, "int", "sfactorAlpha");
    QUERY->add_arg(QUERY, "int", "dfactorAlpha");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_CheckFramebufferStatus, "int", "CheckFramebufferStatus");
    QUERY->add_arg(QUERY, "int", "target");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Clear, "void", "Clear");
    QUERY->add_arg(QUERY, "int", "mask");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_ClearColor, "void", "ClearColor");
    QUERY->add_arg(QUERY, "float", "red");
    QUERY->add_arg(QUERY, "float", "green");
    QUERY->add_arg(QUERY, "float", "blue");
    QUERY->add_arg(QUERY, "float", "alpha");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_ClearDepthf, "void", "ClearDepthf");
    QUERY->add_arg(QUERY, "float", "d");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_ClearStencil, "void", "ClearStencil");
    QUERY->add_arg(QUERY, "int", "s");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_ColorMask, "void", "ColorMask");
    QUERY->add_arg(QUERY, "int", "red");
    QUERY->add_arg(QUERY, "int", "green");
    QUERY->add_arg(QUERY, "int", "blue");
    QUERY->add_arg(QUERY, "int", "alpha");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_CompileShader, "void", "CompileShader");
    QUERY->add_arg(QUERY, "int", "shader");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_CompressedTexImage2D, "void", "CompressedTexImage2D");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "level");
    QUERY->add_arg(QUERY, "int", "internalformat");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "height");
    QUERY->add_arg(QUERY, "int", "border");
    QUERY->add_arg(QUERY, "int", "imageSize");
    QUERY->add_arg(QUERY, "Object", "data");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_CompressedTexSubImage2D, "void", "CompressedTexSubImage2D");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "level");
    QUERY->add_arg(QUERY, "int", "xoffset");
    QUERY->add_arg(QUERY, "int", "yoffset");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "height");
    QUERY->add_arg(QUERY, "int", "format");
    QUERY->add_arg(QUERY, "int", "imageSize");
    QUERY->add_arg(QUERY, "Object", "data");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_CopyTexImage2D, "void", "CopyTexImage2D");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "level");
    QUERY->add_arg(QUERY, "int", "internalformat");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "height");
    QUERY->add_arg(QUERY, "int", "border");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_CopyTexSubImage2D, "void", "CopyTexSubImage2D");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "level");
    QUERY->add_arg(QUERY, "int", "xoffset");
    QUERY->add_arg(QUERY, "int", "yoffset");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "height");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_CreateProgram, "int", "CreateProgram");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_CreateShader, "int", "CreateShader");
    QUERY->add_arg(QUERY, "int", "type");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_CullFace, "void", "CullFace");
    QUERY->add_arg(QUERY, "int", "mode");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DeleteBuffers, "void", "DeleteBuffers");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->add_arg(QUERY, "int[]", "buffers");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DeleteFramebuffers, "void", "DeleteFramebuffers");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->add_arg(QUERY, "int[]", "framebuffers");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DeleteProgram, "void", "DeleteProgram");
    QUERY->add_arg(QUERY, "int", "program");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DeleteRenderbuffers, "void", "DeleteRenderbuffers");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->add_arg(QUERY, "int[]", "renderbuffers");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DeleteShader, "void", "DeleteShader");
    QUERY->add_arg(QUERY, "int", "shader");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DeleteTextures, "void", "DeleteTextures");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->add_arg(QUERY, "int[]", "textures");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DepthFunc, "void", "DepthFunc");
    QUERY->add_arg(QUERY, "int", "func");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DepthMask, "void", "DepthMask");
    QUERY->add_arg(QUERY, "int", "flag");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DepthRangef, "void", "DepthRangef");
    QUERY->add_arg(QUERY, "float", "n");
    QUERY->add_arg(QUERY, "float", "f");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DetachShader, "void", "DetachShader");
    QUERY->add_arg(QUERY, "int", "program");
    QUERY->add_arg(QUERY, "int", "shader");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Disable, "void", "Disable");
    QUERY->add_arg(QUERY, "int", "cap");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DisableVertexAttribArray, "void", "DisableVertexAttribArray");
    QUERY->add_arg(QUERY, "int", "index");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DrawArrays, "void", "DrawArrays");
    QUERY->add_arg(QUERY, "int", "mode");
    QUERY->add_arg(QUERY, "int", "first");
    QUERY->add_arg(QUERY, "int", "count");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DrawElements, "void", "DrawElements");
    QUERY->add_arg(QUERY, "int", "mode");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "int", "type");
    QUERY->add_arg(QUERY, "Object", "indices");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Enable, "void", "Enable");
    QUERY->add_arg(QUERY, "int", "cap");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_EnableVertexAttribArray, "void", "EnableVertexAttribArray");
    QUERY->add_arg(QUERY, "int", "index");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Finish, "void", "Finish");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Flush, "void", "Flush");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_FramebufferRenderbuffer, "void", "FramebufferRenderbuffer");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "attachment");
    QUERY->add_arg(QUERY, "int", "renderbuffertarget");
    QUERY->add_arg(QUERY, "int", "renderbuffer");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_FramebufferTexture2D, "void", "FramebufferTexture2D");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "attachment");
    QUERY->add_arg(QUERY, "int", "textarget");
    QUERY->add_arg(QUERY, "int", "texture");
    QUERY->add_arg(QUERY, "int", "level");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_FrontFace, "void", "FrontFace");
    QUERY->add_arg(QUERY, "int", "mode");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GenBuffers, "void", "GenBuffers");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->add_arg(QUERY, "int[]", "buffers");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GenerateMipmap, "void", "GenerateMipmap");
    QUERY->add_arg(QUERY, "int", "target");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GenFramebuffers, "void", "GenFramebuffers");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->add_arg(QUERY, "int[]", "framebuffers");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GenRenderbuffers, "void", "GenRenderbuffers");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->add_arg(QUERY, "int[]", "renderbuffers");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GenTextures, "void", "GenTextures");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->add_arg(QUERY, "int[]", "textures");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetActiveAttrib, "void", "GetActiveAttrib");
    QUERY->add_arg(QUERY, "int", "program");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int", "bufSize");
    QUERY->add_arg(QUERY, "int[]", "length");
    QUERY->add_arg(QUERY, "int[]", "size");
    QUERY->add_arg(QUERY, "int[]", "type");
    QUERY->add_arg(QUERY, "int[]", "name");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetActiveUniform, "void", "GetActiveUniform");
    QUERY->add_arg(QUERY, "int", "program");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int", "bufSize");
    QUERY->add_arg(QUERY, "int[]", "length");
    QUERY->add_arg(QUERY, "int[]", "size");
    QUERY->add_arg(QUERY, "int[]", "type");
    QUERY->add_arg(QUERY, "int[]", "name");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetAttachedShaders, "void", "GetAttachedShaders");
    QUERY->add_arg(QUERY, "int", "program");
    QUERY->add_arg(QUERY, "int", "maxCount");
    QUERY->add_arg(QUERY, "int[]", "count");
    QUERY->add_arg(QUERY, "int[]", "shaders");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetAttribLocation, "int", "GetAttribLocation");
    QUERY->add_arg(QUERY, "int", "program");
    QUERY->add_arg(QUERY, "int[]", "name");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetBooleanv, "void", "GetBooleanv");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "data");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetBufferParameteriv, "void", "GetBufferParameteriv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetError, "int", "GetError");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetFloatv, "void", "GetFloatv");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float[]", "data");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetFramebufferAttachmentParameteriv, "void", "GetFramebufferAttachmentParameteriv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "attachment");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetIntegerv, "void", "GetIntegerv");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "data");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetProgramiv, "void", "GetProgramiv");
    QUERY->add_arg(QUERY, "int", "program");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetProgramInfoLog, "void", "GetProgramInfoLog");
    QUERY->add_arg(QUERY, "int", "program");
    QUERY->add_arg(QUERY, "int", "bufSize");
    QUERY->add_arg(QUERY, "int[]", "length");
    QUERY->add_arg(QUERY, "int[]", "infoLog");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetRenderbufferParameteriv, "void", "GetRenderbufferParameteriv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetShaderiv, "void", "GetShaderiv");
    QUERY->add_arg(QUERY, "int", "shader");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetShaderInfoLog, "void", "GetShaderInfoLog");
    QUERY->add_arg(QUERY, "int", "shader");
    QUERY->add_arg(QUERY, "int", "bufSize");
    QUERY->add_arg(QUERY, "int[]", "length");
    QUERY->add_arg(QUERY, "int[]", "infoLog");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetShaderPrecisionFormat, "void", "GetShaderPrecisionFormat");
    QUERY->add_arg(QUERY, "int", "shadertype");
    QUERY->add_arg(QUERY, "int", "precisiontype");
    QUERY->add_arg(QUERY, "int[]", "range");
    QUERY->add_arg(QUERY, "int[]", "precision");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetShaderSource, "void", "GetShaderSource");
    QUERY->add_arg(QUERY, "int", "shader");
    QUERY->add_arg(QUERY, "int", "bufSize");
    QUERY->add_arg(QUERY, "int[]", "length");
    QUERY->add_arg(QUERY, "int[]", "source");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetTexParameterfv, "void", "GetTexParameterfv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetTexParameteriv, "void", "GetTexParameteriv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetUniformfv, "void", "GetUniformfv");
    QUERY->add_arg(QUERY, "int", "program");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "float[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetUniformiv, "void", "GetUniformiv");
    QUERY->add_arg(QUERY, "int", "program");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetUniformLocation, "int", "GetUniformLocation");
    QUERY->add_arg(QUERY, "int", "program");
    QUERY->add_arg(QUERY, "int[]", "name");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetVertexAttribfv, "void", "GetVertexAttribfv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetVertexAttribiv, "void", "GetVertexAttribiv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Hint, "void", "Hint");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "mode");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_IsBuffer, "int", "IsBuffer");
    QUERY->add_arg(QUERY, "int", "buffer");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_IsEnabled, "int", "IsEnabled");
    QUERY->add_arg(QUERY, "int", "cap");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_IsFramebuffer, "int", "IsFramebuffer");
    QUERY->add_arg(QUERY, "int", "framebuffer");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_IsProgram, "int", "IsProgram");
    QUERY->add_arg(QUERY, "int", "program");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_IsRenderbuffer, "int", "IsRenderbuffer");
    QUERY->add_arg(QUERY, "int", "renderbuffer");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_IsShader, "int", "IsShader");
    QUERY->add_arg(QUERY, "int", "shader");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_IsTexture, "int", "IsTexture");
    QUERY->add_arg(QUERY, "int", "texture");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_LineWidth, "void", "LineWidth");
    QUERY->add_arg(QUERY, "float", "width");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_LinkProgram, "void", "LinkProgram");
    QUERY->add_arg(QUERY, "int", "program");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PixelStorei, "void", "PixelStorei");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int", "param");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PolygonOffset, "void", "PolygonOffset");
    QUERY->add_arg(QUERY, "float", "factor");
    QUERY->add_arg(QUERY, "float", "units");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_ReadPixels, "void", "ReadPixels");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "height");
    QUERY->add_arg(QUERY, "int", "format");
    QUERY->add_arg(QUERY, "int", "type");
    QUERY->add_arg(QUERY, "Object", "pixels");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_ReleaseShaderCompiler, "void", "ReleaseShaderCompiler");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_RenderbufferStorage, "void", "RenderbufferStorage");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "internalformat");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "height");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_SampleCoverage, "void", "SampleCoverage");
    QUERY->add_arg(QUERY, "float", "value");
    QUERY->add_arg(QUERY, "int", "invert");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Scissor, "void", "Scissor");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "height");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_ShaderBinary, "void", "ShaderBinary");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "int[]", "shaders");
    QUERY->add_arg(QUERY, "int", "binaryformat");
    QUERY->add_arg(QUERY, "Object", "binary");
    QUERY->add_arg(QUERY, "int", "length");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_StencilFunc, "void", "StencilFunc");
    QUERY->add_arg(QUERY, "int", "func");
    QUERY->add_arg(QUERY, "int", "ref");
    QUERY->add_arg(QUERY, "int", "mask");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_StencilFuncSeparate, "void", "StencilFuncSeparate");
    QUERY->add_arg(QUERY, "int", "face");
    QUERY->add_arg(QUERY, "int", "func");
    QUERY->add_arg(QUERY, "int", "ref");
    QUERY->add_arg(QUERY, "int", "mask");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_StencilMask, "void", "StencilMask");
    QUERY->add_arg(QUERY, "int", "mask");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_StencilMaskSeparate, "void", "StencilMaskSeparate");
    QUERY->add_arg(QUERY, "int", "face");
    QUERY->add_arg(QUERY, "int", "mask");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_StencilOp, "void", "StencilOp");
    QUERY->add_arg(QUERY, "int", "fail");
    QUERY->add_arg(QUERY, "int", "zfail");
    QUERY->add_arg(QUERY, "int", "zpass");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_StencilOpSeparate, "void", "StencilOpSeparate");
    QUERY->add_arg(QUERY, "int", "face");
    QUERY->add_arg(QUERY, "int", "sfail");
    QUERY->add_arg(QUERY, "int", "dpfail");
    QUERY->add_arg(QUERY, "int", "dppass");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexImage2D, "void", "TexImage2D");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "level");
    QUERY->add_arg(QUERY, "int", "internalformat");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "height");
    QUERY->add_arg(QUERY, "int", "border");
    QUERY->add_arg(QUERY, "int", "format");
    QUERY->add_arg(QUERY, "int", "type");
    QUERY->add_arg(QUERY, "Object", "pixels");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexParameterf, "void", "TexParameterf");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float", "param");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexParameterfv, "void", "TexParameterfv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexParameteri, "void", "TexParameteri");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int", "param");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexParameteriv, "void", "TexParameteriv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexSubImage2D, "void", "TexSubImage2D");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "level");
    QUERY->add_arg(QUERY, "int", "xoffset");
    QUERY->add_arg(QUERY, "int", "yoffset");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "height");
    QUERY->add_arg(QUERY, "int", "format");
    QUERY->add_arg(QUERY, "int", "type");
    QUERY->add_arg(QUERY, "Object", "pixels");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform1f, "void", "Uniform1f");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "float", "v0");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform1fv, "void", "Uniform1fv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "float[]", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform1i, "void", "Uniform1i");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "v0");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform1iv, "void", "Uniform1iv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "int[]", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform2f, "void", "Uniform2f");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "float", "v0");
    QUERY->add_arg(QUERY, "float", "v1");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform2fv, "void", "Uniform2fv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "float[]", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform2i, "void", "Uniform2i");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "v0");
    QUERY->add_arg(QUERY, "int", "v1");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform2iv, "void", "Uniform2iv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "int[]", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform3f, "void", "Uniform3f");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "float", "v0");
    QUERY->add_arg(QUERY, "float", "v1");
    QUERY->add_arg(QUERY, "float", "v2");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform3fv, "void", "Uniform3fv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "float[]", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform3i, "void", "Uniform3i");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "v0");
    QUERY->add_arg(QUERY, "int", "v1");
    QUERY->add_arg(QUERY, "int", "v2");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform3iv, "void", "Uniform3iv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "int[]", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform4f, "void", "Uniform4f");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "float", "v0");
    QUERY->add_arg(QUERY, "float", "v1");
    QUERY->add_arg(QUERY, "float", "v2");
    QUERY->add_arg(QUERY, "float", "v3");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform4fv, "void", "Uniform4fv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "float[]", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform4i, "void", "Uniform4i");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "v0");
    QUERY->add_arg(QUERY, "int", "v1");
    QUERY->add_arg(QUERY, "int", "v2");
    QUERY->add_arg(QUERY, "int", "v3");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform4iv, "void", "Uniform4iv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "int[]", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_UniformMatrix2fv, "void", "UniformMatrix2fv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "int", "transpose");
    QUERY->add_arg(QUERY, "float[]", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_UniformMatrix3fv, "void", "UniformMatrix3fv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "int", "transpose");
    QUERY->add_arg(QUERY, "float[]", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_UniformMatrix4fv, "void", "UniformMatrix4fv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "int", "transpose");
    QUERY->add_arg(QUERY, "float[]", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_UseProgram, "void", "UseProgram");
    QUERY->add_arg(QUERY, "int", "program");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_ValidateProgram, "void", "ValidateProgram");
    QUERY->add_arg(QUERY, "int", "program");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib1f, "void", "VertexAttrib1f");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "float", "x");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib1fv, "void", "VertexAttrib1fv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib2f, "void", "VertexAttrib2f");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib2fv, "void", "VertexAttrib2fv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib3f, "void", "VertexAttrib3f");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    QUERY->add_arg(QUERY, "float", "z");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib3fv, "void", "VertexAttrib3fv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib4f, "void", "VertexAttrib4f");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    QUERY->add_arg(QUERY, "float", "z");
    QUERY->add_arg(QUERY, "float", "w");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib4fv, "void", "VertexAttrib4fv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttribPointer, "void", "VertexAttribPointer");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int", "size");
    QUERY->add_arg(QUERY, "int", "type");
    QUERY->add_arg(QUERY, "int", "normalized");
    QUERY->add_arg(QUERY, "int", "stride");
    QUERY->add_arg(QUERY, "Object", "pointer");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Viewport, "void", "Viewport");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "height");


    
    QUERY->end_class(QUERY);
    
    return TRUE;
}

