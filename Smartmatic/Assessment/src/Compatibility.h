// =============================================================================================================================================
// <copyright file="Compatibility.h" company="Lake Manor Consulting">
//    Copyright © 2018-2018 Lake Manor Consulting
//    All Rights Reserved.
// </copyright>
// <summary>
// Solution: AssessmentMain
//  Project: AssessmentMain
//     File: Compatibility.h
//   Author: Ron W Moore (webbtrail@gmail.com)
//  Created: 2018-12-05, 2:53 PM
//  Purpose: Platform compatibility support
// </summary>
// =============================================================================================================================================

#ifndef _COMPATIBILITY_H
#define _COMPATIBILITY_H

#include <string>

bool FileExists(const std::string &filename);

void MillisecondSleep(int milliseconds);


#endif  // _COMPATIBILITY_H
