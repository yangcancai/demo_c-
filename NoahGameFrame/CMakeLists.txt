aux_source_directory(ThreadPool ThreadPoolSrc)
aux_source_directory(. Src)
aux_source_directory(NFKernel NFKernelSrc)
aux_source_directory(Example ExampleSrc)
add_executable(
        NFServer
        ${ThreadPoolSrc}
        ${Src}
        ${ExampleSrc}
        ${NFKernelSrc}
)
target_link_libraries(NFServer
  pthread)
