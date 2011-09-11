/**
 * \file priority_queue.cpp, Contains the PriorityQueue usage example.
 *
 * Copyright (C) 2011 Thomas P. Lahoda
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
#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <algorithm>

#include "PriorityQueue.h"

int main (int argc, char** argv) {
  using namespace std;
  using namespace data;

  MinPriorityQueue<string> minQueue;
  minQueue.push ("30", "3");
  minQueue.push ("20", "2a");
  minQueue.push ("600", "6c");
  minQueue.push ("1", "1");
  minQueue.push ("20", "2b");
  minQueue.push ("600", "6a");
  minQueue.push ("500", "5");
  minQueue.push ("40", "4");
  minQueue.push ("20", "2c");
  minQueue.push ("600", "6b");

  cout << "----------------------------------------" << endl;
  cout << "MinPriorityQueue internal structure:" << endl;
  cout << "----------------------------------------" << endl;
  minQueue.print ();
  cout << "----------------------------------------" << endl << endl;

  cout << "Min pop_all:" << endl;
  cout << "----------------------------------------" << endl;
  list<string> flatQueue = minQueue.pop_all ();
  copy (flatQueue.begin (), flatQueue.end (), ostream_iterator<string> (cout, "\n"));
  cout << "----------------------------------------" << endl << endl;

  MaxPriorityQueue<string> maxQueue;
  maxQueue.push ("30", "3");
  maxQueue.push ("20", "2a");
  maxQueue.push ("600", "6c");
  maxQueue.push ("1", "1");
  maxQueue.push ("20", "2b");
  maxQueue.push ("600", "6a");
  maxQueue.push ("500", "5");
  maxQueue.push ("40", "4");
  maxQueue.push ("20", "2c");
  maxQueue.push ("600", "6b");

  cout << "MaxPriorityQueue internal structure:" << endl;
  cout << "----------------------------------------" << endl;
  maxQueue.print ();
  cout << "----------------------------------------" << endl << endl;

  cout << "Max pop:" << endl;
  cout << "----------------------------------------" << endl;
  while (!maxQueue.empty ())
    cout << maxQueue.pop () << std::endl;
  cout << "----------------------------------------" << endl;
  
  return 0;
};

