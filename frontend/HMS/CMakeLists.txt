cmake_minimum_required(VERSION 3.19)
project(HMS LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)

qt_standard_project_setup()

qt_add_executable(HMS
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    ../../Login.cpp
    ../../Login.h
)

qt_add_translations(
    TARGETS HMS
    TS_FILES HMS_en_GB.ts
)

target_link_libraries(HMS
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS HMS
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET HMS
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
