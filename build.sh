echo "-------------------------------------" 
echo "dlting old executable" && rm -rf ./a.out 
clang++ main.cpp -std=c++17 -O2 -lglfw -lvulkan -ldl -lpthread -ggdb
echo "compilation successful"
echo "-------------------------------------"

echo "running app" && ./a.out
echo "-------------------------------------"

