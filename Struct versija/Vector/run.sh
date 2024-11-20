cmake -DCMAKE_BUILD_TYPE=Release .
cmake --build . --config Release

echo "Executable Sizes:"
ls -lh Vector_O1 Vector_O2 Vector_O3

echo "Performance Measurements:"
for opt in O1 O2 O3; do
    echo "Optimization Level: $opt"
    time ./Vector_${opt}
done

echo "Experiment completed. Press enter to close."
read
