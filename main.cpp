
#include <iostream>



int main(int argc, char* argv[])
{
    std::cout << "Hello World!" << std::endl;
std::cout << "Mängden argument" << argc << std::endl;
for(int i = 0; i < argc; i++)
{
    std::cout << "Argumentet: " << argv[i] << std::endl;
}




return 0;
}