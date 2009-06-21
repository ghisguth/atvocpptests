/* volat_barrier.cpp
 * This file is a part of atvocpptests library
 * Copyright (c) atvocpptests authors (see file `COPYRIGHT` for the license)
 */
#include <iostream>
#include <tr1/memory>
#include <boost/thread/barrier.hpp>

#include "common.h"

static const int  NUM_IT=1024 * 1024;

void IncThreadFunc(boost::barrier * barrier, volatile int * volatile int_ptr)
{
  barrier->wait();
  for(int i = 0; i < NUM_IT; ++i)
  {
    ++*int_ptr;
  }
}

int main()
{
  static const int NUM_THREADS = 64;
  typedef boost::array<boost::thread, NUM_THREADS> Threads;

  std::cout<<"hardware concurrency "<<boost::thread::hardware_concurrency()<<std::endl;
  std::cout<<"threads "<<NUM_THREADS<<std::endl;
  std::cout<<"iterations per threads "<<NUM_IT<<std::endl;

  volatile int i = 0;
  boost::barrier barrier(NUM_THREADS);

  Threads threads;
  for(Threads::iterator it = threads.begin(); it != threads.end(); ++it)
  {
    *it = boost::thread(boost::bind(&IncThreadFunc, &barrier, &i));
  }

  for(Threads::iterator it = threads.begin(); it != threads.end(); ++it)
  {
    (*it).join();
  }

  std::cout<<"result  "<<i<<" expected "<<(NUM_THREADS*NUM_IT)<<" ("<<(NUM_THREADS*NUM_IT-i)<<")"<<std::endl;

  return 0;
}

