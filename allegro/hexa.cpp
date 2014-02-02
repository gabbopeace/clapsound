#include <iostream>
#include <fstream>
int main()
{
    std::ifstream f("test.bin");
    f.seekg(2);
    unsigned char b;
    f >> b;
    std::cout << std::hex << +b << '\n';
}
