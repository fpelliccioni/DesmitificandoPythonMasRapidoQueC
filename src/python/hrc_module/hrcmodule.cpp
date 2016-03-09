// Documentation for Python Module Creation
//  https://docs.python.org/3.5/extending/extending.html
//  https://docs.python.org/3.5/extending/building.html#building

// Compilation
//  Windows:
//    For Visual Studio 2013 (VS12): 
//      SET VS90COMNTOOLS=%VS120COMNTOOLS%
//    For Visual Studio 2015 (VS14): 
//      SET VS90COMNTOOLS=%VS140COMNTOOLS%

//    #python setup.py build
//    #python setup.py install
//    py -2 setup.py build
//    py -2 setup.py install

//    D:\Python27\Python.exe setup.py build


//    py -3 setup.py build
//    py -3 setup.py install
// Linux?   
//    export CFLAGS='-std=c++11'
// 		python setup.py build
// 		python setup.py install
//  OSX
//    export CPPFLAGS='-std=c++1y -stdlib=libc++ -mmacosx-version-min=10.7'
//    python3 setup.py build
//    python3 setup.py install


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

static struct PyModuleDef hrcmodule = {
   PyModuleDef_HEAD_INIT,
   "hrc",   /* name of module */
   NULL, //hrc_doc, /* module documentation, may be NULL */
   -1,        //size of per-interpreter state of the module,
                //or -1 if the module keeps state in global variables. 
   HrcMethods
};

PyMODINIT_FUNC
PyInit_hrc(void) {
    return PyModule_Create(&hrcmodule);
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

