// =============================================================================================================================================
// <copyright file="HeapSort.h" company="Lake Manor Consulting">
//    Copyright © 2018-2018 Lake Manor Consulting
//    All Rights Reserved.
// </copyright>
// <summary>
// Solution: AssessmentMain
//  Project: AssessmentMain
//     File: HeapSort.h
//   Author: Ron W Moore (webbtrail@gmail.com)
//  Created: 2018-12-05, 1:37 PM
//  Purpose:
// </summary>
// =============================================================================================================================================

#ifndef _HEAP_SORT_H
#define _HEAP_SORT_H

#include <vector>


namespace Algorithms
{	
    /// <summary>The heap sort.</summary>
    /// <remarks>
    ///     While usually not quite as fast as QuickSort, HeapSort is a very popular sorting routine.
    ///     It is a true "in-place" sort, requiring no auxiallary storage.  It is an N*log2(N) process,
    ///     not only on average, but also for the worst-case order of input data.  Its worst case is
	///     only approximately 20 percent worse than its average running time.
	/// </remarks>
    template <typename T> class HeapSort
    {
    public:

        /// <summary>Sorts the specified data.</summary>
        /// <param name="data">The data.</param>
        /// <remarks>
        ///     Sorts a vector into ascending numerical order using the HeapSort algorithm.
        ///     <paramref name="data" /> is replaced on output by its sorted rearrangement.
        /// </remarks>
        static void Sort(std::vector<T> &data)
        {
            int i;
            const auto n = static_cast<int>(data.size());
            for (i = n / 2 - 1; i >= 0; --i)
            {
                // The index i, which here determines the "left" range of the sift-down, i.e., the element
                // to be sifted down, is decremented from n/2-1 down to 0 during the "hiring" (heap
                // creation) phase.
                SiftDown(data, i, n - 1);
            }

            for (i = n - 1; i > 0; --i)
            {
                // Here the "right" range of the sift-down is decremented from n-2 down to 0 during the
                // "retirement-and-promotion" (heap selection) phase.

                // Clear a space at the end of the array, and retire the top of the heap into it.
                std::swap(data[0], data[i]);
                SiftDown(data, 0, i - 1);
            }
        }

    private:

        /// <summary>
        ///     Carry out the sift-down on element data[l] to maintain the heap structure.
        ///     l and r determine the "left" and "right" range of the sift-down.
        /// </summary>
        /// <param name="data">The data.</param>
        /// <param name="l">The left.</param>
        /// <param name="r">The right.</param>
        static void SiftDown(std::vector<T> &data, int l, int r)
        {
            T   a    = data[l];
            int jOld = l;
            int j    = l + 1;

            while (j <= r)
            {
                // Compare to the better underlining.
                if ((j < r) && (data[j] < data[j + 1])) {
                    ++j;
                }

                // Found "a's" level.  Terminate the sift-down.  Otherwise, denote "a" and contiue.
                if (a >= data[j]) {
                    break;
                }

                data[jOld] = data[j];
                jOld       = j;
                j          = 2*j + 1;
            }

            // Put "a" into it's slot.
            data[jOld] = a;
        }
    };
}

#endif  // _HEAP_SORT_H
