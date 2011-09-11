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

#include "PriorityQueue.h"

int main (int argc, char** argv) {
  using namespace std;
  using namespace data;

  MinPriorityQueue<string> queue;
  queue.push ("30", "3");
  queue.push ("20", "2a");
  queue.push ("600", "6c");
  queue.push ("1", "1");
  queue.push ("20", "2b");
  queue.push ("600", "6a");
  queue.push ("500", "5");
  queue.push ("40", "4");
  queue.push ("20", "2c");
  queue.push ("600", "6b");

  queue.print ();

  list<string> flatQueue = queue.pop_all ();

  for (list<string>::iterator cur = flatQueue.begin (); cur != flatQueue.end (); ++cur) {
    cout << *cur << endl;
  }
  //while (!queue.empty ())
  //  cout << queue.pop () << std::endl;
  
  return 0;
};

