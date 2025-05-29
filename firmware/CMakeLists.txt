add_library(microcyphal INTERFACE) # TODO static?
target_include_directories(microcyphal INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
# platformify(microcyphal)

file(GLOB_RECURSE headers CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/**/*.hpp
)

target_sources(microcyphal INTERFACE ${FTL_HEADERS})
target_link_libraries(microcyphal INTERFACE ftl)
