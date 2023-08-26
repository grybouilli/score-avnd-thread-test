#pragma once

#include <boost/python.hpp> 
#include <boost/python/numpy.hpp>

#include <string>
#include <vector>

namespace python = boost::python;
namespace np = boost::python::numpy;

class python_env
{
public: 
    python_env();

    void add_to_search_path(const std::string&);

    bool exec_code (const std::string&);
    // bool exec_function(const std::string&);

    std::vector<float>& get_array(const std::string&);
    std::vector<float>& get_array_from_func(const std::string&);

private:
    python::object _main;

};