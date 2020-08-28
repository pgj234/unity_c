from distutils.core import setup, Extension

setup(name = "_ex02",
    version = "1.0",
    description = "hello method smaple",
    author = "pgj",
    author_email = "pgj94@naver.com",
    url = "https://www.youtube.com/channel/UC3AmmUhLog47cJW9UWse96g?view_as=subscriber",
    ext_modules = [Extension("_ex02",
    sources = ["ex02_py_mod.c"])]
)