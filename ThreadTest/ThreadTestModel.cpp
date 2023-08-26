#include "ThreadTest.hpp"
#include <iostream>

namespace Example
{
void ThreadTest::operator()(halp::tick t)
{
    if (inputs.launcher1.value)
    {
        this->worker.request(this->to_python_env, inputs.program.value);
    }
    // Process the input buffer
}

std::function<void(ThreadTest&)> ThreadTest::worker_t::work(std::shared_ptr<python_env> penv, std::string code)
{
    // 3. Implement the "threaded" work part:
    // This is executed in a separate worker thread, slow operations can be done here 
    // safely.
    penv->exec_code(code);
    // 4. Return a function which will update the internal state of ThreadTest:
    return {};
}
}
