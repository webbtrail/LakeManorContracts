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

// ReSharper disable CppUnusedIncludeDirective

#ifdef _MSC_VER
#  include <windows.h>  // NOLINT(llvm-include-order)
#  include <synchapi.h>
#  include <corecrt_io.h>
#else
#  include <io.h>
#  include <unistd.h>
#endif

// ReSharper restore CppUnusedIncludeDirective

#include "Compatibility.h"


bool FileExists(const std::string &filename)
{
#ifdef _MSC_VER
    return _access(filename.c_str(), 0) != -1;
#else
    return access(filename.c_str(), 0) != -1;
#endif
}


/// <summary>Milliseconds sleep.</summary>
/// <param name="milliseconds">The milliseconds.</param>
void MillisecondSleep(int milliseconds)
{
#ifdef _MSC_VER
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}
