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

    std::cout << test.Get("Animation","Type") << std::endl;

    std::cout << test.Get_Int("Animation","Speed") << std::endl;

    std::cout << test.Get_Int("Audio","Volume") << std::endl;

    std::cout << (test.Get_Boolean("Levels","Stage_1") ? ("True") : ("False")) << std::endl;

    std::cout << test.Get_Real("Distance","Rifle") << std::endl;


    test.Close();

    return 0;
}
