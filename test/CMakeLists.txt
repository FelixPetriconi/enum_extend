project(enum_extend_test)

if(WIN32)
  add_definitions(-D_WIN32_WINNT=0x0501 -D_SCL_SECURE_NO_WARNINGS)
ENDIF(WIN32)

# Visual Studio 2012 only supports up to 8 template parameters in
# std::tr1::tuple by default, but gtest requires 10
if(MSVC AND MSVC_VERSION EQUAL 1700)
  add_definitions(-D_VARIADIC_MAX=10)
endif ()


include_directories("${PROJECT_SOURCE_DIR}/..")
include_directories("${PROJECT_SOURCE_DIR}/../tools/gtest-1.7.0/include")
include_directories(${Boost_INCLUDE_DIRS})

set(HEADERS
)

set(SOURCE
  enum_extend_filtered_range_test.cpp
  enum_extend_test.cpp
  enum_extend_with_decoration_test.cpp
  enum_extend_test_helper.hpp
  main.cpp
)

add_executable(enum_extend_test ${SOURCE} ${HEADERS})

add_dependencies(enum_extend_test gtest)
add_dependencies(enum_extend_test enum_extend)
target_link_libraries(enum_extend_test gtest enum_extend)
