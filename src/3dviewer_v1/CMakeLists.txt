cmake_minimum_required(VERSION 3.5)

project(3dviewer_v1 VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



# if(NOT LINUX) should work, too, if you need that
if(APPLE)
    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS OpenGLWidgets Widgets Gui)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGLWidgets Widgets Gui)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c11 -Wall -Werror -Wextra")
else()
    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS OpenGL OpenGLExtensions Widgets Gui)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGL OpenGLExtensions Widgets Gui)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
endif()

set(PROJECT_SOURCES
        back/s21_3dviewer.h

        back/s21_parser.c
        back/s21_transformations.c

        front/s21_3dviewer.h
        front/s21_glwidget.h
        front/s21_sizes.h
        front/s21_numlineedit.h

        front/s21_3dviewer.cpp
        front/s21_glwidget.cpp
        front/s21_sizes.cpp
        front/s21_numlineedit.cpp

        front/s21_3dviewer.ui
        front/s21_sizes.ui
        
        front/QtGifImage/qgifglobal.h
        front/QtGifImage/qgifimage_p.h
        front/QtGifImage/qgifimage.cpp
        front/QtGifImage/qgifimage.h
        front/QtGifImage/quantize.c
        front/QtGifImage/gif_lib.h
        front/QtGifImage/gifalloc.c
        front/QtGifImage/gif_lib_private.h
        front/QtGifImage/gif_hash.h
        front/QtGifImage/gif_hash.c
        front/QtGifImage/gif_font.c
        front/QtGifImage/gif_err.c
        front/QtGifImage/egif_lib.c
        front/QtGifImage/dgif_lib.c

        main.cpp
        pictures.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3dviewer_v1
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        misc/icon.ico
    )
else()
    add_executable(3dviewer_v1
        ${PROJECT_SOURCES}
        misc/icon.ico
    )
endif()



target_include_directories(3dviewer_v1 PRIVATE front)
target_include_directories(3dviewer_v1 PRIVATE back)
target_include_directories(3dviewer_v1 PRIVATE front/QtGifImage)


target_include_directories(3dviewer_v1 PRIVATE "front/")
target_include_directories(3dviewer_v1 PRIVATE "front/QtGifImage")

if(APPLE)
    target_link_libraries(3dviewer_v1 PRIVATE Qt${QT_VERSION_MAJOR}::OpenGLWidgets Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Gui)
else()
    target_link_libraries(3dviewer_v1 PRIVATE Qt${QT_VERSION_MAJOR}::OpenGL Qt${QT_VERSION_MAJOR}::OpenGLExtensions Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Gui)
endif()



set_target_properties(3dviewer_v1 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE_ICON_FILE ../Resources/icon.ico
    RESOURCE misc/icon.ico
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3dviewer_v1)
endif()

