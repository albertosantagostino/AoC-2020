#include <iostream>

#include <boot_code.h>

using bootcode::BootCode;

int main()
{
    // Load data
    std::ifstream fp("data/day08.txt");
    BootCode bc(fp);

    while(true)
    {
        if(bc.CheckTouched(bc.GetIdx()) == 1U)
        {
            break;
        }
        else
        {
            bc.StepProgram();
        }
    }

    std::cout << bc.GetAccumulator() << std::endl;

    return EXIT_SUCCESS;
}
