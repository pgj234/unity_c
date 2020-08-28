# setup.py
from distutils.core import setup, Extension

setup(name = "_ex01",
        version = "1.0",
        description = "ex01",
        author = "gbox3d",
        author_email = "gbox3d@gmail.com",
        url = "https://gbox3d.blogspot.com/",
        ext_modules = [Extension("_ex01", ["ex01.c"])]
        )