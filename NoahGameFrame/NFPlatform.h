//
// Created by Administrator on 2020/6/28.
//

#ifndef DEBUG_DEAD_LOCK_NFPLATFORM_H
#define DEBUG_DEAD_LOCK_NFPLATFORM_H
#include <iostream>
#include <functional>
#include <map>
#include <memory>
#include <chrono>
#include <thread>
#include <vector>
// Integer formats of fixed bit width
typedef uint32_t NFUINT32;
typedef uint16_t NFUINT16;
typedef uint8_t NFUINT8;
typedef int32_t NFINT32;
typedef int16_t NFINT16;
typedef int8_t NFINT8;
typedef uint64_t NFUINT64;
typedef int64_t NFINT64;
typedef int64_t NFSOCK;


#define NF_PLATFORM_WIN 1
#define NF_PLATFORM_LINUX 2
#define NF_PLATFORM_APPLE 3
#define NF_PLATFORM_SYMBIAN 4
#define NF_PLATFORM_APPLE_IOS 5
#define NF_PLATFORM_ANDROID 6

#define NF_COMPILER_MSVC 1
#define NF_COMPILER_GNUC 2
#define NF_COMPILER_BORL 3
#define NF_COMPILER_WINSCW 4
#define NF_COMPILER_GCCE 5

#define NF_ENDIAN_LITTLE 1
#define NF_ENDIAN_BIG 2

/* Finds the current platform */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined( __WIN32__ ) || defined( _WIN32 ) || defined(_WINDOWS) || defined(WIN) || defined(_WIN64) || defined( __WIN64__ )
#   define NF_PLATFORM NF_PLATFORM_WIN
//////////////////////////////////////////////////////////////////////////
#elif defined( __APPLE_CC__) || defined(__APPLE__) || defined(__OSX__)
// Device                                                     Simulator
// Both requiring OS version 4.0 or greater
#   if __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ >= 40000 || __IPHONE_OS_VERSION_MIN_REQUIRED >= 40000
#       define NF_PLATFORM NF_PLATFORM_APPLE_IOS
#   else
#       define NF_PLATFORM NF_PLATFORM_APPLE
#   endif
//////////////////////////////////////////////////////////////////////////
#elif defined(linux) && defined(__arm__)
// TODO: This is NOT the correct way to detect the Tegra 2 platform but it works for now.
// It doesn't appear that GCC defines any platform specific macros.
#   define NF_PLATFORM NF_PLATFORM_TEGRA2
#elif defined(__ANDROID__)
#   define NF_PLATFORM NF_PLATFORM_ANDROID
//////////////////////////////////////////////////////////////////////////
#elif defined( __native_client__ )
#   define NF_PLATFORM NF_PLATFORM_NACL
#   ifndef NF_STATIC_LIB
#       error NF must be built as static for NaCl (NF_STATIC=true in cmake)
#   endif
#   ifdef NF_BUILD_RENDERSYSTEM_D3D9
#       error d3d9 is nor supported on NaCl (ONF_BUILD_RENDERSYSTEM_D3D9 false in cmake)
#   endif
#   ifdef NF_BUILD_RENDERSYSTEM_GL
#       error gl is nor supported on NaCl (ONF_BUILD_RENDERSYSTEM_GL=false in cmake)
#   endif
#   ifndef NF_BUILD_RENDERSYSTEM_GLES2
#       error GLES2 render system is needed for NaCl (ONF_BUILD_RENDERSYSTEM_GLES2=false in cmake)
#   endif
#else
#   define NF_PLATFORM NF_PLATFORM_LINUX
#endif


#define NF_SHARED_PTR std::shared_ptr
#define NF_NEW new
#define GET_CLASS_NAME(class) #class
#endif //DEBUG_DEAD_LOCK_NFPLATFORM_H
