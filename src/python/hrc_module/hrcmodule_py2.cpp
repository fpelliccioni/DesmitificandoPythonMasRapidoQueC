// Documentation for Python Module Creation
//  https://docs.python.org/2/extending/extending.html
//  https://docs.python.org/2/extending/building.html#building

// Compilation
//  Windows:
//    For Visual Studio 2013 (VS12): 
//      SET VS90COMNTOOLS=%VS120COMNTOOLS%
//    For Visual Studio 2015 (VS14): 
//      SET VS90COMNTOOLS=%VS140COMNTOOLS%

//    py -2 setup_py2.py build
//    py -2 setup_py2.py install
// Linux?   
//    export CFLAGS='-std=c++11'
// 		python setup_py2.py build
// 		python setup_py2.py install
//  OSX
//    export CPPFLAGS='-std=c++1y -stdlib=libc++ -mmacosx-version-min=10.7'
//    python2??? setup_py2.py build
//    python2??? setup_py2.py install


// Test
// 		>>> import hrc
// 		>>> status = hrc.nanoseconds_since_epoch()





// hrc: high_resolution_clock

#include <chrono>
#include <Python.h>

static PyObject *
hrc_nanoseconds_since_epoch(PyObject *self, PyObject *args) {

    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::high_resolution_clock::now().time_since_epoch()
            ).count();

    return PyLong_FromLongLong(ns);
}

static PyMethodDef HrcMethods[] = {
    //...
    {"nanoseconds_since_epoch",  hrc_nanoseconds_since_epoch, METH_VARARGS,
     "Returns a 64-bit signed integer representing the number of nanoseconds elapsed between Now and the clock's Unix epoch."},
    //...
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

PyMODINIT_FUNC
inithrc(void)
{
    (void) Py_InitModule("hrc", HrcMethods);
}

// int
// main(int argc, char *argv[])
// {
//     wchar_t *program = Py_DecodeLocale(argv[0], NULL);
//     if (program == NULL) {
//         fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
//         exit(1);
//     }

//     /* Add a built-in module, before Py_Initialize */
//     PyImport_AppendInittab("hrc", PyInit_hrc);

//     // /* Pass argv[0] to the Python interpreter */
//     Py_SetProgramName(program);

//     /* Initialize the Python interpreter.  Required. */
//     Py_Initialize();

//     /* Optionally import the module; alternatively,
//        import can be deferred until the embedded script
//        imports it. */
//     PyImport_ImportModule("hrc");

//     //...

//     PyMem_RawFree(program);
//     return 0;
// }

