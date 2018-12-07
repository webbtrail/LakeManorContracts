// =============================================================================================================================================
// <copyright file="AssessmentMain.cpp" company="Lake Manor Consulting">
//    Copyright © 2018-2018 Lake Manor Consulting
//    All Rights Reserved.
// </copyright>
// <summary>
// Solution: Smartmatic Assessment
//  Project: AssessmentMain
//     File: AssessmentMain.cpp
//   Author: Ron W Moore (webbtrail@gmail.com)
//  Created: 2018-12-04, 10:13 AM
//  Purpose: ...
//          3.  The main process must be a command line executable which loads a file as
//              input file(passed as an argument) in which each line of the file will represent an
//              item to process (which is a string composed by numeric characters or blank
//              spaces, e.g: 15423123 931234 1) and an output file in which the results will be
//              printed, as well as a third argument to choose the sorting algorithm. The
//              amount of characters in each item will never exceed 100 chars. The amount of
//              lines in the input file will never exceed 10000 lines.
//
//              1.  E.g.:
//                  ./ProducerConsumer  /path/to/InputFile /path/to/OutputFile algorithmToSort
//
//          4.  For each item, a new WorkerThread must be created which will process the
//              item (to a maximum of 4 worker threads). Inside each thread:
//
//              1.  The thread must split each character of the item into a vector and sort
//                  them (no sort() is allowed, an implementation of two sorting algorithms
//                  must be made manually).
//
//                  The algorithm use for processing is determined by the third
//                  argument when executing the program. This is one of the most
//                  important parts of the exercise. The interviewee must explain (in a
//                  README file, for example) which two algorithms it chose and why
//                  (e.g.: bubble sort, tree sort, merge sort, etc).  If a blank space is found
//                  as part of the item, the thread must wait one second and not include the
//                  blank space in the vector.
//
//              2.  The thread must them print the characters of the vectors separated by
//                  commas into the output file detailed as second argument (each item in a
//                  new line, the file shared by every worker thread of the module).  
//
// </summary>
// =============================================================================================================================================

#include <iostream>

#include "Algorithms/HeapSort.h"
#include "Algorithms/SortAlgorithm.h"
#include "ProcessInputFile.h"


// Local/Static Method prototypes:
static int  CheckApplicationArguments(char *argv[], Algorithms::SortAlgorithm &sortAlgorithm);
static void QuickTest(char *argv[]);
static void Usage(char *argv[]);


/// <summary>Main method.</summary>
/// <param name="argc">The argument count.</param>
/// <param name="argv">The argument vector.</param>
/// <returns>Exit status</returns>
int main(const int argc, char *argv[])
{
    // Do we have a correctly formatted command line?
    if (argc < 3)
    {
        Usage(argv);
        exit(-1);
    }

    Algorithms::SortAlgorithm sortAlgorithm;
    int errorCode = CheckApplicationArguments(argv, sortAlgorithm);
    if (errorCode < 0) {
        exit (errorCode);
    }

    const char *pPathToInputFile  = argv[1];
    const char *pPathToOutputFile = argv[2];

    // Process the input file.
    auto processor = new ProcessInputFile(pPathToInputFile, pPathToOutputFile, sortAlgorithm);
    errorCode      = processor->Process();
    delete processor;
    if (errorCode < 0) {
        exit (errorCode);
    }

    std::cout << "Successfully completed." << std::endl;
    exit(0);
}


/// <summary>Checks the application arguments.</summary>
/// <param name="argv">The argv.</param>
/// <param name="sortAlgorithm">The sort algorithm.</param>
/// <returns>Exit/Error Code if less than 0.</returns>
static int CheckApplicationArguments(char *argv[], Algorithms::SortAlgorithm &sortAlgorithm)
{
    const std::string dash("-");
    if ((dash == argv[1]) && (dash == argv[2]))
    {
        QuickTest(argv);
        return -1;
    }

    const   char *pPathToInputFile  = argv[1];
    //const char *pPathToOutputFile = argv[2];
    const   char *pAlgorithmToSort  = argv[3];

    // Is the input file available/readble?
    if (!FileExists(pPathToInputFile))
    {
        std::cerr << "Error:" << std::endl
                  << "Input file '" << pPathToInputFile << "' is not found or accessible." << std::endl;
        return -2;
    }

    // Do we recognize which sort algorithm is requested?
    sortAlgorithm = Algorithms::ToSortAlgorithm(pAlgorithmToSort);
    if (sortAlgorithm == Algorithms::SortAlgorithm::None)
    {
        std::cerr << "Error:" << std::endl
                  << "Sort Algorithm '" << pAlgorithmToSort << "' is not available." << std::endl;
        return -3;
    }

    return 0;
}


/// <summary>Output the progam usage information to stdout.</summary>
/// <param name="argv">The argument vector.</param>
static void Usage(char *argv[])
{
    // Pick up the whole progam executable path.
    const std::string fullProgamPath = argv[0];

    // Trim off the last token as the application name.
    size_t off = fullProgamPath.rfind('/');
    if (off == std::string::npos) {
        off = fullProgamPath.rfind('\\');
    }

    const std::string programName = (off != std::string::npos) ? fullProgamPath.substr(off + 1) : fullProgamPath;

    std::cout << "Usage:" << std::endl
              << programName << " <pathToInputFile> <pathToOutputFile> <algorithmToSort>" << std::endl
              << "    <algorithmToSort>::= [" << Algorithms::SupportedSortAlgorithms() << "]" << std::endl;
}


/// <summary>Quick test cases.</summary>
/// <param name="argv">The argument vector.</param>
static void QuickTest(char *argv[])
{
    const Algorithms::SortAlgorithm sortAlgorithm = Algorithms::ToSortAlgorithm(argv[3]);

    std::vector<char> itemFilteredVector(10);
    itemFilteredVector[0] = '^';
    itemFilteredVector[1] = 'G';
    itemFilteredVector[2] = ':';
    itemFilteredVector[3] = '\\';
    itemFilteredVector[4] = 'R';
    itemFilteredVector[5] = 'O';
    itemFilteredVector[6] = 'N';
    itemFilteredVector[7] = '\\';
    itemFilteredVector[8] = 'D';
    itemFilteredVector[9] = 'O';

    std::string itemStringSorted;
    switch (sortAlgorithm)
    {
    case Algorithms::SortAlgorithm::HeapSortAlgorithm:
        Algorithms::HeapSort<char>::Sort(itemFilteredVector);
        itemStringSorted = std::string(itemFilteredVector.begin(), itemFilteredVector.end());
        break;

    default: ;
    }

    std::cout << itemStringSorted << std::endl;
}

