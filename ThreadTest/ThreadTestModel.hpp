#pragma once

#include <halp/audio.hpp>
#include <halp/controls.hpp>
#include <halp/meta.hpp>

#include <memory>

#include "PythonEnvModel.hpp"

namespace Example
{

    class ThreadTest
    {
    public:
        halp_meta(name, "Thread Test")
        halp_meta(category, "Audio")
        halp_meta(c_name, "threadtest")
        halp_meta(uuid, "fb4c5ebb-5961-4856-9434-3ca6e8761448")

        ThreadTest(): to_python_env{std::make_shared<python_env>()}{}

        std::shared_ptr<python_env> to_python_env;

        struct ins
        {
            halp::dynamic_audio_bus<"Input", double> audio;

            struct {
                enum widget { pushbutton };
                halp_meta(name, "Execute python code")
                bool value;
            } launcher1;
            using launcher1_t = decltype(launcher1);

            struct : halp::lineedit<"Program", "">
            {
                halp_meta(language, "Python")
            } program;
        } inputs;

        struct
        {
            halp::dynamic_audio_bus<"Output", double> audio;
        } outputs;

        struct 
        {
            // Called from DSP thread
            std::function<void(std::shared_ptr<python_env>, std::string)> request;

            // "work" is called from a worker thread
            static std::function<void(ThreadTest&)> work(std::shared_ptr<python_env>, std::string);

            // The std::function object returned by work is called from the DSP thread
        } worker;
        using worker_t = decltype(worker);

        using setup = halp::setup;
        void prepare(halp::setup info)
        {
            // Initialization, this method will be called with buffer size, etc.
        }

        // Do our processing for N samples
        using tick = halp::tick;

        // Defined in the .cpp
        void operator()(halp::tick t);

        // UI is defined in another file to keep things clear.
    };

}
