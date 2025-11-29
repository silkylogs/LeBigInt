# Build
clang -c lebigint.c -o lebigint.o -Wmost

# Test
cd Prober
bash ./build.sh
cd ..

clang test.c Prober/prober.o lebigint.o -o test.exe
./test.exe