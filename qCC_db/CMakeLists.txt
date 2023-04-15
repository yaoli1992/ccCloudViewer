cmake_minimum_required(VERSION 3.0)

project( QCC_DB_LIB )
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Core Gui Widgets OpenGL OpenGLExtensions REQUIRED)

include_directories( ${CC_CORE_LIB_SOURCE_DIR}/include )
include_directories( ${CC_FBO_LIB_SOURCE_DIR}/include )

include_directories(${QCC_DB_LIB_SOURCE_DIR})
message(${QCC_DB_LIB_SOURCE_DIR})

file( GLOB header_list *.h)
file( GLOB source_list *.cpp)


#QT5_WRAP_CPP(ccPointCloudLOD_MOC ccPointCloudLOD.h)

#add_library(my_widget ${SOURCES} ${MY_WIDGET_MOC})

#file( GLOB ui_list ../common/ui_templates/*.ui )

#set( CMAKE_CXX_VISIBILITY_PRESET hidden )

#qt5_wrap_ui( generated_ui_list ${ui_list} )


add_library( ${PROJECT_NAME} SHARED ${header_list} ${source_list} ${generated_ui_list})

target_link_libraries( ${PROJECT_NAME}
	CC_CORE_LIB
	CC_FBO_LIB 
	
	)

# Qt
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::OpenGL)

# Add custom preprocessor definitions
target_compile_definitions( ${PROJECT_NAME} PRIVATE QCC_DB_LIBRARY_BUILD )
