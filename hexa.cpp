#include <iostream>
#include <fstream>
int main()
{
    std::ifstream f("prova.raw");
    f.seekg(15);
    unsigned char b;
    f >> b;
    std::cout << std::hex << +b << '\n';
}
