// =============================================================================================================================================
// <copyright file="ItemConsumer.h" company="Lake Manor Consulting">
//    Copyright © 2018-2018 Lake Manor Consulting
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
#include "ItemProducerQueue.h"


/// <summary> The Consumer portion of the requisite asynchronous Producer / Consumer design pattern. </summary>
/// <remarks>
///     <code> https://codereview.stackexchange.com/questions/177650/a-simple-implementation-of-the-producer-consumer-pattern </code>
/// </remarks>
template<typename TItem> class ItemConsumer
{
private:

    typedef TItem item_t;
    typedef void (*consumer_t)(void *, const item_t &);

    std::atomic<bool>          _isRunning = ATOMIC_VAR_INIT(true);
    consumer_t                 _consumer;
    void                      *_state;
    ItemProducerQueue<item_t> &_queue;

    std::thread _thread;  // Has to be initialized last.


public:

    /// <summary>Initializes a new instance of the <see cref="ItemConsumer"/> class.</summary>
    /// <param name="queue">The queue.</param>
    /// <param name="consumer">The consumer.</param>
    /// <param name="state">The state.</param>
    ItemConsumer(ItemProducerQueue<item_t> &queue, consumer_t consumer, void *state)
        : _consumer(consumer),
          _state(state),
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
        TItem item;
        while (_isRunning)
        {
            while (_isRunning && !_queue.TryPop(item))
            {
                /* do nothing */
                MillisecondSleep(1);
            }

            if (!_isRunning) {
                return;
            }

            _consumer(_state, item);
        }
    }


    /// <summary>Finalizes an instance of the <see cref="ItemConsumer{TItem}"/> class.</summary>
    ~ItemConsumer()
    {
        _isRunning = false;
        _thread.join();
    }

};

#endif //_ITEM_CONSUMER_H
