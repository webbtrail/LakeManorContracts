// =============================================================================================================================================
// <copyright file="SortAlgorithm.h" company="Lake Manor Consulting">
//    Copyright © 2018-2018 Lake Manor Consulting
//    All Rights Reserved.
// </copyright>
// <summary>
// Solution: Smartmatic Assessment
//  Project: AssessmentMain
//     File: SortAlgorithm.h
//   Author: Ron W Moore (webbtrail@gmail.com)
//  Created: 2018-12-04, 11:23 AM
//  Purpose: Identified/supported Sort Algorithms.
// </summary>
// =============================================================================================================================================

#ifndef _SORT_ALGORITHM_H
#define _SORT_ALGORITHM_H

#include <string>

namespace Algorithms
{   
    /// <summary>Enumeration of identified/supported Sort Algorithms.</summary>
    enum SortAlgorithm
    {
        None = 0,
        
        /// <summary>The heap sort algorithm.</summary>
        /// <remarks>
        ///     While usually not quite as fast as QuickSort, HeapSort is a very popular sorting routine.
        ///     It is a true "in-place" sort, requiring no auxiallary storage.  It is an N*log2(N) process,
        ///     not only on average, but also for the worst-case order of input data.  Its worst case is
        ///     only approximately 20 percent worse than its average running time.
        /// </remarks>
        HeapSortAlgorithm,

        /// <summary>The shell sort algorithm.</summary>
        /// <remarks>
        ///     This is actually a variant on straight insertion, but is also quite powerful.
        ///     It can be shown that for an sequence of increments that the number of operations required in
        ///     all is of order N^(3/2) for the worst possible ordering of the original data.  For "randomly"
        ///     ordered data, the operations count goes approximately as N^(1.25), at least for N < 60000.
        ///     For N > 50, however, QuickSort is generally faster (and a significantly larger implementation).
        /// </remarks>
        ShellSortAlgorithm
    };


    /// <summary>Returns the supported sort algorithms.</summary>
    /// <returns></returns>
    inline std::string SupportedSortAlgorithms()
    {
        return "HeapSort | ShellSort";
    }


    /// <summary>Translate the string to a supported sort algorithm</summary>
    /// <param name="algorithmName">The algorithm to use.</param>
    /// <returns>a supported sort algorithm</returns>
    SortAlgorithm ToSortAlgorithm(const std::string &algorithmName);
}

#endif // _SORT_ALGORITHM_H
