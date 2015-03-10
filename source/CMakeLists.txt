project(enum_extend)

include_directories("${PROJECT_SOURCE_DIR}/../enum_extend")

if(WIN32)
  add_definitions(-D_WIN32_WINNT=0x0501)
endif(WIN32)

set(SOURCE
  dummy.cpp
)

set(HEADERS
  ../enum_extend/decoration_range.hpp
  ../enum_extend/enum_range.hpp
  ../enum_extend/enum_decorator.hpp
  ../enum_extend/extender.hpp
  ../enum_extend/filtered_range.hpp
  ../enum_extend/range.hpp
  ../enum_extend/internal/error_handling.hpp
  ../enum_extend/internal/helper_structs.hpp
)

include_directories(${Boost_INCLUDE_DIRS})

add_library(enum_extend ${SOURCE} ${HEADERS})