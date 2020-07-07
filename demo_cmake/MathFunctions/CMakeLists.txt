## 增加一个MathFunctions.lib库
add_library(MathFunctions mysqrt.cpp)
## 项目跟目录作为include
target_include_directories(MathFunctions PUBLIC
        "${PROJECT_SOURCE_DIR}")
## 链接common
target_link_libraries(MathFunctions
        common)

install(TARGETS MathFunctions DESTINATION lib)
install(FILES MathFunctions.h
        DESTINATION include)