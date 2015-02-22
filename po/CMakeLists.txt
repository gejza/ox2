
file(GLOB POT_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../src/*.cpp)
file(WRITE POTFILES.in "")

foreach(pot_file ${POT_FILES})
  file(APPEND POTFILES.in "${pot_file}\n")
endforeach(pot_file)

#foreach(pot_file ${POT_FILES})
  # here replace / for linux and \ for windows
#  string(REPLACE "/" "_" header_path header) 
#  string(TOUPPER header_path final_header_path)
#  file(APPEND POTFILES.in define 
#    PATH_${final_header_path} ${CMAKE_CURRENT_SOURCE_DIR}/header)
#endforeach(header)

GettextTranslate()
