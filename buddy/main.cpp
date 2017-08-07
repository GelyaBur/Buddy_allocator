#include <iostream>
#include "buddy_alloc.h"
#include <new>
#include <Python.h>
#include <stdexcept>
#include <python_allocator.h>

int main()
{
    size_t size = 160000000;
    void *p0 = operator new(size);
    void *p = (void *) ((char *) p0 + ((size_t)((char *) p0 + 15) & ~(size_t) (15)) -(size_t) p0);
    std::cout << "address p: " << p << '\n';
    Py_Initialize();
    PythonAllocator<BuddyAllocator> alloc(p, size);
    alloc.set_py_allocators();
    FILE *fp = fopen("myfile", "r");
    if (fp == NULL)
        std::cerr << "can't open file";
    fseek(fp, 0, SEEK_END);
    long int s = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *str = (char *) malloc(sizeof(char) * s);
    if (str == NULL)
        std::cerr << "error malloc";
    size_t res = fread(str, 1, s, fp);
    if (res != s)
        std::cerr << "error fread";
    //const char *str = "print('trololo', 5+5)\nprint('GG')";
    const char *str2 = "print(50*10000, '!!')";
    const char *file = "myfile";
    std::cout << "first\n";
    PyObject *py_code = Py_CompileString(str, file, Py_file_input);
    PyObject *py_code2 = Py_CompileString(str2, file, Py_file_input);
    std::cout << "second\n";
    if (PyErr_Occurred()) {
        throw std::runtime_error("compilation error 1");
    }
    std::cout << "third\n";
    PyObject *_globals = PyModule_GetDict(PyImport_AddModule("__main__"));
    PyObject *_locals = PyDict_New();
    std::cout << "forth\n";
    PyEval_EvalCode(py_code, _globals, _locals);
    PyEval_EvalCode(py_code2, _globals, _locals);
    if (PyErr_Occurred()) {
        throw std::runtime_error("evaluation error");
    }
    std::cerr << "before return main\n";
    return 0;
}
