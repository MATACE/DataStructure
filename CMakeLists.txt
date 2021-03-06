#
# For x64 compile, please use command
# cmake -DCMAKE_BUILD_TYPE=Debug ..
# For arm cross compile, please use command
# For Debug Version
# cmake -DPLATFORM=arm -DCMAKE_BUILD_TYPE=Debug ..
# For Release Version
# cmake -DPLATFORM=arm -DCMAKE_BUILD_TYPE=Release ..
# make -j4 && make install
#

cmake_minimum_required (VERSION 3.5)

option(BUILD_SHARED_LIBS "Build the project shared library" OFF)
option(SET_OUTPUT_FILE_PATH "Set the bin output file paht" OFF)
option(SET_LIB_OUTPUT_PATH "Set the lib output path" OFF)

option(BUILD_LIST "Build the client" OFF)
option(C_CLASS "Build the c class" ON)

# Set project name.
project(pro)

# Set C and C++ build version.
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

# Set the library version.
if(BUILD_SHARED_LIBS)
    set(VERSION_MAJOR 1)
    set(VERSION_MINOR 0)
    set(VERSION_PATCH 0)

    configure_file (
        "${CMAKE_CURRENT_LIST_DIR}/version/version.h.in"
        "${CMAKE_CURRENT_LIST_DIR}/version/version.h"
        )
    include_directories(${CMAKE_CURRENT_LIST_DIR}/version)
endif(BUILD_SHARED_LIBS)

# Set the bin output file.
if(SET_OUTPUT_FILE_PATH)
    SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
        CACHE PATH
        ""
    )

    SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/bin
        CACHE PATH
        ""
    )

    SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
        CACHE PATH
        ""
    )
endif(SET_OUTPUT_FILE_PATH)

# # Set the lib output path
# if(SET_LIB_OUTPUT_PATH)
#     set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/build/libs/lib)
#     file(GLOB_RECURSE ALL_HEARD_FILE ${CMAKE_CURRENT_LIST_DIR}/include/*.h)
#     file(COPY ${ALL_HEARD_FILE} DESTINATION ${CMAKE_CURRENT_LIST_DIR}/build/libs/include)
# endif()

# Set the build type: Debug or Release
if (CMAKE_BUILD_TYPE MATCHES "Debug" OR CMAKE_BUILD_TYPE MATCHES "None")
    MESSAGE(STATUS "CMAKE_BUILD_TYPE is Debug")
    set(CMAKE_BUILD_GLOG_LOG_LEVEL "INFO")
    set(CMAKE_BUILD_DEBUG_INFO "DEBUG_INFO_OPEN")
else()
    MESSAGE(STATUS "CMAKE_BUILD_TYPE is Release")
    set(CMAKE_BUILD_GLOG_LOG_LEVEL "ERROR")
    set(CMAKE_BUILD_DEBUG_INFO "DEBUG_INFO_CLOSE")
endif()

# Set the Debug Info Head Name.
set(CMAKE_BUILD_DEBUG_INFO_HEAD "Pro Info")

configure_file(
    "${CMAKE_CURRENT_LIST_DIR}/macro/cmake_build_macro.h.in"
    "${CMAKE_CURRENT_LIST_DIR}/macro/cmake_build_macro.h"
)
include_directories(${CMAKE_CURRENT_LIST_DIR}/macro)

# Set build tool flag
if (PLATFORM MATCHES "arm")
    set(CMAKE_SYSTEM_NAME Linux)
    set(CMAKE_SYSTEM_PROCESSOR arm)

    # Set the build cross tool.
    set(CMAKE_CXX_COMPILER /opt/arm-2014.05/bin/arm-none-linux-gnueabi-g++)
    set(CMAKE_C_COMPILER   /opt/arm-2014.05/bin/arm-none-linux-gnueabi-gcc)

    # Set the C or C++ cross tool build flag.
    set(GNU_CXX_FLAGS "-mfpu=vfp -fPIC -g -W -O2 -std=c++11")
    set(GNU_C_FLAGS "-mfpu=vfp -fPIC -g -W -O2 -std=c99")
    set(CMAKE_CXX_FLAGS "${GNU_CXX_FLAGS}")
    set(CMAKE_C_FLAGS   "${GNU_C_FLAGS}")

else()
    set(GNU_CXX_FLAGS "-DCOM_X64 -g -W -std=c++11")
    set(GNU_C_FLAGS "-DCOM_X64 -g -W -std=c99")
    set(CMAKE_CXX_FLAGS "${GNU_CXX_FLAGS}")
    set(CMAKE_C_FLAGS   "${GNU_C_FLAGS}")

endif()

if (BUILD_LIST)
    message("Build the list")

    if (PLATFORM MATCHES "arm")
        # Include the third use libs. 
        include_directories(${CMAKE_CURRENT_LIST_DIR}/libs/arm/zlog/include)
        link_directories(${CMAKE_CURRENT_LIST_DIR}/libs/arm/zlog/lib)

        # Include the project src code.
        include_directories(${CMAKE_CURRENT_LIST_DIR}/include/list)
        include_directories(${CMAKE_CURRENT_LIST_DIR}/include/zlog)
        aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src/list LIST_SRC)
        aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src/zlog LIST_SRC)

    else()
        # Include the third use libs. 
        include_directories(${CMAKE_CURRENT_LIST_DIR}/libs/x64/zlog/include)
        link_directories(${CMAKE_CURRENT_LIST_DIR}/libs/x64/zlog/lib)

        # Include the project src code.
        include_directories(${CMAKE_CURRENT_LIST_DIR}/include/list)
        include_directories(${CMAKE_CURRENT_LIST_DIR}/include/zlog)
        aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src/list LIST_SRC)
        aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src/zlog LIST_SRC)

    endif()
endif()


if (BUILD_LIST)
    if (BUILD_SHARED_LIBS)
        add_library(list SHARED ${LIST_SRC})

        if (PLATFORM MATCHES "arm")
            target_link_libraries(list dl pthread rt
                ${CMAKE_CURRENT_LIST_DIR}/libs/arm/zlog/lib/libzlog.a)
        else()
            target_link_libraries(list dl pthread rt
                ${CMAKE_CURRENT_LIST_DIR}/libs/x64/zlog/lib/libzlog.a)
        endif()
        # Set C target
        set_property(TARGET list PROPERTY C_STANDARD 99)
        set_property(TARGET list PROPERTY C_STANDARD_REQUIRED ON)

        set_target_properties(list
            PROPERTIES
                SOVERSION ${VERSION_MAJOR}
                VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
            )
        
    else()

        add_library(list STATIC ${LIST_SRC})
        
        if (PLATFORM MATCHES "arm")
            target_link_libraries(list dl pthread rt
                ${CMAKE_CURRENT_LIST_DIR}/libs/arm/zlog/lib/libzlog.a)
        else()
            target_link_libraries(list dl pthread rt
                ${CMAKE_CURRENT_LIST_DIR}/libs/x64/zlog/lib/libzlog.a)
        endif()

        # Set C target
        set_property(TARGET list PROPERTY C_STANDARD 99)
        set_property(TARGET list PROPERTY C_STANDARD_REQUIRED ON)
    endif()
    
endif()


if (C_CLASS)
    message("Build the list")

    if (PLATFORM MATCHES "arm")
        # Include the third use libs. 
        include_directories(${CMAKE_CURRENT_LIST_DIR}/libs/arm/zlog/include)
        link_directories(${CMAKE_CURRENT_LIST_DIR}/libs/arm/zlog/lib)

        # Include the project src code.
        include_directories(${CMAKE_CURRENT_LIST_DIR}/include/class)
        include_directories(${CMAKE_CURRENT_LIST_DIR}/include/zlog)
        aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src/list CLASS_SRC)
        aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src/zlog CLASS_SRC)

    else()
        # Include the third use libs. 
        include_directories(${CMAKE_CURRENT_LIST_DIR}/libs/x64/zlog/include)
        link_directories(${CMAKE_CURRENT_LIST_DIR}/libs/x64/zlog/lib)

        # Include the project src code.
        include_directories(${CMAKE_CURRENT_LIST_DIR}/include/class)
        include_directories(${CMAKE_CURRENT_LIST_DIR}/include/zlog)
        aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src/class CLASS_SRC)
        aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src/zlog CLASS_SRC)

    endif()
endif()


if (C_CLASS)
    if (BUILD_SHARED_LIBS)
        add_library(class SHARED ${CLASS_SRC})

        if (PLATFORM MATCHES "arm")
            target_link_libraries(class dl pthread rt
                ${CMAKE_CURRENT_LIST_DIR}/libs/arm/zlog/lib/libzlog.a)
        else()
            target_link_libraries(class dl pthread rt
                ${CMAKE_CURRENT_LIST_DIR}/libs/x64/zlog/lib/libzlog.a)
        endif()
        # Set C target
        set_property(TARGET class PROPERTY C_STANDARD 99)
        set_property(TARGET class PROPERTY C_STANDARD_REQUIRED ON)

        set_target_properties(class
            PROPERTIES
                SOVERSION ${VERSION_MAJOR}
                VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
            )
        
    else()

        add_library(class STATIC ${CLASS_SRC})
        
        if (PLATFORM MATCHES "arm")
            target_link_libraries(class dl pthread rt
                ${CMAKE_CURRENT_LIST_DIR}/libs/arm/zlog/lib/libzlog.a)
        else()
            target_link_libraries(class dl pthread rt
                ${CMAKE_CURRENT_LIST_DIR}/libs/x64/zlog/lib/libzlog.a)
        endif()

        # Set C target
        set_property(TARGET class PROPERTY C_STANDARD 99)
        set_property(TARGET class PROPERTY C_STANDARD_REQUIRED ON)
    endif()
    
endif()


