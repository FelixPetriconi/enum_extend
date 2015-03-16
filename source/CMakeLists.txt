project(enum_extend)

include_directories("${PROJECT_SOURCE_DIR}/../enum_extend")

if(WIN32)
  add_definitions(-D_WIN32_WINNT=0x0501)
endif(WIN32)

set(SOURCE
  dummy.cpp
)

set(HEADERS
  ../enum_extend/declare_enum.hpp
  ../enum_extend/declare_enum_class.hpp
  ../enum_extend/declare_typed_enum.hpp
  ../enum_extend/declare_typed_enum_class.hpp
  ../enum_extend/decoration_range.hpp
  ../enum_extend/define_enum.hpp
  ../enum_extend/define_enum_class.hpp
  ../enum_extend/define_typed_enum.hpp
  ../enum_extend/define_typed_enum_class.hpp
  ../enum_extend/enum_range.hpp
  ../enum_extend/extender.hpp
  ../enum_extend/filtered_range.hpp
  ../enum_extend/range.hpp
  ../enum_extend/internal/declare_operators_helpers.hpp
  ../enum_extend/internal/define_enum_helper.hpp
  ../enum_extend/internal/define_operators_helpers.hpp
  ../enum_extend/internal/error_handling.hpp
  ../enum_extend/internal/helper_structs.hpp
  ../enum_extend/internal/macro_helper.hpp
  ../enum_extend/internal/tupple_helper.hpp
)

include_directories(${Boost_INCLUDE_DIRS})

add_library(enum_extend ${SOURCE} ${HEADERS})