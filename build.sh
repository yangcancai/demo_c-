git submodule update --init --recursive
cmake -S . -B build  -G "CodeBlocks - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug && cd build && make clean && make all && ./debug_dead_lock
