set(header_list
   ${header_list}
   ${CMAKE_CURRENT_SOURCE_DIR}/cc2sm.h
   ${CMAKE_CURRENT_SOURCE_DIR}/copy.h
   ${CMAKE_CURRENT_SOURCE_DIR}/my_point_types.h
   ${CMAKE_CURRENT_SOURCE_DIR}/PCLCloud.h
   ${CMAKE_CURRENT_SOURCE_DIR}/PCLConv.h
   ${CMAKE_CURRENT_SOURCE_DIR}/sm2cc.h
   PARENT_SCOPE
)

set(source_list
   ${source_list}
   ${CMAKE_CURRENT_SOURCE_DIR}/cc2sm.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/copy.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/sm2cc.cpp
   PARENT_SCOPE
)


