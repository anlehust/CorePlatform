/*
 *  CPURL.h
 *  CorePlatform
 *
 *  Created by Ben Vanik on 1/18/11.
 *  Copyright 2011 Ben Vanik. All rights reserved.
 *
 */

#pragma once

#include <CorePlatform/CPPlatform.h>
#include <CorePlatform/CPConfig.h>
#include <CorePlatform/CPTypes.h>
#include <CorePlatform/CPAnnotations.h>
#include <CorePlatform/CPCodeUtilities.h>
#include <CorePlatform/CPMath.h>
#include <CorePlatform/CPAtomic.h>
#include <CorePlatform/CPMemory.h>
#include <CorePlatform/CPDebugging.h>
#include <CorePlatform/CPObject.h>
#include <CorePlatform/CPString.h>

CP_EXTERNC_BEGIN

// CPURL is immutable so it is allocated as the CPURL object + the character array value
// CPURLs that are relative will retain their baseURL - this means that repetitive URLs should be created relative to conserve memory
// Design taken largely from CFURL: http://developer.apple.com/library/mac/#documentation/CoreFoundation/Reference/CFURLRef/Reference/reference.html

#define CPURLInvalidIndex ((size_t)-1)

#define CPMAXURL    2048

typedef enum CPURLEscapeOptions_e {
    CPURLEscapeOptionsPath          = 1,
} CPURLEscapeOptions;

CP_DECLARE_TYPE(CPURL);

struct CPURL_t {
    CPObject        object;

    size_t          absoluteLength;
    CPURLRef        baseURL;

    size_t          length;

#pragma warning(push)
#pragma warning(disable : 4200)
    sal_field_ecount_full(length + 1) CPChar value[0];
#pragma warning(pop)
};

CP_API sal_checkReturn sal_out_opt CPURLRef CPURLCreate(sal_inout_opt CPURLRef baseURL, sal_in_z const CPChar* source);
CP_API sal_checkReturn sal_out_opt CPURLRef CPURLCreateWithString(sal_inout_opt CPURLRef baseURL, sal_inout CPStringRef source);
CP_API sal_checkReturn sal_out_opt CPURLRef CPURLCreateAbsoluteCopy(sal_inout CPURLRef source);

CP_API sal_out_opt CPStringRef CPURLCopyAbsoluteString(sal_inout CPURLRef url);
CP_API sal_checkReturn BOOL CPURLGetAbsoluteString(sal_inout CPURLRef url, sal_out_bcount_opt(bufferSize) CPChar* buffer, const size_t bufferSize);

// TODO: queries:
CP_API size_t CPURLGetScheme(sal_inout CPURLRef url, sal_out_bcount_opt(bufferSize) CPChar* buffer, const size_t bufferSize);
CP_API sal_out_opt CPStringRef CPURLCopyScheme(sal_inout CPURLRef url);
// CPURLGetHostName
// CPURLGetPortNumber
// CPURLGetNetLocation
// CPURLGetPath
CP_API size_t CPURLGetLastPathComponent(sal_inout CPURLRef url, sal_out_bcount_opt(bufferSize) CPChar* buffer, const size_t bufferSize);
CP_API sal_out_opt CPStringRef CPURLCopyLastPathComponent(sal_inout CPURLRef url);
CP_API size_t CPURLGetPathExtension(sal_inout CPURLRef url, sal_out_bcount_opt(bufferSize) CPChar* buffer, const size_t bufferSize);
CP_API sal_out_opt CPStringRef CPURLCopyPathExtension(sal_inout CPURLRef url);
// CPURLGetQueryString
// CPURLGetFragment

CP_API BOOL CPURLIsHTTP(sal_inout CPURLRef url);
CP_API BOOL CPURLIsHTTPS(sal_inout CPURLRef url);
CP_API BOOL CPURLIsFile(sal_inout CPURLRef url);

CP_API sal_checkReturn size_t CPURLEscape(sal_in_z const CPChar* source, sal_out_bcount(bufferSize) CPChar* buffer, const size_t bufferSize, const uint32 escapeOptions);
CP_API sal_checkReturn size_t CPURLUnescape(sal_in_z const CPChar* source, sal_out_bcount(bufferSize) CPChar* buffer, const size_t bufferSize);
CP_API sal_out_opt CPStringRef CPURLUnescapeString(sal_inout CPStringRef source);

CP_API void CPURLNormalizeSlashes(sal_in_z CPChar* url, const CPChar slashChar);

CP_EXTERNC_END
