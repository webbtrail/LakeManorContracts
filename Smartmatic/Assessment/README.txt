All issues in requirements document should have been addressed.
Assumptions are documented in the source code, and I will attempt to document them here as well.
Code works with MS Visual Studio 2017 and CygWin.  I don't have a ready version of Linux to test against.

No warnings during compilation.
no use of external libraries (severely limited)
Cyclomatic complexity is never an issue.
Full use of the Producer/Consumer design pattern

Using two sort algorithms:
HeapSort and ShellSort.
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
