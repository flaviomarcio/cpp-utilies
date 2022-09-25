cmake_minimum_required(VERSION 3.16)

project(dirUtilities VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

qt_add_executable(appdirUtilities
    main.cpp
    settings.h
    settings.cpp
    search_model.h
    search_model.cpp
    search_model_settings.h
    search_model_settings.cpp
    search_qt_lib_model.h
    search_qt_lib_model.cpp
    search_qt_lib_model_setting.h
    search_qt_lib_model_setting.cpp

)

qt_add_qml_module(appdirUtilities
    URI dirUtilities
    VERSION 1.0
    QML_FILES main.qml UtilFiles.qml UtilQt.qml
)

set_target_properties(appdirUtilities PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appdirUtilities
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appdirUtilities
    PRIVATE Qt6::Quick)
