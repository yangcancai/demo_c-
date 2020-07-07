add_library(common IBase.cpp)
install(TARGETS common DESTINATION lib)
install(FILES IBase.h DESTINATION include)