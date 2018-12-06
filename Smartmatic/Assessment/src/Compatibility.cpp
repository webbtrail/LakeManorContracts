// =============================================================================================================================================
// <copyright file="Compatibility.cpp" company="Lake Manor Consulting">
//    Copyright © 2018-2018 Lake Manor Consulting
//    All Rights Reserved.
// </copyright>
// <summary>
// Solution: AssessmentMain
//  Project: AssessmentMain
//     File: Compatibility.cpp
//   Author: Ron W Moore (webbtrail@gmail.com)
//  Created: 2018-12-05, 2:53 PM
//  Purpose: Platform compatibility support
// </summary>
// =============================================================================================================================================

#ifdef _MSC_VER
#  include <windows.h>
#  include <synchapi.h>
#else
#  include <unistd.h>
#endif

#include "Compatibility.h"


void MillisecondSleep(int milliseconds)
{
#ifdef _MSC_VER
    Sleep(milliseconds);
#else
    usleep(milliseconds);
#endif
}
