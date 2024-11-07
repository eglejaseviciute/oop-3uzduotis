cmake -DCMAKE_BUILD_TYPE=Release .
cmake --install . --config Release
cmake --build . --config Release

./v1.0_vector

echo "Script finished. Press enter to close."
read