// =============================================================================================================================================
// <copyright file="WorkItem.cpp" company="Lake Manor Consulting">
//    Copyright © 2018-2018 Lake Manor Consulting
//    All Rights Reserved.
// </copyright>
// <summary>
// Solution: AssessmentMain
//  Project: AssessmentMain
//     File: WorkItem.cpp
//   Author: Ron W Moore (webbtrail@gmail.com)
//  Created: 2018-12-06, 12:02 PM
//  Purpose: Declare static data members of class WorkItem
// </summary>
// =============================================================================================================================================

#include "WorkItem.h"

//#include "ProcessInputFile.h"


int WorkItem::_serialNumberGenerator = 0;

WorkItem * WorkItem::_empty = nullptr;

/// <summary>A default empty instance.</summary>
const WorkItem &WorkItem::Empty()
{
    if (nullptr == _empty) {
        _empty = new WorkItem();
    }

    return *_empty;
}

