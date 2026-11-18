cmake_minimum_required(VERSION 3.16)
project(QtViewerDicom LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Habilita a geração automática do MOC do Qt (Corrige o erro do vtable)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
find_package(DCMTK REQUIRED)

add_executable(QtViewerDicom
    main.cpp
    MainWindow.h
    MainWindow.cpp
    DicomLoader.h
    DicomLoader.cpp
)

target_link_libraries(QtViewerDicom PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    dcmdata
    dcmimgle
    dcmimage
    dcmjpeg
    oflog
    ofstd
    pthread
)
