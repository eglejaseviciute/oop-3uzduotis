cmake -DCMAKE_BUILD_TYPE=Release .
cmake --install . --config Release
cmake --build . --config Release

./List

echo "Script finished. Press enter to close."
read
