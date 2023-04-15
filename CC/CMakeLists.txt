cmake_minimum_required(VERSION 3.0)

# to compile CCLib only! (CMake implicitly imposes to declare a project before anything...)
project( CC_CORE_LIB )

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

	# find qt5 components
# find_package(Qt5 COMPONENTS OpenGL Widgets Core Gui PrintSupport Concurrent REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5Concurrent REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5OpenGLExtensions REQUIRED)
find_package(Qt5Svg REQUIRED)

# ScalarType as float (default) or double
option( OPTION_SCALAR_DOUBLE "Check to define ScalarType as double" OFF )

if ( OPTION_SCALAR_DOUBLE )
	add_definitions( -DSCALAR_TYPE_DOUBLE )
	set (USE_SCALAR_TYPE_DOUBLE ON PARENT_SCOPE)
else()
	add_definitions( -DSCALAR_TYPE_FLOAT )
endif()

if (COMPILE_CC_CORE_LIB_WITH_CGAL)
	include( cmake/CGALSupport.cmake )
endif()

if (COMPILE_CC_CORE_LIB_WITH_TBB)
	include( cmake/FindTBB.cmake )
else()
	if (NOT WIN32)
		message( WARNING "CCLib configured without parallel algorithm capabilities - see COMPILE_CC_CORE_LIB_WITH_TBB" )
	endif()
endif()

# Additional dependencies (only Qt in fact)
if (COMPILE_CC_CORE_LIB_WITH_QT)
	#include( CMakeExternalLibs )
endif()

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include )

file( GLOB header_list include/*.h)
file( GLOB source_list src/*.cpp src/*.h)

if ( WIN32 )
	# Add Qt5 natvis file
	if ( COMPILE_CC_CORE_LIB_WITH_QT )
		list( APPEND header_list ${CMAKE_CURRENT_SOURCE_DIR}/../scripts/windows/qt5.natvis )
		#message(${header_list})
	endif()
endif()

#if (COMPILE_CC_CORE_LIB_SHARED)
if (FALSE)
	#set( CMAKE_CXX_VISIBILITY_PRESET hidden )
	#set( CMAKE_VISIBILITY_INLINES_HIDDEN 1 )
	
	add_library( ${PROJECT_NAME} SHARED ${header_list} ${source_list} )

# Qt
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::OpenGL)

# Add custom preprocessor definitions
target_compile_definitions( ${PROJECT_NAME} PRIVATE QCC_DB_LIBRARY_BUILD )

else()
	add_library( ${PROJECT_NAME} STATIC ${header_list} ${source_list} )
	
	target_compile_definitions( ${PROJECT_NAME} PRIVATE CC_CORE_LIB_STATIC_DEFINE )	
endif()

# generate the export header file
include( GenerateExportHeader )

generate_export_header( ${PROJECT_NAME}
	EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/include/CCCoreLibExport.h
	EXPORT_MACRO_NAME CC_CORE_LIB_API
)