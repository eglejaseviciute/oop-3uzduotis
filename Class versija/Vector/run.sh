cmake -DCMAKE_BUILD_TYPE=Release .
cmake --build . --config Release


echo "Executable Sizes:"
ls -lh v1.0_vector_O1 v1.0_vector_O2 v1.0_vector_O3

echo "Performance Measurements:"
for opt in O1 O2 O3; do
    echo "Optimization Level: $opt"
    time ./v1.0_vector_${opt}
done

echo "Experiment completed. Press enter to close."
read