## Specialize The enum_extend::extender
It is necessary to specialize the enum_extend::extender class with the enum type and initialize it with all existing values:

~~~C++
~~~

Doing this manually has the disadvantage that one has to write all enumerated values twice, first at the declaration and the again for the specialization. Additionally one might forget to update the implementation part when one changes the enum declaration. So there is a set of macros that helps to circumvent both:

~~~C++
// for the header file
#include <enum_extend/declare_typed_enum_class.hpp>

#define RGBCOLOR_ENUM_SPEC (RGBColors, char, (Red)(Green)(Blue))
ENUM_EXTEND_DECLARE_TYPED_ENUM_CLASS(RGBCOLOR_ENUM_SPEC)
~~~

This expands to:

~~~C++
enum RGBColors : char
{
  Red, Green, Blue
};

RGBColors& operator++(RGBColors& e);                                                  
RGBColors& operator--(RGBColors& e);                                                  
RGBColors operator++(RGBColors& e, int);                                              
RGBColors operator--(RGBColors& e, int);                                              
~~~

The part for the implementation file is:

~~~C++
#include "[corresponding header file]"
#include <enum_extend/define_typed_enum_class.hpp>

// for the cpp file
ENUM_EXTEND_DEFINE_TYPED_ENUM_CLASS(RGBCOLOR_ENUM_SPEC)
~~~ 

Which expands to

~~~C++
template <>
enum_extend::extender<RGBColors>::instances enum_extend::extender<RGBColors>::s_instances = {
  RGBColors::Red, RGBColors::Green, RGBColors::Blue
};

RGBColors& operator++(RGBColors& e) { return enum_extend::extender<RGBColors>::increment(e); } 
RGBColors& operator--(RGBColors& e) { return enum_extend::extender<RGBColors>::decrement(e); }
RGBColors operator++(RGBColors& e, int) {                                            
  auto tmp = e;                                                            
  enum_extend::extender<RGBColors>::increment(e);
  return tmp;                                                              
}                                                                          
RGBColors operator--(RGBColors& e, int) {                                            
  auto tmp = e;                                                            
  enum_extend::extender<RGBColors>::decrement(e);
  return tmp;                                                              
}                                                                          
~~~

## Range Based Loop Over All Enumerated Values
### Problem

Sometimes there are reasons that the enumerated values are pre-defined with explicit values, that are not contiguous. In this case it is not possible to cast a value to int, increment it inside a loop and then cast back to the enumerated type.

~~~C++
enum Color class {
  Red = 0x4,
  Green = 0x8,
  Blue = 0x10
}

for (int c = static_cast<int>(Color::Red); i <= static_cast<int>(Color::Blue); i++) {
  // This is plain wrong!
} 
~~~

### Solution

Create a range that provides begin() and end() iterators.

~~~C++
for (auto c : enum_extend::range<Color>()) {
  // c iterates over all defined values
}
~~~

## Context Related Loop Over A Subset Of Enumerated Values
### Problem

Some enumerated values are composed from others and we need to iterate over all those where a specific bit is set.

~~~C++
enum TrafficLightStates class {
  Red = 0x1,
  Yellow = 0x2,
  Green = 0x4,
  YellowRed = Red | Yelow
}
~~~

### Solution

Use the filtered_range and pass a predicate that specifies all valid states.

~~~C++
auto yellowStates = [](TrafficLightStates s) { 
  return (s & TrafficLightStates::Yellow) != 0;
}

for (auto state : enum_extend::FilteredRange<TrafficLightStates>(yellowStates)) {
  // iterates over Yellow and YellowRed
}
~~~

## Incrementing And Decrementing An Enumerated Value
### Problem

For incrementation and decrementation of enumerated value one has to implement the necessary operators. If the enumerated values are not contiguous, this is pretty annoying.

### Solution

Inside the operator implementations, delegate everything to the extender<T>::increment and extender<T>::decrement functions. For further details see above.

## Getting A Textual Representation Of An Enumerated Value 
### Problem

Often it happens that one needs a textual representation for each enumerated value.

### Solution

Specialize the extender not only with the enumerated type, but as well with an attached type, e.g. const char*.

~~~C++
enum class Gray
{
  DarkGray, MidGray, LightGray
};

template <>
enum_extend::extender<Gray, const char*>::instances 
  enum_extend::extender<Gray, const char*>::s_instances = {
    std::make_tuple( Gray::DarkGray, "DarkGray" ), 
    std::make_tuple( Gray::MidGray, "MidGray" ), 
    std::make_tuple( Gray::LightGray, "LightGray" ) 
  };
~~~

Now it is possible to do:

~~~C++
std::cout << enum_extend::extender<Gray, const char*>::to_decoration<const char*>(Gray::MidGray) << std::endl;
~~~

## Binding Several Decorations Onto A Single Enumerated Value
### Problem

Sometimes it is necessary to have multiple associated types to a single enumerated value, like one textual representation for logging and one for display to the user.

### Solution

Bind more types to the enum like:

~~~C++
enum class Gray
{
  DarkGray, MidGray, LightGray
};

using DecoratedGray = enum_extend::extender<Gray, const char*, TranslatedText>;

template <>
DecoratedGray::instances DecoratedGray::s_instances = {
    std::make_tuple( Gray::DarkGray, "DarkGray", TranslatedString("Dark Gray")) ), 
    std::make_tuple( Gray::MidGray, "MidGray", TranslatedString("Mid Gray")) ), 
    std::make_tuple( Gray::LightGray, TranslatedString("Light Gray") ) 
  };
~~~

Now one could access each associated type with:

~~~C++

widget->setText( DecoratedGray::to_decoration<TranslatedText>(Gray::MidGray).text() );
~~~