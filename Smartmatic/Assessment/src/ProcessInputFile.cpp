// =============================================================================================================================================
// <copyright file="ProcessInputFile.h" company="Lake Manor Consulting">
//    Copyright � 2018-2018 Lake Manor Consulting
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

#include "ProcessInputFile.h"

#include <iostream>
#include <sstream>
#include <vector>

#include "Compatibility.h"
#include "Algorithms/HeapSort.h"
#include "Algorithms/ShellSort.h"
//std::mutex ProcessInputFile::_outputStreamMutex;

#ifdef _DEBUG
std::mutex ProcessInputFile::_consoleMutex;
#endif


/// <summary>Finalizes an instance of the <see cref="ProcessInputFile"/> class.</summary>
ProcessInputFile::~ProcessInputFile()
{
    if (nullptr != _consumers)
    {            
        for (auto &consumer : *_consumers)
        {
            delete consumer;
            //consumer = nullptr;
        }
    
        //delete[] _consumers;
        //_consumers = nullptr;
    }

    _outputStream.close();
}


/// <summary>Processes this instance.</summary>
/// <returns>Error Code if less than 0.</returns>
int ProcessInputFile::Process()
{
    const int errorCode = Initialize();
    if (errorCode < 0) {
        return errorCode;
    }

    // Loop through the lines of the file, stopping when we run out of data or hit the configured hard limit.
    // We need to expose the number of lines read.
    int linesRead = 0;
    for (; linesRead < MAX_LINES; ++linesRead)
    {
        char itemsMaxBuf[MAX_BUF_LENGTH];
        _inputStream->getline(itemsMaxBuf, MAX_BUF_LENGTH);
        if (_inputStream->bad())
        {
            // Break out of input loop on error or end-of-file.
            break;
        }

        std::string            itemString    = std::string(itemsMaxBuf);
        std::string::size_type indexPastData = itemString.find('\n');
        if (indexPastData == std::string::npos) {
            indexPastData = itemString.find('\0');
        }

        // If indexPastData is 0, then there is no data, and the length is indeed 0.
        const size_t length = std::min<size_t>(((indexPastData != std::string::npos) ? indexPastData : MAX_CHARS), MAX_CHARS);
        std::string edittedString = itemString.substr(0, length);

        // Reference: https://stackoverflow.com/questions/8777603/what-is-the-simplest-way-to-convert-array-to-vector
        _producerQueue.Push(item_t(edittedString.begin(), edittedString.end()));
    }

    WaitForQueueToEmpty(linesRead);
    return 0;
}


/// <summary>Initializes this instance.</summary>
/// <returns></returns>
int ProcessInputFile::Initialize()
{
    _inputStream = std::make_unique<std::ifstream>();
    _inputStream->open(_inputFile);
    if (_inputStream->bad())
    {
        std::cerr << "Error opening input file '" << _inputFile << "'." << std::endl;
        return -11;
    }

    //_outputStream = std::ofstream(_outputFile);
    _outputStream.open(_outputFile);
    if (_outputStream.bad())
    {
        std::cerr << "Error opening output file '" << _outputFile << "'." << std::endl;
        return -12;
    }

    // _outputStream is not making it through the lambda capture
    // Sometimes the less layered logic is easier to debug.
    // We are completely avoiding captures and closures within this class by using this older state tracking methodology.

    for (auto i = 0; i < MAX_CONSUMER_THREADS; ++i) {
        _consumers->at(i) = new ItemConsumer<item_t>(_producerQueue, &ProcessInputFile::Consumer, this);        
    }

    return 0;
}


/// <summary>Consumes the item.</summary>
void ProcessInputFile::Consumer(void *state, const item_t &item)
{
    // Sometimes the less layered logic is easier to debug.
    // We are completely avoiding captures and closures within this class by using this older state tracking methodology.
    auto pThis = static_cast<ProcessInputFile *>(state);

    const auto length = item.size();
    if (length == 0) {
        return;
    }

    const std::string itemStringOriginal(item.begin(), item.end());

    const auto itemStringSorted = pThis->ParseAndSortItemString(itemStringOriginal);

    const auto itemStringFormatted = ToItemStringFormatted(itemStringSorted);

    // Where are we routinely getting an uninitialized member error hear?
    // Everything seems to work fine when the output is not attempted to be outputted.
    // Each stream operator is supposed to be thread safe.
    // The _outputStream member value is not making it here.
    pThis->_outputStream << itemStringFormatted;
}


/// <summary>Send trace messages to Standard Out.</summary>
void ProcessInputFile::ConsoleTrace(const std::string &msg)
{
#ifdef _DEBUG
    {
        // Lock will be released as soon as it goes out of scope.
        std::unique_lock<std::mutex> consoleLock(_consoleMutex);

        std::cout << "ProcessInputFile::ConsoleTrace([" << msg.size() << "]'" << msg << "')." << std::endl;
    }
#endif
}


/// <summary>Parses and Sorts the item string.</summary>
/// <param name="itemString">The item string.</param>
/// <returns></returns>
std::string ProcessInputFile::ParseAndSortItemString(const std::string &itemString) const
{
    // Handle waiting for and skipping spaces.
    std::ostringstream stringStream;
    for (auto c : itemString)
    {
        // Sleeping one second and skipping embedded spaces.
        // Requirements document didn't specify whether it was one second per space,
        // or once for the case where a space was detected.
        if (isspace(c)) {
            MillisecondSleep(1000);
        }
        else {
            stringStream << c;
        }
    }

    const std::string itemFilteredString = stringStream.str();

    // Now we need to sort this item vector.
    const std::string itemSortedString = ToItemStringSorted(itemFilteredString);
    return itemSortedString;
}


/// <summary>To the item string formatted.</summary>
/// <param name="itemStringSorted">The item string sorted.</param>
/// <returns></returns>
std::string ProcessInputFile::ToItemStringFormatted(const std::string &itemStringSorted)
{
    bool first = true;
    std::ostringstream itemStringStreamFormatted;
    for (auto c : itemStringSorted)
    {
        if (first) {
            first = false;
        }
        else {
            itemStringStreamFormatted << ',';
        }

        itemStringStreamFormatted << c;
    }

    itemStringStreamFormatted << std::endl;
    return itemStringStreamFormatted.str();
}


/// <summary>To the item string sorted.</summary>
/// <param name="itemStringFiltered">The item string filtered.</param>
/// <returns></returns>
std::string ProcessInputFile::ToItemStringSorted(const std::string &itemStringFiltered) const
{
#ifdef _DEBUG
    ConsoleTrace("itemStringFiltered=" + itemStringFiltered);
#endif

    std::vector<char> itemFilteredVector(itemStringFiltered.begin(), itemStringFiltered.end());

    std::string itemStringSorted;
    switch (_sortAlgorithm)
    {
    case Algorithms::SortAlgorithm::HeapSortAlgorithm:
        Algorithms::HeapSort<char>::Sort(itemFilteredVector);
        itemStringSorted = std::string(itemFilteredVector.begin(), itemFilteredVector.end());
        break;

    case Algorithms::SortAlgorithm::ShellSortAlgorithm:
        Algorithms::ShellSort<char>::Sort(itemFilteredVector);
        itemStringSorted = std::string(itemFilteredVector.begin(), itemFilteredVector.end());
        break;

    default: ;
    }

#ifdef _DEBUG
    ConsoleTrace("itemStringSorted=" + itemStringSorted);
#endif
    return itemStringSorted;
}


/// <summary>Waits for queue to empty.</summary>
/// <param name="linesRead">The lines read.</param>
void ProcessInputFile::WaitForQueueToEmpty(const int linesRead) const
{
    // Assume a maximum of 8 spaces per line that are waited for.
    // Above this number, that line is pretty garbled anyway.
    const int maximumSecondsToWaitForQueueToEmpty = linesRead * 8;

    // Wait some time for the queue to finish emptying.
    const clock_t start = clock();
    while (!_producerQueue.IsEmpty())
    {
        const clock_t now = clock();
        const float durationInSeconds = static_cast<float>(now - start) / CLOCKS_PER_SEC;
        if (durationInSeconds)
        {
            if (durationInSeconds > maximumSecondsToWaitForQueueToEmpty) {
                break;
            }
        }

        // Wait for the queue to process
        MillisecondSleep(100);
    }
}
