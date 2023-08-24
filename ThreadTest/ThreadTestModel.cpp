#include "ThreadTest.hpp"
#include <iostream>

namespace Example
{
void ThreadTest::operator()(halp::tick t)
{
    if(inputs.launcher1.value)
    {
        this->worker.request(123, "foo");
    }
  // Process the input buffer
}

void ThreadTest::ins::launcher1_t::update(ThreadTest& obj)
{
}

void ThreadTest::ins::launcher2_t::update(ThreadTest& obj)
{
    std::cerr << obj.internal_string << std::endl;
}

std::function<void(ThreadTest&)> ThreadTest::worker_t::work(int x, std::string foo)
{
  // 3. Implement the "threaded" work part:
  // This is executed in a separate worker thread, slow operations can be done here 
  // safely.

  // Repeat the string x times:
  std::string orig = foo;
  while(x > 0) {
    foo += orig;
  }

  // 4. Return a function which will update the internal state of ThreadTest:
  return [str = std::move(foo)] (ThreadTest& obj) {
    // Executed in the DSP thread again, so don't do long operations here!
    obj.internal_string = str;
  };
}
}
