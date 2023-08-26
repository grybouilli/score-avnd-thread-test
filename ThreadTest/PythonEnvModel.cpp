#include "PythonEnvModel.hpp"
#include <filesystem>
#include <sstream>
#include "numpyToCppUtils.hpp"

python_env::python_env()
{
    try
    {
        Py_Initialize();
        np::initialize();

        _main = python::import("__main__");
        python::exec(
            "import sys; import os", 
            _main.attr("__dict__")
        );
    }
    catch (const python::error_already_set&)
    {
        PyErr_Print();
    }
}

void python_env::add_to_search_path(const std::string& path)
{
    try
    {
    if (path != "" && std::filesystem::is_directory(path))
    {
        std::stringstream add_new_path_cmd{};
        add_new_path_cmd << "sys.path.append(\'" << path << "\')\n"
            << "os.chdir(\'" << path << "\')";

        python::exec(
            add_new_path_cmd.str().c_str(),
            _main.attr("__dict__")
        );
    }
    }
    catch(const python::error_already_set&)
    {
        PyErr_Print();
    }
}

bool python_env::exec_code(const std::string& code)
{
    try
    {
        python::exec(
            code.c_str(),
            _main.attr("__dict__")
        );
    }
    catch(const python::error_already_set&)
    {
        PyErr_Print();
        return false;
    }
    return true;
}

std::vector<float>& python_env::get_array(const std::string& array_name)
{
    std::vector<float> out {};
    try
    {
        auto src = python::extract<np::ndarray>(_main.attr(array_name.c_str()))(); // store the np.ndarray into a variable
        copy(src, out);
    }
    catch(const python::error_already_set&)
    {
        PyErr_Print();
    }
    return out;
}

std::vector<float>& python_env::get_array_from_func(const std::string& func_name)
{
    std::vector<float> out {};
    try
    {
        auto src = python::extract<np::ndarray>(_main.attr(func_name.c_str())())(); // store the np.ndarray into a variable
        copy(src, out);
    }
    catch(const python::error_already_set&)
    {
        PyErr_Print();
    }
    return out;
}