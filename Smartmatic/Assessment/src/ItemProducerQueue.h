// =============================================================================================================================================
// <copyright file="ItemProducerQueue.h" company="Lake Manor Consulting">
//    Copyright © 2018-2018 Lake Manor Consulting
//    All Rights Reserved.
// </copyright>
// <summary>
// Solution: AssessmentMain
//  Project: AssessmentMain
//     File: ItemProducerQueue.h
//   Author: Ron W Moore (webbtrail@gmail.com)
//  Created: 2018-12-04, 3:28 PM
//   Purpose: The Producer portion of the requisite asynchronous Producer / Consumer design pattern.
// Reference: https://codereview.stackexchange.com/questions/177650/a-simple-implementation-of-the-producer-consumer-pattern
// </summary>
// =============================================================================================================================================

#ifndef _ITEM_PRODCER_QUEUE_H
#define _ITEM_PRODCER_QUEUE_H

#include <mutex>
#include <queue>


/// <summary> The Producer portion of the requisite asynchronous Producer / Consumer design pattern. </summary>
/// <remarks>
///     <code> https://codereview.stackexchange.com/questions/177650/a-simple-implementation-of-the-producer-consumer-pattern </code>
/// </remarks>
template<typename TItem> class ItemProducerQueue
{
private:

    std::mutex        _mutex;
    std::queue<TItem> _queue;

public:

    /// <summary>Initializes a new instance of the <see cref="ItemProducerQueue"/> class.</summary>
    ItemProducerQueue()
        : _queue()
    { }


    // Prevent optimization from removing the queue management mutex.
#ifndef _MSC_VER
#pragma GCC push_options
#pragma GCC optimize ("O0")
#pragma OPTIMIZE OFF
#endif


    /// <summary>Determines whether this queue is empty.</summary>
    /// <returns> true or false as appropriate.</returns>
    bool IsEmpty()
#ifndef _MSC_VER
        __attribute__((optimize("-O0")))
#endif
    {
        // Lock will be released as soon as it goes out of scope.
        std::unique_lock<std::mutex> lock(_mutex);

        return _queue.empty();
    }


    /// <summary>Tries to pop an item from the producer queue.</summary>
    /// <param name="item">The item.</param>
    /// <returns>true / false - depending upon success.</returns>
    bool TryPop(TItem & item)
#ifndef _MSC_VER
        __attribute__((optimize("-O0")))
#endif
    {
        {            
            // Lock will be released as soon as it goes out of scope.
            std::unique_lock<std::mutex> lock(_mutex);

            if (_queue.empty()) {
                return false;
            }

            item = _queue.front();
            _queue.pop();
        }

        return true;
    }


    /// <summary>Pushes the specified item into the producer queue.</summary>
    /// <param name="item">The item.</param>
    void Push(TItem && item)
#ifndef _MSC_VER
        __attribute__((optimize("-O0")))
#endif
    {
        // Lock will be released as soon as it goes out of scope.
        std::unique_lock<std::mutex> lock(_mutex);

        _queue.push(std::move(item));
    }


#ifndef _MSC_VER
#pragma OPTIMIZE ON
#pragma GCC pop_options
#endif
};


#endif // _ITEM_PRODCER_QUEUE_H
