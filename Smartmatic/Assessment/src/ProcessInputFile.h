// =============================================================================================================================================
// <copyright file="ProcessInputFile.h" company="Lake Manor Consulting">
//    Copyright © 2018-2018 Lake Manor Consulting
//    All Rights Reserved.
// </copyright>
// <summary>
// Solution: Smartmatic Assessment
//  Project: AssessmentMain
//     File: ProcessInputFile.h
//   Author: Ron W Moore (webbtrail@gmail.com)
//  Created: 2018-12-04, 12:57 PM
//  Purpose: Process the supplied input file.
// </summary>
// =============================================================================================================================================

#ifndef _PROCESS_INPUT_FILE_H
#define _PROCESS_INPUT_FILE_H

#include <fstream>
#include <string>
#include <thread>

#include "Algorithms/SortAlgorithm.h"
#include "ConcurrentQueue.h"
#include "ItemConsumer.h"
#include "WorkItem.h"

/// <summary>
///     Process the specified input file.
/// </summary>
class ProcessInputFile
{
public:
    static const int MAX_BUF_LENGTH       = 2048;
    static const int MAX_CHARS            = 100;
    static const int MAX_LINES            = 10000;
    static const int MAX_CONSUMER_THREADS = 4;

    using item_t     = std::vector<char>;
    using consumer_t = void (*)(WorkItem&&);

private:
    // Inputs
    std::string   _inputFile;
    std::string   _outputFile;
    Algorithms::SortAlgorithm _sortAlgorithm;

    // Working I/O streams.
    std::unique_ptr<std::ifstream> _inputStream;
    std::ofstream                  _outputStream;

    ConcurrentQueue<WorkItem>            _producerQueue;
    std::vector<ItemConsumer<WorkItem> *> *_consumers;

    //static std::mutex _outputStreamMutex;

#ifdef _DEBUG
    static std::mutex _consoleMutex;
#endif

public:
    /// <param name="inputFile">The input file.</param>
    /// <param name="outputFile">The output file.</param>
    /// <param name="sortAlgorithm">The sort algorithm.</param>
    ProcessInputFile(const std::string &inputFile, const std::string &outputFile, const Algorithms::SortAlgorithm sortAlgorithm)
    {
        _inputFile     = inputFile;
        _outputFile    = outputFile;
        _sortAlgorithm = sortAlgorithm;

        _consumers = new std::vector<ItemConsumer<WorkItem> *>(MAX_CONSUMER_THREADS);
    }


    /// <summary>Finalizes an instance of the <see cref="ProcessInputFile" /> class.</summary>
    /// <remarks>Let the std::unique_ptr destructor automatically clean up for us.</remarks>
    virtual ~ProcessInputFile();

    /// <summary>Processes this instance.</summary>
    /// <returns>Error Code if less than 0.</returns>
    int Process();


    /// Block the copy constructor.
    ProcessInputFile(ProcessInputFile &) = delete;

    /// Block the move constructor.
    ProcessInputFile(ProcessInputFile &&) = delete;

    /// Block the copy assignment operator.
    ProcessInputFile operator =(ProcessInputFile &) = delete;

    /// Block the move assignment operator.
    ProcessInputFile operator =(ProcessInputFile &&) = delete;

private:
    /// <summary>Send trace messages to Standard Out.</summary>
    static void ConsoleTrace(const std::string &msg);

    /// <summary>Consume an item in the producer queue.</summary>
    static void Consumer(WorkItem && workItem);

    /// <summary>Get the next item string (raw) from the input stream.</summary>
    /// <param name="edittedString">The editted string.</param>
    /// <returns><see langword="true"/> if successful, <see langword="false"/> otherwise.</returns>
    bool GetItemString(std::string &edittedString) const;

    /// <summary>Initializes this instance.</summary>
    /// <returns>If less than zero, any associated error code.</returns>
    int Initialize();

    std::string ParseAndSortItemString(const std::string &itemString) const;

    std::string ToItemFormattedString(const std::string &itemStringSorted) const;

    std::string ToItemSortedString(const std::string &itemStringFiltered) const;

    /// <summary>Waits for queue to empty.</summary>
    /// <param name="linesRead">The lines read.</param>
    void WaitForQueueToEmpty(int linesRead);
};

#endif // _PROCESS_INPUT_FILE_H
