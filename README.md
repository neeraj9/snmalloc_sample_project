# snmalloc_sample_project

This is a sample project which uses [snmalloc] in a couple
of different setup. There are a couple of ways to
integrate [snmalloc] and the one highlighted here may not
be the best for your scenario. Irrespective, this one
is tested and does work without much of trouble.

## Microsoft Windows

The code repository [windows](./windows), shall capture
the Microsoft windows operating system and is largely
built using Visual Studio 2019.

### Standalone pure c++ project

You first need to clone and get snmalloc submodule
as follows.

```console
git clone https://github.com/neeraj9/snmalloc_sample_project
cd snmalloc_sample_project
cd windows
git submodule init
git submodule update
```

You should then subsequently open [SnmallocSample.sln](./windows/SnmallocSample.sln)
and more specifically build `SampleConsoleApp`. This will
generate an executable for the x64 platform, which uses
[snmalloc] internally via custom allocator and needs to be
injected within the standard c++ STL (as shown in the project).

### C++/CLI mixed c# and c++ project

* CppNativeLibrary - This is the pure C++ library which
  includes snmalloc, simple wrapper for including its build
  system (SnmallocWrapper.h/cpp) and a sample library
  (SearchWeb.h/cpp) which demonstrates memory allocation
  via snmalloc. This consists of unmanaged C++ code.
* DotNETCppInteropLibrary - This is the interop library which
  connects native C++ library (CppNativeLibrary) with the
  C# console application (CsharpConsoleApp). There is an
  interesting transformation between unmanaged C++ native
  library and .NET. This repository contains managed C++ code.
* CsharpConsoleApp - C# .NET 5 console application, which
  uses DotNETCppInteropLibrary to invoke functionality exposed
  by CppNativeLibrary. Note that CsharpConsoleApp do not
  know about CppNativeLibrary directly.

[snmalloc]: https://github.com/Microsoft/snmalloc
