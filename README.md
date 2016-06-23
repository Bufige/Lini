# Lini
A simple [INI Parser](http://en.wikipedia.org/wiki/INI_file) written in C++. It's made to be fast,simple,small and easy to understand.


## Simple example in C++##

```cpp
#include <iostream>
#include <lini.h>



int main()
{
    Lini test("..\\test.ini");

    test.Set("Animation","Type","Animation_Name");
    test.Set_Int("Animation","Speed",25);

    test.Set_Int("Audio","Volume",100);

    test.Set_Boolean("Levels","Stage_1",true);

    test.Set_Real("Distance","Rifle",250.5);



    std::cout << "Section:" << std::endl;
    for(auto section : test.Get_Section())
    {
        std::cout << it << std::endl;
    }
    std::cout << std::endl << "Keys:" << std::endl;
    for(auto key : test.Get_Fields("Animation"))
    {
        std::cout << key << std::endl;
    }
    test.Close();

    return 0;
}

```
