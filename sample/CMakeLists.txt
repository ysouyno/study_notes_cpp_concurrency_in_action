file (GLOB SAMPLE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
message ("${SAMPLE}")

foreach (samplefile ${SAMPLE})
  string (REPLACE ".cpp" "" filename ${samplefile})
  add_executable (${filename} ${samplefile})
  target_link_libraries (${filename} "-pthread")
endforeach (samplefile ${SAMPLE})
