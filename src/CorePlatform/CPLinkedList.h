/*
 *  CPLinkedList.h
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

CP_EXTERNC_BEGIN

CP_DECLARE_TYPE(CPLinkedList);

struct CPLinkedList_t {
    CPObject        object;

    size_t          prevPointerOffset, nextPointerOffset;
    
    size_t          count;
    cpptr           head;
    cpptr           tail;
};

CP_API sal_checkReturn sal_out_opt CPLinkedListRef CPLinkedListCreate(const size_t prevPointerOffset, const size_t nextPointerOffset);

CP_API size_t CPLinkedListGetCount(sal_inout CPLinkedListRef list);
CP_API sal_out_opt cpptr CPLinkedListGetHead(sal_inout CPLinkedListRef list);
CP_API sal_out_opt cpptr CPLinkedListGetTail(sal_inout CPLinkedListRef list);

CP_API BOOL CPLinkedListAddItem(sal_inout CPLinkedListRef list, sal_inout cpptr item);

CP_API void CPLinkedListRemoveItem(sal_inout CPLinkedListRef list, sal_inout cpptr item);
CP_API void CPLinkedListRemoveAllItems(sal_inout CPLinkedListRef list);

CPFORCEINLINE sal_out_opt cpptr CPLinkedListPrevItem(sal_inout CPLinkedListRef list, sal_inout cpptr item)
{
    return *((cpptr*)(((byte*)item) + list->prevPointerOffset));
}
CPFORCEINLINE sal_out_opt cpptr CPLinkedListNextItem(sal_inout CPLinkedListRef list, sal_inout cpptr item)
{
    return *((cpptr*)(((byte*)item) + list->nextPointerOffset));
}

CP_EXTERNC_END
