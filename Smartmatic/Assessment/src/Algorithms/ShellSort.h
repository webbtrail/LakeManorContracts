// =============================================================================================================================================
// <copyright file="ShellSort.h" company="Lake Manor Consulting">
//    Copyright © 2018-2018 Lake Manor Consulting
//    All Rights Reserved.
// </copyright>
// <summary>
// Solution: AssessmentMain
//  Project: AssessmentMain
//     File: ShellSort.h
//   Author: Ron W Moore (webbtrail@gmail.com)
//  Created: 2018-12-05, 4:16 PM
//  Purpose:
// </summary>
// =============================================================================================================================================

#ifndef _SHELL_SORT_H
#define _SHELL_SORT_H

#include <vector>


namespace Algorithms
{
    /// <summary>The shell sort algorithm.</summary>
    /// <remarks>
    ///     This is actually a variant on straight insertion, but is also quite powerful.
    ///     It can be shown that for an sequence of increments that the number of operations required in
    ///     all is of order N^(3/2) for the worst possible ordering of the original data.  For "randomly"
    ///     ordered data, the operations count goes approximately as N^(1.25), at least for N < 60000.
    ///     For N > 50, however, QuickSort is generally faster (and a significantly larger implementation).
    /// </remarks>
    template <typename T> class ShellSort
    {
    public:

        /// <summary>Sorts the specified data.</summary>
        /// <param name="data">The data.</param>
        /// <remarks>
        ///     Sorts an array into ascending numerical order by Shell's method (diminishing increment sort).
        ///     The array is replaced on output by its sorted rearrangement.  Normally, the argument "m"
        ///     should be set to the size "n" of the data array, but if m &lt; data.size(), then only the first
        ///     "m" elements of the data array are sorted.  This feature is used elsewhere.
        /// </remarks>
        static void Sort(std::vector<T> &data)
        {
            return Sort(static_cast<int>(data.size()), data);
        }


        /// <summary>Sorts the specified member/minus.</summary>
        /// <param name="m">The magnitude.</param>
        /// <param name="data">The data.</param>
        /// <remarks>
        ///     Sorts an array into ascending numerical order by Shell's method (diminishing increment sort).
        ///     The array is replaced on output by its sorted rearrangement.  Normally, the argument "m"
        ///     should be set to the size "n" of the data array, but if m &lt; data.size(), then only the first
        ///     "m" elements of the data array are sorted.  This feature is used elsewhere.
        /// </remarks>
        static void Sort(const int m, std::vector<T> &data)
        {
            // Determine the starting increment.
            int inc = 1;
            do
            {
                inc *= 3;
                ++inc;
            }
            while (inc <= m);

            do
            {
                // Loop over the partial sorts.
                inc /= 3;

                // Outer loop of straight insertion.
                for (auto i = inc; i < m; ++i)
                {
                    T   v = data[i];
                    int j = i;

                    // Inner loop of straight insertion.
                    while (data[j - inc] > v)
                    {
                        data[j] = data[j - inc];
                        j -= inc;
                        if (j < inc) {
                            break;
                        }
                    }

                    data[j] = v;
                }
            }
            while (inc > 1);
        }

    private:
    };
}


#endif  // _SHELL_SORT_H
