cmake_minimum_required(VERSION 3.5)
include(${CMAKE_CURRENT_LIST_DIR}/../CMakeLists.txt)

if(BUILD_LIST)
    add_executable(list_demo list_demo.c ${LIST_SRC})
    target_link_libraries(list_demo pthread rt zlog)

endif()

if(C_CLASS)
    add_executable(c_class_demo ch_class.c ${CLASS_SRC})
    target_link_libraries(c_class_demo pthread rt zlog)

endif()