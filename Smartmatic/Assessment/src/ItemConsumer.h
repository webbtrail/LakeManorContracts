// =============================================================================================================================================
// <copyright file="ItemConsumer.h" company="Lake Manor Consulting">
//    Copyright � 2018-2018 Lake Manor Consulting
//    All Rights Reserved.
// </copyright>
// <summary>
//  Solution: Smartmatic Assessment
//   Project: AssessmentMain
//      File: ItemConsumer.h
//    Author: Ron W Moore (webbtrail@gmail.com)
//   Created: 2018-12-04, 2:56 PM
//   Purpose: The Consumer portion of the requisite asynchronous Producer / Consumer design pattern.
// Reference: https://codereview.stackexchange.com/questions/177650/a-simple-implementation-of-the-producer-consumer-pattern
// </summary>
// =============================================================================================================================================

#ifndef _ITEM_CONSUMER_H
#define _ITEM_CONSUMER_H

#include <atomic>
#include <thread>

#include "Compatibility.h"
#include "ConcurrentQueue.h"
#include "WorkItem.h"


/// <summary> The Consumer portion of the requisite asynchronous Producer / Consumer design pattern. </summary>
/// <remarks>
///     <code> https://codereview.stackexchange.com/questions/177650/a-simple-implementation-of-the-producer-consumer-pattern </code>
/// </remarks>
template<typename TWorkItem> class ItemConsumer
{
private:
    using consumer_t = void (*)(WorkItem&&);
    using item_t     = TWorkItem;

    std::atomic<bool>        _isRunning = ATOMIC_VAR_INIT(true);
    consumer_t               _consumer;
    ConcurrentQueue<item_t> &_queue;

    std::thread _thread;  // Has to be initialized last.


public:

    /// <summary>Initializes a new instance of the <see cref="ItemConsumer"/> class.</summary>
    /// <param name="queue">The queue.</param>
    /// <param name="consumer">The consumer.</param>
    ItemConsumer(ConcurrentQueue<item_t> &queue, consumer_t consumer)
        : _consumer(consumer),
          _queue(queue),
          _thread([&]()
          {
              Run();
          })
    { }


    /// <summary>Is this Consumer currently runnig?</summary>
    /// <returns> true or false as appropriate.</returns>
    bool IsRunning() const { return _isRunning; }


    /// <summary>Runs the specified consumer.</summary>
    void Run()
    {
        while (_isRunning)
        {
            TWorkItem item;
            while (_isRunning && !_queue.TryPop(item))
            {
                // Do nothing
                MillisecondSleep(100);
            }

            if (!_isRunning) {
                return;
            }

            _consumer(std::move(item));

            // This should NOT be necessary, because the move operation in the previous line should have
            // taken care to clear the data.  Some C++ implementations still require this explicit data void.
            item.ClearItemData();  // NOLINT(bugprone-use-after-move)
        }
    }


    /// <summary>Finalizes an instance of the <see cref="ItemConsumer{TWorkItem}"/> class.</summary>
    ~ItemConsumer()
    {
        _isRunning = false;
        _thread.join();
    }


    /// Block the copy constructor.
    ItemConsumer(ItemConsumer &) = delete;

    /// Block the move constructor.
    ItemConsumer(ItemConsumer &&) = delete;

    /// Block the copy assignment operator.
    ItemConsumer operator =(ItemConsumer &) = delete;

    /// Block the move assignment operator.
    ItemConsumer operator =(ItemConsumer &&) = delete;
};

#endif //_ITEM_CONSUMER_H
