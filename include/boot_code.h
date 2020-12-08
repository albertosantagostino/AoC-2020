#ifndef BOOT_CODE_H
#define BOOT_CODE_H

#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <vector>

namespace bootcode
{
typedef std::pair<std::string, int> Instruction;
typedef std::vector<Instruction> Program;
typedef std::map<std::size_t, std::size_t> TouchedRegister;

class BootCode
{
  public:
    BootCode();
    BootCode(std::ifstream& program_fp);
    BootCode(const Program program, const int accumulator);

    // Execution
    void StepProgram();

    // Setters
    void TouchInstruction(const std::size_t idx);
    inline void ChangeInstruction(const std::size_t idx, const std::string new_instruction)
    {
        m_program[idx].first = new_instruction;
    };

    // Getters
    inline Program GetProgram() { return m_program; }
    inline int GetAccumulator() { return m_accumulator; }
    inline std::size_t GetIdx() { return m_idx; }
    inline Instruction GetInstruction(std::size_t idx) { return m_program[idx]; }
    inline std::size_t GetProgramSize() { return m_program.size(); }

    // Utilities
    std::size_t CheckTouched(std::size_t idx);
    void PrintProgram();

  private:
    Program m_program;
    int m_accumulator{0U};
    std::size_t m_idx{0U};
    TouchedRegister m_touched_register;
};

BootCode::BootCode()
{}

BootCode::BootCode(std::ifstream& program_fp)
{
    std::string str;
    while (std::getline(program_fp, str))
    {
        std::istringstream iss(str);
        std::vector<std::string> words{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
        m_program.push_back({words[0], std::stoi(words[1])});
    }
}

BootCode::BootCode(const Program program, const int accumulator) : m_program(program), m_accumulator(accumulator)
{}

void BootCode::StepProgram()
{
    // Register instruction as touched
    TouchInstruction(m_idx);
    Instruction instruction{m_program[m_idx]};
    std::size_t jump_increase{1U};
    if (instruction.first == "acc")
    {
        m_accumulator += instruction.second;
    }
    else if (instruction.first == "jmp")
    {
        jump_increase = instruction.second;
    }
    m_idx += jump_increase;
}

void BootCode::PrintProgram()
{
    for (std::size_t i; i < m_program.size(); ++i)
    {
        std::cout << m_program[i].first << "\t" << m_program[i].second;
        if (i == m_idx)
        {
            std::cout << "\t<<";
        }
        std::cout << std::endl;
    }
}

void BootCode::TouchInstruction(const std::size_t idx)
{
    auto it = m_touched_register.find(idx);
    if (it != m_touched_register.end())
    {
        it->second++;
    }
    else
    {
        m_touched_register.insert({idx, 1U});
    }
}

std::size_t BootCode::CheckTouched(std::size_t idx)
{
    auto it = m_touched_register.find(idx);
    if (it == m_touched_register.end())
    {
        return 0U;
    }
    else
    {
        return it->second;
    }
}

}  // namespace bootcode

#endif  // BOOT_CODE_H
