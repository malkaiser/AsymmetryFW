rm -rf build install
cmake -S . -B build -DCMAKE_INSTALL_PREFIX=install
cmake --build build --target install
cd RunAnalysis/
