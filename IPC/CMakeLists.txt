aux_source_directory(SharedMemory SharedMemorySrc)

##UNIX : is TRUE on all UNIX-like OS's, including Apple OS X and
#CygWin
#
#
#WIN32 : is TRUE on Windows. Prior to 2.8.4 this included CygWin
#
#
#APPLE : is TRUE on Apple systems. Note this does not imply the
#system is Mac OS X, only that APPLE is #defined in C/C++
#header files.
#
#MINGW : is TRUE when using the MinGW compiler in Windows
#
#MSYS : is TRUE when using the MSYS developer environment in Windows
#
#CYGWIN : is TRUE on Windows when using the CygWin version of cmake
if(CYGWIN)
set(BOOST_ROOT /cygdrive/h/cam/c++/boost_1_73_0)
else()
## for WIN32 : setx BOOT H:/cam/c++/boost_1_73_0
## for Linux: write BOOT environment to ~/.bash_profile and then source ~/.bash_profile
set(BOOST_ROOT $ENV{BOOST})
endif()
set( Boost_USE_STATIC_LIBS ON )
set( Boost_USE_MULTITHREADED ON )
find_package(BOOST 1.73.0 COMPONENTS thread)
if(Boost_FOUND)
    message(Boost_INCLUDE_DIRS " ${Boost_INCLUDE_DIRS}")
    message(Boost_LIBRARY_DIRS " ${Boost_LIBRARY_DIRS}")
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif()
add_executable(shared_memory
        ${SharedMemorySrc})
