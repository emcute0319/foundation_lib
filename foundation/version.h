/* version.h  -  Foundation library  -  Public Domain  -  2013 Mattias Jansson / Rampant Pixels
 *
 * This library provides a cross-platform foundation library in C11 providing basic support data types and
 * functions to write applications and games in a platform-independent fashion. The latest source code is
 * always available at
 *
 * https://github.com/rampantpixels/foundation_lib
 *
 * This library is put in the public domain; you can redistribute it and/or modify it without any restrictions.
 *
 */

#pragma once

#include <foundation/platform.h>
#include <foundation/types.h>


static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL version_t  version_make( unsigned int major, unsigned int minor, unsigned int revision, unsigned int build, unsigned int control )
{
    version_t v;
    v.sub.major = (uint16_t)major;
    v.sub.minor = (uint16_t)minor;
    v.sub.revision = revision;
    v.sub.build = build;
    v.sub.control = control;
    return v;
}
