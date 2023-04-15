cmake_minimum_required(VERSION 3.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

include_directories( ${CC_CORE_LIB_SOURCE_DIR}/include )

include_directories( ${CC_FBO_LIB_SOURCE_DIR}/include )

include_directories( ${QCC_DB_LIB_SOURCE_DIR} )

if( MSVC )
   include_directories( ${QCC_DB_LIB_SOURCE_DIR}/msvc )
endif()

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

project( QCC_IO_LIB )
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


file( GLOB header_list *.h)
file( GLOB source_list *.cpp *.c)
file( GLOB ui_list ui_templates/*.ui )

set( CMAKE_CXX_VISIBILITY_PRESET hidden )

qt5_wrap_ui( generated_ui_list ${ui_list} )
add_library( ${PROJECT_NAME} SHARED ${header_list} ${source_list} ${generated_ui_list} )

target_link_libraries( ${PROJECT_NAME}
	CC_CORE_LIB
	CC_FBO_LIB
	QCC_DB_LIB )

# Qt
target_link_libraries(${PROJECT_NAME} Qt5::Core)	

target_compile_options( ${PROJECT_NAME} PRIVATE /Zc:wchar_t-)
target_compile_definitions( ${PROJECT_NAME} PRIVATE QCC_IO_LIBRARY_BUILD )
