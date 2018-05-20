cmake_minimum_required(VERSION 3.10)
project(certman)

set(CMAKE_CXX_STANDARD 17)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/resources)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

# Tell CMake to create the helloworld executable
add_executable(certman src/main.cpp src/mainwindow.cpp src/cert/Certificate.cpp src/cert/Certificate.h src/cert/CertificateList.cpp src/cert/CertificateList.h src/cert/CertificateManager.cpp src/cert/CertificateManager.h src/gui/Assistant.cpp src/gui/Assistant.h src/gui/ExportAssistant.cpp src/gui/ExportAssistant.h src/gui/ImportAssistant.cpp src/gui/ImportAssistant.h src/gui/PKIAssistant.cpp src/gui/PKIAssistant.h src/gui/CertificateAssistant.cpp src/gui/CertificateAssistant.h src/gui/CertificateDetail.cpp src/gui/CertificateDetail.h src/gui/CertificatesList.cpp src/gui/CertificatesList.h src/core/Application.cpp src/core/Application.h src/core/Environment.cpp src/core/Environment.h)

# Use the Widgets module from Qt 5.
target_link_libraries(certman Qt5::Widgets)