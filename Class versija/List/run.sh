cmake -DCMAKE_BUILD_TYPE=Release .
cmake --build . --config Release

echo "Performance Measurements:"
for opt in O1 O2 O3; do
    echo "Optimization Level: $opt"
    time ./List_${opt}
done

echo "Experiment completed. Press enter to close."
read