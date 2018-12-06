// =============================================================================================================================================
// <copyright file="SortAlgorithm.cpp" company="Lake Manor Consulting">
//    Copyright © 2018-2018 Lake Manor Consulting
//    All Rights Reserved.
// </copyright>
// <summary>
// Solution: Smartmatic Assessment
//  Project: AssessmentMain
//     File: SortAlgorithm.cpp
//   Author: Ron W Moore (webbtrail@gmail.com)
//  Created: 2018-12-04, 11:33 AM
//  Purpose: Identified/supported Sort Algorithms.
// </summary>
// =============================================================================================================================================

#include "SortAlgorithm.h"


namespace Algorithms
{
	/// <summary>Translate the string to a supported sort algorithm</summary>
	/// <param name="algorithmName">The algorithm to use.</param>
	/// <returns>a supported sort algorithm</returns>
	SortAlgorithm ToSortAlgorithm(const std::string &algorithmName)
	{
		if (algorithmName == "HeapSort") {
			return HeapSortAlgorithm;
		}

		if (algorithmName == "ShellSort") {
			return ShellSortAlgorithm;
		}

		return None;
	}
}
