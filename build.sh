cmake -S . -B cmake-build-debug  -G "CodeBlocks - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug && cd build && make clean && make all && ./debug_dead_lock
