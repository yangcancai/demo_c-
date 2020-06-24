cmake -S . -B cmake-build-debug  -G "CodeBlocks - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug && cd cmake-build-debug && make clean && make all && ./debug_dead_lock
