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
#include <map>
#include <list>
#include <algorithm>
#include <stdexcept>
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
    static typename T::iterator iterator (T& t) {
      return t.begin ();
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
     * Get the iterator from the container.
     *
     * \tparam T The type of the container.
     *
     * \param t The container.
     *
     * \return The iterator.
     */
    template<typename T>
    static typename T::iterator iterator (T& t) {
      return --t.end ();
    };
  }; //Max

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
    typedef map<string, list<T> > BUCKET;

    /**
     * \typedef map<unsigned int, BUCKET> BUCKETS
     * The type of the buckets container.
     */
    typedef map<unsigned int, BUCKET> BUCKETS;

    /**
     * Constructs a PriorityQueue. This is a constant time operation.
     */
    PriorityQueue () : buckets_ (), size_ (0), curDigitsBucket_ (), curPriorityBucket_ (), curHighest_ () {};

    /**
     * Destroys a PriorityQueue. Complexity is O(n) where n is the number of elements
     * in the queue at the time of destruction.
     */
    ~PriorityQueue () {};

    /**
     * Pushes an element onto the PriorityQueue. push has a typical complexity of
     * O(log k*p) where k is the maximum number of digits a priority may have and
     * p is the number of unigue  priorities currently in the queue having the
     * same length as the priority being pushed. Worst case complexity is
     * O(log 2*k*Np) where k is the maximum number of digits a priority may have
     * and Np is the size of the set of priorities having the same number of
     * digits as the priority being pushed. This occurs when both a digits bucket
     * has to be created and a priority bucket has to be created. This is 
     * guaranteed to occur the first time a priority is pushed into the queue.
     *
     * Any issue with construction cost of the maps or the list could be
     * alleviated by caching the maps instead of constructing and destroying them.
     *
     * \param priority The priority of the element.
     * \param t The element to insert.
     *
     * \return void.
     */
    void push (const string& priority, const T& t) {
      unsigned int numDigits = priority.size ();
      auto digitsBucket = buckets_.find (numDigits);
      if (digitsBucket == buckets_.end ())
        digitsBucket = buckets_.insert (make_pair (numDigits, BUCKET ())).first;
     
      auto priorityBucket = digitsBucket->second.find (priority);
      if (priorityBucket == digitsBucket->second.end ())
        priorityBucket = digitsBucket->second.insert (make_pair (priority, list<T> ())).first;

      priorityBucket->second.push_back (t);

      if (size_ == 0 || DIRECTION::compare (priority, *curHighest_)) {
        curDigitsBucket_ = digitsBucket;
        curPriorityBucket_ = priorityBucket;
        curHighest_ = priorityBucket->second.begin ();
      }
      ++size_;
    };

    /**
     * Removes and returns the highest priority element. This is a constant time operation.
     * This is acheived by the removal of empty buckets from the structure, by using C++'s
     * begin/end iterators to find the highest priority, and by caching the current highest
     * priority element, the priority bucket it is in and the digits bucket it is in.
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
        curDigitsBucket_->second.erase (curPriorityBucket_);
      
      if (curDigitsBucket_->second.empty ())
        buckets_.erase (curDigitsBucket_);
      --size_;

      if (size_ != 0) {
        curDigitsBucket_ = DIRECTION::iterator (buckets_);
        curPriorityBucket_ = DIRECTION::iterator (curDigitsBucket_->second);
        curHighest_ = curPriorityBucket_->second.begin ();
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
      while (!buckets_.empty ()) {
        auto curDigitsBucket = DIRECTION::iterator (buckets_);
        while (!curDigitsBucket->second.empty ()) {
          auto curPriorityBucket = DIRECTION::iterator (curDigitsBucket->second);
          res.splice (res.end (), curPriorityBucket->second);
          curDigitsBucket->second.erase (curPriorityBucket);
        }
        buckets_.erase (curDigitsBucket);
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
     * Prints the contents of the queue.
     *
     * \return void.
     */
    void print () const {
      for (auto curDigitsBucket = buckets_.begin (), end = buckets_.end (); 
           curDigitsBucket != end; ++curDigitsBucket) {
        cout << curDigitsBucket->first << endl;
        for (auto curPriorityBucket = curDigitsBucket->second.begin (), endBucket = curDigitsBucket->second.end ();
             curPriorityBucket != endBucket; ++curPriorityBucket) {
          cout << "\t" << curPriorityBucket->first << endl;
          for (auto cur = curPriorityBucket->second.begin (), endEle = curPriorityBucket->second.end ();
              cur != endEle; ++cur) {
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
       * The digits bucket in which the current highest priority element resides.
       */
      typename BUCKETS::iterator curDigitsBucket_;

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
   * \struct MinPriorityQueue
   * Lower valued priorities are higher priorities. This exists as a class because
   * g++ does not yet have templated typedefs.
   *
   * \tparam T The type to be held by the queue.
   */
  template<typename T>
  struct MinPriorityQueue : public PriorityQueue<T, Min> {};

  /**
   * \struct MaxPriorityQueue
   * Higher valued priorities are higher priorities. This exists as a class because
   * g++ does not yet have templated typedefs.
   *
   * \tparam T The type to be held by the queue.
   */
  template<typename T>
  struct MaxPriorityQueue : public PriorityQueue<T, Max> {};
}; //data

#endif //DATA_PRIORITYQUEUE_H

