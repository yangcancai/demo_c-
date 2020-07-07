git submodule update --init --recursive
cmake -S . -B build/linux  -G "CodeBlocks - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug && cd build/linux && make clean && make all && ./debug_dead_lock
