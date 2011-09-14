/**
 * \file PriorityQueue.h, Contains a bi-directional priority queue implemented
 * using a radix sort. 
 *
 * Copyright (C) 20011 Thomas P. Lahoda
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#ifndef DATA_PRIORITYQUEUE_H
#define DATA_PRIORITYQUEUE_H

#include <string>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include <stdexcept>
#include <iostream>

namespace data {
  using namespace std;

  /**
   * \struct PriorityQueue
   * Implements a bi-directional priority queue in terms of a radix sort.
   *
   * \tparam T The type of the elements held by the PriorityQueue.
   * \tparam DIRECTION Whether or not lower or higher values are the higher priorities.
   */
  template<typename T, typename DIRECTION>
  struct PriorityQueue {
    /**
     * \typedef map<string, list<T> > BUCKET
     * The bucket type.
     */
    typedef map<string, list<T>> BUCKET;

    /**
     * \typedef vector<unsigned int, BUCKET> BUCKETS
     * The type of the buckets container.
     */
    typedef vector<BUCKET> BUCKETS;

    /**
     * Constructs a PriorityQueue.
     *
     * \param maxKeyLength The maximum number of digits a key will have.
     */
    PriorityQueue (unsigned int maxKeyLength) 
      : buckets_ (maxKeyLength), size_ (0), curPriorityBucket_ (), curHighest_ () {};

    /**
     * Destroys a PriorityQueue. Complexity is O(n) where n is the number of elements
     * in the queue at the time of destruction.
     */
    ~PriorityQueue () {};

    /**
     * Pushes an element onto the PriorityQueue. push has a complexity of O(log p)
     * where p is the number of unigue  priorities currently in the queue having
     * the same length as the priority being pushed.
     *
     * \param priority The priority of the element.
     * \param t The element to insert.
     *
     * \return void.
     */
    void push (const string& priority, const T& t) {
      auto priorityBucket = buckets_[priority.size () - 1].insert (make_pair (priority, list<T> ())).first;
      priorityBucket->second.push_back (t);

      if (size_ == 0 || DIRECTION::compare (priority, *curHighest_)) {
        curPriorityBucket_ = priorityBucket;
        curHighest_ = priorityBucket->second.begin ();
      }
      ++size_;
    };

    /**
     * Removes and returns the highest priority element. pop has a complexity of
     * O(k) where k is the maximum number of digits a priority will have.
     *
     * \return The highest priority element.
     *
     * \throw runtime_error If the queue is empty.
     */
    T pop () {
      if (size_ == 0) throw runtime_error ("Priority queue is empty.");
      
      T t = *curHighest_;
      curPriorityBucket_->second.erase (curHighest_);
      if (curPriorityBucket_->second.empty ())
        buckets_[curPriorityBucket_->first.size () - 1].erase (curPriorityBucket_);
      --size_;

      if (size_ != 0) {
        for (auto cur = DIRECTION::begin (buckets_), end = DIRECTION::end (buckets_); cur != end; ++cur) {
          if (!cur->empty ()) {
            curPriorityBucket_ = DIRECTION::convert (DIRECTION::begin (*cur));
            curHighest_ = curPriorityBucket_->second.begin ();
            break;
          }
        }
      }
      return t;
    };

    /**
     * Returns the highest priority element. This is a constant time operation.
     * This is acheived by caching the current highest priority element, the priority
     * bucket it is in and the digits bucket it is in.
     *
     * \return A reference to the highest priority element.
     *
     * \throw runtime_error If the queue is empty.
     */
    T& top () const {
      if (size_ == 0) throw runtime_error ("Priority queue is empty.");
      return *curHighest_;
    };

    /**
     * Empties and returns the PriorityQueue as a stable ordered list containing
     * all of the elements currently in the queue. Complexity is O(n) where n is
     * the number of unique priorities currently in the queue. This is independent
     * of the number of elements in the queue.
     *
     * \return The stable ordered list of elements.
     */
    list<T> pop_all () {
      list<T> res;
      for (auto curDigitsBucket = DIRECTION::begin (buckets_), end = DIRECTION::end (buckets_);
        curDigitsBucket != end; ++curDigitsBucket) {
        while (!curDigitsBucket->empty ()) {
          auto curPriorityBucket = DIRECTION::begin (*curDigitsBucket);
          res.splice (res.end (), curPriorityBucket->second);
          curDigitsBucket->erase (DIRECTION::convert (curPriorityBucket));
        }
      }
      size_ = 0;
      return res;   
    };

    /**
     * Tells if the PriorityQueue is empty or not. This is a constant time operation.
     *
     * \return Whether or not the PriorityQueue is empty.
     */
    bool empty () const { return size_ == 0; };

    /**
     * Tells the number of elements in the PriorityQueue.
     *
     * \return The size.
     */
    unsigned int size () const { return size_; };

    /**
     * Writes the PriorityQueue to an ostream.
     *
     * \param os The ostream to which to write.
     * \param queue The PriorityQueue to write.
     *
     * \return A reference to the ostream.
     */
    friend ostream& operator<< (ostream& os, const PriorityQueue& queue) {
      int i = 0;
      for (auto curDigitsBucket = queue.buckets_.begin (), end = queue.buckets_.end (); curDigitsBucket != end; ++curDigitsBucket) {
        os << "  digits - " << i++ << endl;
        for (auto curPriorityBucket = curDigitsBucket->begin (), endBucket = curDigitsBucket->end (); curPriorityBucket != endBucket; ++curPriorityBucket) {
          os << "    priority - " << curPriorityBucket->first << endl;
          for (auto cur = curPriorityBucket->second.begin (), endEle = curPriorityBucket->second.end (); cur != endEle; ++cur) {
            os << "      element - " << *cur << endl;
          }
        }
        os << endl;
      }
      return os;
    };

    private:
      /**
       * The copy constructor.
       *
       * \param rhs The PriorityQueue to copy.
       */
      PriorityQueue (const PriorityQueue& rhs);

      /**
       * The assignment operator.
       *
       * \param rhs The PriorityQueue from which to assign.
       *
       * \return A reference to this PriorityQueue.
       */
      PriorityQueue& operator= (const PriorityQueue& rhs);
    
      /**
       * The bucket container.
       */
      BUCKETS buckets_;

      /**
       * The number of elements in the PriorityQueue.
       */
      int size_;

      /**
       * The priority bucket in which the current highest priority element resides.
       */
      typename BUCKET::iterator curPriorityBucket_;

      /**
       * The current highest priority element.
       */
      typename list<T>::iterator curHighest_;
  }; //PriorityQueue

  /**
   * \struct Min
   * Makes lower values the higher priorities.
   */
  struct Min {
    /**
     * Determines if the priority is lower than min.
     *
     * \param priority The priority to check.
     * \param min The min to check.
     *
     * \return bool True if lower, false otherwise.
     */
    static bool compare (const string& priority, const string& min) {
      return priority < min;
    };

    /**
     * Get the begin iterator from the container.
     *
     * \tparam T The type of the container.
     *
     * \param t The container.
     *
     * \return The iterator.
     */
    template<typename T>
    static typename T::iterator begin (T& t) {
      return t.begin ();
    };

    /**
     * Get the end iterator from the container.
     *
     * \tparam T The type of the container.
     *
     * \param t The container.
     *
     * \return The iterator.
     */
    template<typename T>
    static typename T::iterator end (T& t) {
      return t.end ();
    };

    /**
     * Ensures the iterator is a forward_iterator.
     *
     * \tparam T The type of the iterator.
     *
     * \param t The iterator.
     *
     * \return The converted iterator.
     */
    template<typename T>
    static T convert (const T& t) {
      return t;
    };
  }; //Min

  /**
   * \struct Max
   * Makes higher values the higher priorities.
   */
  struct Max {
    /**
     * Determines if the priority is higher than max.
     *
     * \param priority The priority to check.
     * \param max The max to check.
     *
     * \return bool True if higher, false otherwise.
     */
    static bool compare (const string& priority, const string& max) {
      return priority > max;
    };

    /**
     * Get the begin iterator from the container.
     *
     * \tparam T The type of the container.
     *
     * \param t The container.
     *
     * \return The iterator.
     */
    template<typename T>
    static typename T::reverse_iterator begin (T& t) {
      return t.rbegin ();;
    };

    /**
     * Get the end iterator from the container.
     *
     * \tparam T The type of the container.
     *
     * \param t The container.
     *
     * \return The iterator.
     */
    template<typename T>
    static typename T::reverse_iterator end (T& t) {
      return t.rend ();
    };

    /**
     * Ensures the iterator is a forward_iterator.
     *
     * \tparam T The type of the iterator.
     *
     * \param t The iterator.
     *
     * \return The converted iterator.
     */
    template<typename T>
    static typename T::iterator_type convert (const T& t) {
      return --t.base ();
    };
  }; //Max

  /**
   * \struct MinPriorityQueue
   * Lower valued priorities are higher priorities. This exists as a class because
   * g++ does not yet have templated typedefs.
   *
   * \tparam T The type to be held by the queue.
   */
  template<typename T>
  struct MinPriorityQueue : public PriorityQueue<T, Min> {
    MinPriorityQueue (unsigned int maxKeyLength) : PriorityQueue<T, Min> (maxKeyLength) {};
  };

  /**
   * \struct MaxPriorityQueue
   * Higher valued priorities are higher priorities. This exists as a class because
   * g++ does not yet have templated typedefs.
   *
   * \tparam T The type to be held by the queue.
   */
  template<typename T>
  struct MaxPriorityQueue : public PriorityQueue<T, Max> {
    MaxPriorityQueue (unsigned int maxKeyLength) : PriorityQueue<T, Max> (maxKeyLength) {};
  };
}; //data

#endif //DATA_PRIORITYQUEUE_H

