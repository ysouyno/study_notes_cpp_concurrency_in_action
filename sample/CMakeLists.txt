file (GLOB SAMPLE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
message ("${SAMPLE}")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")

foreach (samplefile ${SAMPLE})
  string (REPLACE ".cpp" "" filename ${samplefile})
  add_executable (${filename} ${samplefile})
  target_link_libraries (${filename} "-pthread -latomic")
endforeach (samplefile ${SAMPLE})
