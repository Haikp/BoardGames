#include <iostream>
  
int main()
{
    for (int i = 0; i < 3;)
    {
        for (int j = 0; j < 3; j++, i++)
        {
            std::cout << i << " " << j << std::endl;
        }
    }
}