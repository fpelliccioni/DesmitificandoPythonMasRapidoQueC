from distutils.core import setup, Extension

module1 = Extension('hrc',
                    sources = ['hrcmodule.cpp'])

setup (name = 'PackageName',
       version = '1.0',
       description = 'This is a hrc package',
       ext_modules = [module1])