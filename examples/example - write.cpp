#include <iostream>
#include <lini.h>



int main()
{
    Lini test("..\\test.ini");

    if(test.Error())
    {
        //Something went wrong
        std::cout << "Couldn't create/open the file" << std::endl;
        return 1;
    }

    test.Set("Animation","Type","Animation_Name");

    test.Set_Int("Animation","Speed",25);

    test.Set_Int("Audio","Volume",100);

    test.Set_Boolean("Levels","Stage_1",true);

    test.Set_Real("Distance","Rifle",250.5);



    std::cout << "Section:" << std::endl;
    for(auto section : test.Get_Section())
    {
        std::cout << section << std::endl;
    }
    std::cout << std::endl << "Keys:" << std::endl;
    for(auto key : test.Get_Fields("Animation"))
    {
        std::cout << key << std::endl;
    }
    test.Close();

    return 0;
}