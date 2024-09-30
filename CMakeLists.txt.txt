cmake_minimum_required(VERSION 3.29)
project(url_downloader)

set(CMAKE_CXX_STANDARD 17)

set(CURL_INCLUDE_DIR "C:/vcpkg/vcpkg/installed/x64-windows/include")
set(CURL_LIBRARY "C:/vcpkg/vcpkg/installed/x64-windows/lib/libcurl.lib")
set(ZLIB_INCLUDE_DIR "C:/vcpkg/vcpkg/installed/x64-windows/include")
set(ZLIB_LIBRARY "C:/vcpkg/vcpkg/installed/x64-windows/lib/zlib.lib")
set(MAIN_CPP "C:/url_downloader/dido/src/main.cpp")
set(DOWNLOADER_CPP "C:/url_downloader/dido/src/downloader.cpp")

find_package(CURL REQUIRED)

include_directories(${CURL_INCLUDE_DIR})
include_directories(${ZLIB_INCLUDE_DIR})
include_directories(C:/url_downloader/dido/src)

add_executable(url_downloader ${MAIN_CPP} ${DOWNLOADER_CPP})

target_link_libraries(url_downloader PRIVATE ${CURL_LIBRARY} ${ZLIB_LIBRARY})
