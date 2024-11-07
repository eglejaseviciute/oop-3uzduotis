cmake -DCMAKE_BUILD_TYPE=Release .
cmake --install . --config Release
cmake --build . --config Release

./v1.0_list

echo "Script finished. Press enter to close."
read