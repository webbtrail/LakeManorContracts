// =============================================================================================================================================
// <copyright file="WorkItem.h" company="Lake Manor Consulting">
//    Copyright © 2018-2018 Lake Manor Consulting
//    All Rights Reserved.
// </copyright>
// <summary>
// Solution: AssessmentMain
//  Project: AssessmentMain
//     File: WorkItem.h
//   Author: Ron W Moore (webbtrail@gmail.com)
//  Created: 2018-12-06, 10:32 AM
//  Purpose: The definition of a work item, the base unit of work in the project.
// </summary>
// =============================================================================================================================================

#ifndef _WORK_ITEM_H
#define _WORK_ITEM_H

#include <memory>
#include <utility>
#include <vector>

// Type prototypes:
class ProcessInputFile;


class WorkItem
{
public:

    typedef void (*consumer_t)(const WorkItem &);
    typedef std::vector<char> item_t;

private:

    static int _serialNumberGenerator;

    const int               _serialNumber;
    int                     _inputID;
    ProcessInputFile       *_producer;
    consumer_t              _consumer;
    std::shared_ptr<item_t> _itemData;

public:

    /// <summary>Initializes a new instance of the <see cref="WorkItem"/> class.</summary>
    WorkItem()
      : _serialNumber(++_serialNumberGenerator),
        _inputID(-1),
        _producer(nullptr),
        _consumer(nullptr)
    { }


    /// <summary>Initializes a new instance of the <see cref="WorkItem" /> class.</summary>
    /// <param name="inputID">The input identifier.</param>
    /// <param name="producer">The producer.</param>
    /// <param name="consumer">The consumer.</param>
    /// <param name="itemData">The item.</param>
    WorkItem(int inputID, ProcessInputFile* producer, consumer_t consumer, std::shared_ptr<item_t> itemData)
        : _serialNumber(++_serialNumberGenerator),
          _inputID(inputID),
          _producer(producer),
          _consumer(consumer),
          _itemData(std::move(itemData))
    { }


    /// <summary>Initializes a new instance of the <see cref="WorkItem"/> class.</summary>
    /// <param name="other">The other.</param>
    WorkItem(const WorkItem &other)
        : _serialNumber(++_serialNumberGenerator),
          _inputID(other._inputID),
          _producer(other._producer),
          _consumer(other._consumer),
          _itemData(other._itemData)
    { }

    /// <summary>Initializes a new instance of the <see cref="WorkItem"/> class.</summary>
    /// <param name="other">The other.</param>
    WorkItem(WorkItem && other) noexcept
        : _serialNumber(++_serialNumberGenerator),
          _inputID(other._inputID),
          _producer(nullptr),
          _consumer(other._consumer),
          _itemData(std::move(other._itemData))
    {
        _producer = other._producer;
    }


    /// <summary>Operator=s the specified other.</summary>
    /// <param name="other">The other.</param>
    /// <returns></returns>
    WorkItem &operator =(const WorkItem &other)
    {
        if (this == &other) {
            return *this;
        }

        _inputID  = other._inputID;
        _producer = other._producer;
        _consumer = other._consumer;
        _itemData = other._itemData;
        return *this;
    }

    /// <summary>Operator=s the specified other.</summary>
    /// <param name="other">The other.</param>
    /// <returns></returns>
    WorkItem &operator =(WorkItem && other) noexcept
    {
        if (this == &other) {
            return *this;
        }

        _inputID  = other._inputID;
        _producer = other._producer;
        _consumer = other._consumer;
        _itemData = std::move(other._itemData);
        return *this;
    }
    
    /// <summary>Finalizes an instance of the <see cref="WorkItem"/> class.</summary>
    ~WorkItem() = default;


    /// <summary>Return the input identifier.</summary>
    int InputID() const { return _inputID; }

    /// <summary>The producer associated with this instance.</summary>
    ProcessInputFile *Producer() const { return _producer; }

    /// <summary>Consumes this instance.</summary>
    consumer_t Consumer() const { return _consumer; }


    /// <summary>Returns the item data associated with this instance.</summary>
    /// <returns>Read-only instance yields read-only item.</returns>
    const item_t &Item() const { return *_itemData; }

    /// <summary>Returns the item data associated with this instance.</summary>
    /// <returns>Writable instance yields writable item.</returns>
    std::shared_ptr<item_t> Item() { return _itemData; }
};

#endif  // _WORK_ITEM_H
