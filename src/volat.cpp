/* volat.cpp
 * This file is a part of atvocpptests library
 * Copyright (c) atvocpptests authors (see file `COPYRIGHT` for the license)
 */
#include <iostream>
#include <tr1/memory>

#include "common.h"

static const int  NUM_IT=1024 * 1024;

void IncThreadFunc(volatile int * volatile started, volatile int * volatile int_ptr, boost::condition_variable * cond, boost::mutex * mut)
{
  {
    boost::unique_lock<boost::mutex> lock(*mut);
    ++*started;
    cond->wait(lock);
  }
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
  boost::condition_variable cond;
  boost::mutex mut;
  volatile int started = 0;

  Threads threads;
  for(Threads::iterator it = threads.begin(); it != threads.end(); ++it)
  {
    *it = boost::thread(boost::bind(&IncThreadFunc, &started, &i, &cond, &mut));
  }

  while(started < NUM_THREADS)
  {
    boost::this_thread::sleep(boost::posix_time::milliseconds(10));
  }

  cond.notify_all();

  for(Threads::iterator it = threads.begin(); it != threads.end(); ++it)
  {
    (*it).join();
  }

  std::cout<<"result  "<<i<<" expected "<<(NUM_THREADS*NUM_IT)<<" ("<<(NUM_THREADS*NUM_IT-i)<<")"<<std::endl;

  return 0;
}

