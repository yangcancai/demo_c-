project(NFServer VERSION 1.0)
aux_source_directory(ThreadPool ThreadPoolSrc)
aux_source_directory(. Src)
aux_source_directory(NFKernel NFKernelSrc)
aux_source_directory(Example ExampleSrc)
include_directories(${PROJECT_SOURCE_DIR})
#target_include_directories(NFServer PUBLIC
#        "${PROJECT_SOURCE_DIR}")
add_executable(
        NFServer
        ${ThreadPoolSrc}
        ${Src}
        ${ExampleSrc}
        ${NFKernelSrc}
)
if(WIN32)
else()
target_link_libraries(NFServer
  pthread)
endif()

