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
  ../enum_extend/declare_decorated_enum.hpp
  ../enum_extend/decoration_range.hpp
  ../enum_extend/define_decorated_enum.hpp
  ../enum_extend/define_enum.hpp
  ../enum_extend/enum_range.hpp
  ../enum_extend/extender.hpp
  ../enum_extend/filtered_range.hpp
  ../enum_extend/range.hpp
  ../enum_extend/internal/compiler_support.hpp
  ../enum_extend/internal/declare_operators_helpers.hpp
  ../enum_extend/internal/define_enum_helper.hpp
  ../enum_extend/internal/define_operators_helpers.hpp
  ../enum_extend/internal/error_handling.hpp
  ../enum_extend/internal/helper_structs.hpp
  ../enum_extend/internal/pp_create_seq_from_1st_tuple2.hpp
  ../enum_extend/internal/pp_create_seq_from_1st_tuple3.hpp
  ../enum_extend/internal/pp_create_seq_from_tuple2_seq.hpp
  ../enum_extend/internal/pp_create_seq_from_tuple3_seq.hpp
  ../enum_extend/internal/pp_helper.hpp
  ../enum_extend/internal/tupple_helper.hpp
)

include_directories(${Boost_INCLUDE_DIRS})

add_library(enum_extend ${SOURCE} ${HEADERS})