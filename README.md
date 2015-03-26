Enum Extend {#mainpage}
============

A C++ library that extends the functionality of enums.

Motivation
----------
C++, the STL and boost lack some often needed functionality in regard to enums:
* It is not possible to iterate over all defined enumerated values.
* There are no pre or postfix ++/-- operators to advance to the next defined enumerated value.
* Often enumerated values needs a string representation to further operations - at least to log those into files.

Enum Extend Library Overview
----------------------------
The following is possible with this library:

~~~
  using enum_extend::range;
  using enum_extend::extend;
  using enum_extend::filtered_range;
  
  enum Color
  {
    Red = 0, 
    Green = 4, 
    Blue = 8
  };

  // Let's walk over all defined values
  for (auto c : range<Color>()) {
    // ...
  }
  
  auto c = Color::Red;
  // we can increase as well
  ++c;

  // We iterate in reverse order over all defined values
  std::vector<Color> allReverseColors;
  std::copy(extend<Color>::rbegin(),
            extend<Color>::rend(), 
            std::back_inserter(allReverseColors));


  // Just iterate over all values that match a certain criteria; 
  // usefull if the enumerated values are defined as combined bit fields
  auto FilterRed = [](Color c) { return c == Color::Red; };
  for (auto c : filtered_range<Color>(FilterRed)) {
    // Do just something with red values
  }
  
  
  // easier can this be archived by the following macros:
  
  // for the header file
  #define MACROCOLOR_ENUM_SPEC (MacroColorEnum, (Red)(Green)(Blue))
  ENUM_EXTEND_DECLARE_ENUM(MACROCOLOR_ENUM_SPEC)
  
  // for the cpp file
  ENUM_EXTEND_DEFINE_ENUM(MACROCOLOR_ENUM_SPEC)

~~~

Macros exist as well for creating an enum class or a typed enum class.


Documentation
-------------
A first tutorial is [here](https://github.com/FelixPetriconi/enum_extend/wiki/Tutorial)

Author 
------
  Felix Petriconi (felix at petriconi.net)
  

Contributions
-------------

  Comments, feedback or contributions are welcome!

  
License
-------
  Boost 1.0 License


Version
-------
  1.0

Prerequisites
-------------
  * C++ 11 (partly, as far as Visual Studio 2013 supports it)
  * CMake 2.8 or later
  * Boost Preprocessor (1.55)
  * GoogleTest 1.7 (It is part of the repository, because it's CMakeFiles.txt needs some patches to compile with Visual Studio)


Platform
--------
| Compiler | Status |
-----------|---------
| Visual Studio 2013 x64 | All tests pass |
| Clang 3.6 | All tests pass |


Installation Win
----------------
  * Clone into e.g. D:\misc\enum_extend
  * Create a build folder, eg D:\misc\enum_extend_build
  * Open a command prompt in that enum_extend_build
  * Have CMake in the path
  * Execute cmake -G "Visual Studio 12 Win64" ..\enum_extend
  * Open created solution in .\enum_extend_build\enum_library.sln
  * Compile and run all test
  
ToDo
----
 * Docs
 