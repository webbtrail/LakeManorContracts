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
#include "ItemProducerQueue.h"
#include "ItemConsumer.h"


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

    typedef std::vector<char> item_t;
    typedef void (*consumer_t)(void *state, const item_t &);

private:
    // Inputs
    std::string   _inputFile;
    std::string   _outputFile;
    Algorithms::SortAlgorithm _sortAlgorithm;

    // Working I/O streams.
    std::unique_ptr<std::ifstream> _inputStream;
    std::ofstream                  _outputStream;

    ItemProducerQueue<item_t>            _producerQueue;
    std::vector<ItemConsumer<item_t> *> *_consumers;

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

        _consumers = new std::vector<ItemConsumer<item_t> *>(MAX_CONSUMER_THREADS);
    }


    /// <summary>Finalizes an instance of the <see cref="ProcessInputFile" /> class.</summary>
    /// <remarks>Let the std::unique_ptr destructor automatically clean up for us.</remarks>
    virtual ~ProcessInputFile();

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
    static void Consumer(void *state, const item_t &item);

    /// <summary>Send trace messages to Standard Out.</summary>
    static void ConsoleTrace(const std::string &msg);

    int Initialize();

    std::string ParseAndSortItemString(const std::string &itemString) const;

    static std::string ToItemStringFormatted(const std::string &itemStringSorted);

    std::string ToItemStringSorted(const std::string &itemStringFiltered) const;

    /// <summary>Waits for queue to empty.</summary>
    /// <param name="linesRead">The lines read.</param>
    void WaitForQueueToEmpty(int linesRead);
};

#endif // _PROCESS_INPUT_FILE_H
