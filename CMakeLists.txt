cmake_minimum_required(VERSION 3.0)
project(CloudViewer)

    set( CXX11_FLAG "-std=c++11")
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX11_FLAG} ${FPIC_FLAG}")
    set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${FPIC_FLAG}")
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

find_package(PCL 1.7 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS} include)
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

 
include_directories(${Qt5OpenGL_INCLUDE_DIRS}
                    ${Qt5Widgets_INCLUDE_DIRS}
                    ${Qt5Core_INCLUDE_DIRS}
                    ${Qt5Gui_INCLUDE_DIRS}
                    ${Qt5Concurrent_INCLUDE_DIRS}
                    ${Qt5PrintSupport_INCLUDE_DIRS}
					)

# turn on QStringBuilder for more efficient string construction
#	see https://doc.qt.io/qt-5/qstring.html#more-efficient-string-construction
add_definitions( -DQT_USE_QSTRINGBUILDER )
				
				
find_package(Qt5 COMPONENTS Core Gui Widgets OpenGL OpenGLExtensions REQUIRED)

# Libs requested by both qCC & ccViewer
add_subdirectory( ./CC )
add_subdirectory( ./common )

add_subdirectory( ./CCFbo )
add_subdirectory( ./qCC_db ) # must always be included after CCFbo (dependency)
add_subdirectory( ./qCC_io ) # must always be included after qCC_db (dependency)
add_subdirectory( ./qCC_glWindow ) # must always be included after qCC_db (dependency)
#add_subdirectory( ./plugins )


include_directories( ${CC_FBO_LIB_SOURCE_DIR}/include )
include_directories( ${CC_CORE_LIB_SOURCE_DIR}/include )
include_directories( ${QCC_DB_LIB_SOURCE_DIR} )
message(${QCC_DB_LIB_SOURCE_DIR})

if( MSVC )
   include_directories( ${QCC_DB_LIB_SOURCE_DIR}/msvc )
endif()
include_directories( ${QCC_IO_LIB_SOURCE_DIR} )
include_directories( ${QCC_GL_LIB_SOURCE_DIR} )
include_directories( ${CC_CORE_LIB_SOURCE_DIR}/inlcude )
include_directories( ${CC_CORE_LIB_SOURCE_DIR}/src )
include_directories( ${COMMON_SOURCE_DIR} )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/common)
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )
#include_directories( ${CloudComparePlugins_SOURCE_DIR} )
#MESSAGE(${CloudComparePlugins_SOURCE_DIR})

file( GLOB header_list_common  common/*.h )
file( GLOB source_list_common  common/*.cpp )

file( GLOB header_list  ccViewer/*.h )
file( GLOB source_list  ccViewer/*.cpp )

file( GLOB ui_list ccViewer/ui_templates/*.ui )
file( GLOB ui_list_common common/ui_templates/*.ui )


#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/common)

# 3DX support (3dConnexion devices)
if ( ${OPTION_SUPPORT_3DCONNEXION_DEVICES} )
	add_subdirectory( ../qCC/devices/3dConnexion devices/3dConnexion )
endif()

# Gamepad support (requires Qt 5.7+)
if ( ${OPTION_SUPPORT_GAMEPADS} )
	add_subdirectory( ../qCC/devices/gamepad devices/gamepad )
endif()

qt5_wrap_ui( generated_ui_list ${ui_list} ${ui_list_common})
qt5_add_resources( generated_qrc_list ${qrc_list} )

if( TRUE )
	# App icon with MSVC
	#set( rc_list images/icon/cc_viewer_icon.rc )

	#to get rid of the (system) console
	add_executable( ${PROJECT_NAME} WIN32 ${header_list} ${source_list} ${generated_ui_list} ${generated_qrc_list} ${rc_list}
	                                      ${header_list_common} ${source_list_common} ${ui_list_common})
elseif( APPLE )
	add_executable( ${PROJECT_NAME} MACOSX_BUNDLE ${header_list} ${source_list} ${generated_ui_list} ${generated_qrc_list} ${rc_list})
else()
	add_executable( ${PROJECT_NAME} ${header_list} ${source_list} ${generated_ui_list} ${generated_qrc_list} ${rc_list})
endif()

target_link_libraries( ${PROJECT_NAME}
	CC_FBO_LIB
	CC_CORE_LIB
	QCC_DB_LIB
	QCC_IO_LIB
	QCC_GL_LIB 
	 ${PCL_LIBRARIES}
	#QCORE_IO_PLUGIN
	)

# Qt
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::OpenGL  ${PCL_LIBRARIES})

if (WIN32)
	target_link_libraries( ${PROJECT_NAME} Qt5::WinMain  ${PCL_LIBRARIES})
endif()
