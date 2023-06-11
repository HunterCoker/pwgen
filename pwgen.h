//
// Created by Hunter Coker on 2023-06-08.
//

#ifndef PWGEN_H
#define PWGEN_H

#include <iostream>
#include <string>
#include <vector>

class pwgen {
public:
    bool process_command(int n, char* tokens[]);
    [[nodiscard]] std::string gen_password() const;
public:
    pwgen() :m_size(0), m_conditions(0) {}
    ~pwgen() = default;
private:
    char* create_palette(int* n) const;
    static void print_help_message();
private:
    uint8_t m_size, m_conditions;
};


#endif //PWGEN_H