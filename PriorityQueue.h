/**
 * \file PriorityQueue.h, Contains a priority queue implemented using a LSD radix
 * sort. 
 *
 * Due to the way C++ does its data structures pop performs in constant time and
 * push has a worse case performance of O(2*log (k*Np)) where k is the maximum
 * number of digits a priority may have and Np is the size of the set of 
 * priorities having the same number of digits as the priority being pushed. This
 * is independent of the number of elements held in the queue and is only
 * dependent on the set of priorities being used. Normally a radix sort has a
 * complexity of O(k*n) where k is the maximum number of digits a priority may
 * have and n is the number of possible priorities.
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
#include <map>
#include <list>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <iostream>

namespace data {
  using namespace std;

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
     * Get the iterator from the container.
     *
     * \tparam T The type of the container.
     *
     * \param t The container.
     *
     * \return The iterator.
     */
    template<typename T>
    static typename T::iterator getIter (T& t) {
      return t.begin ();
    };
  };

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
     * Get the iterator from the container.
     *
     * \tparam T The type of the container.
     *
     * \param t The container.
     *
     * \return The iterator.
     */
    template<typename T>
    static typename T::iterator getIter (T& t) {
      return --t.end ();
    };
  };

  /**
   * \struct PriorityQueue
   * Implements a priority queue in terms of a radix sort.
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
    typedef map<string, list<T> > BUCKET;

    /**
     * \typedef map<unsigned int, BUCKET> BUCKETS
     * The type of the buckets container.
     */
    typedef map<unsigned int, BUCKET> BUCKETS;

    /**
     * Constructs a PriorityQueue. This is a constant time operation.
     */
    PriorityQueue () : buckets_ (), size_ (0), curMaxDigitsBucket_ (), curMaxPriorityBucket_ (), curMax_ () {};

    /**
     * Destroys a PriorityQueue. The will be a linear time operation based on the
     * numebr of elements in the queue.
     */
    ~PriorityQueue () {};

    /**
     * Pushes an element onto the PriorityQueue. Complexity is O(log k*Np)
     * where k is the maximum number of digits of a priority and Np is the size
     * of the set of priorities having the same number of digits as the priority
     * being pushed. In some case this could perform O(2*log k*Np) to be more
     * precise.
     *
     * \param priority The priority of the element.
     * \param t The element to insert.
     *
     * \return void.
     */
    void push (const string& priority, const T& t) {
      unsigned int numDigits = priority.size ();
      typename BUCKETS::iterator digitsBucket = buckets_.find (numDigits);
      if (digitsBucket == buckets_.end ())
        digitsBucket = buckets_.insert (make_pair (numDigits, BUCKET ())).first;
     
      typename BUCKET::iterator priorityBucket = digitsBucket->second.find (priority);
      if (priorityBucket == digitsBucket->second.end ())
        priorityBucket = digitsBucket->second.insert (make_pair (priority, list<T> ())).first;

      priorityBucket->second.push_back (t);

      if (size_ == 0 || DIRECTION::compare (priority, *curMax_)) {
        curMaxDigitsBucket_ = digitsBucket;
        curMaxPriorityBucket_ = priorityBucket;
        curMax_ = priorityBucket->second.begin ();
      }
      ++size_;
    };

    /**
     * Removes and returns the highest priority element. This is a constant time operation.
     *
     * \return The highest priority element.
     *
     * \throw runtime_error If the queue is empty.
     */
    T pop () {
      if (size_ == 0) throw runtime_error ("Priority queue is empty.");

      T t = *curMax_;
      curMaxPriorityBucket_->second.erase (curMax_);
      if (curMaxPriorityBucket_->second.empty ())
        curMaxDigitsBucket_->second.erase (curMaxPriorityBucket_);
      
      if (curMaxDigitsBucket_->second.empty ())
        buckets_.erase (curMaxDigitsBucket_);
      --size_;

      if (size_ != 0) {
        curMaxDigitsBucket_ = DIRECTION::getIter (buckets_);
        curMaxPriorityBucket_ = DIRECTION::getIter (curMaxDigitsBucket_->second);
        curMax_ = curMaxPriorityBucket_->second.begin ();
      }
      return t;
    };

    /**
     * Returns the highest priority element. This is a constant time operation.
     *
     * \return A reference to the highest priority element.
     *
     * \throw runtime_error If the queue is empty.
     */
    T& top () {
      if (size_ == 0) throw runtime_error ("Priority queue is empty.");
      return *curMax_;
    };

    /**
     * Tells if the PriorityQueue is empty or not. This is a constant time operation.
     *
     * \return Whether or not the PriorityQueue is empty.
     */
    bool empty () { return size_ == 0; };

    /**
     * Tells the number of elements in the PriorityQueue.
     *
     * \return The size.
     */
    unsigned int size () { return size_; };

    /**
     * Prints the contents of the queue.
     *
     * \return void.
     */
    void print () {
      for (typename BUCKETS::iterator curDigitsBucket = buckets_.begin (); curDigitsBucket != buckets_.end (); ++curDigitsBucket) {
        cout << curDigitsBucket->first << endl;
        for (typename BUCKET::iterator curPriorityBucket = curDigitsBucket->second.begin (); curPriorityBucket != curDigitsBucket->second.end (); ++curPriorityBucket) {
          cout << "\t" << curPriorityBucket->first << endl;
          for (typename list<T>::iterator cur = curPriorityBucket->second.begin (); cur != curPriorityBucket->second.end (); ++cur) {
            cout << "\t\t" << *cur << endl;
          }
        }
      }
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
       * The digits bucket in which the current max priority element resides.
       */
      typename BUCKETS::iterator curMaxDigitsBucket_;

      /**
       * The priority bucket in which the current max priority element resides.
       */
      typename BUCKET::iterator curMaxPriorityBucket_;

      /**
       * The current max priority element.
       */
      typename list<T>::iterator curMax_;
  }; //PriorityQueue
}; //data

#endif //DATA_PRIORITYQUEUE_H

