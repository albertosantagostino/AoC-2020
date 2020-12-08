#include <iostream>

#include <boot_code.h>

using bootcode::BootCode;

bool ExecuteProgram(BootCode bc)
{
    while (true)
    {
        if (bc.CheckTouched(bc.GetIdx()) == 1U)
        {
            return false;
        }
        else if (bc.GetIdx() >= bc.GetProgram().size())
        {
            std::cout << bc.GetAccumulator() << std::endl;
            return true;
        }
        else
        {
            bc.StepProgram();
        }
    }
}

int main()
{
    // Load data
    std::ifstream fp("data/day08.txt");
    BootCode bc(fp);
    bool res{false};
    // Try to execute the program changing every jmp/nop one-by-one
    // Brute force approach
    for (std::size_t i = 0U; ((i < bc.GetProgramSize()) && !res); ++i)
    {
        if (bc.GetInstruction(i).first == "jmp")
        {
            bc.ChangeInstruction(i, "nop");
            res = ExecuteProgram(bc);
            bc.ChangeInstruction(i, "jmp");
        }
        else if (bc.GetInstruction(i).first == "nop")
        {
            bc.ChangeInstruction(i, "jmp");
            res = ExecuteProgram(bc);
            bc.ChangeInstruction(i, "nop");
        }
    }

    return EXIT_SUCCESS;
}
