#include "pwgen.h"

#include <random>

bool pwgen::process_command(int n, char* tokens[]) {
    // no arguments given
    if (n == 1) {
        std::cout << "error: missing argument(s)... usage: 'pwgen [OPTIONS] [LENGTH--REQUIRED]' or see '--help'\n";
        return false;
    }

    // special arguments
    if (strcmp(tokens[1], "--help") == 0) {
        print_help_message();
        return true;
    }

    // process options and length
    else {
        int k = 1;
        // options ( either individually set or in combination )
        while (tokens[k][0] == '-') {
            if (strlen(tokens[k]) == 1) {
                std::cout << "error: missing option(s)... see '--help'\n";
                return false;
            }

            int i = 1;
            while (tokens[k][i] != '\0') {
                switch (tokens[k][i]) {
                    case 'l': m_conditions |= (1u << 0); break;
                    case 'u': m_conditions |= (1u << 1); break;
                    case 'n': m_conditions |= (1u << 2); break;
                    case 's': m_conditions |= (1u << 3); break;
                    default:
                        std::cout << "error: invalid option '" << tokens[k][i] << "'... see '--help'\n";
                        return false;
                }
                i++;
            }
            k++;

            if (k == n) {
                std::cout << "error: no length given... see '--help'\n";
                return false;
            }
        }

        // length
        int j = 0;
        if (k == 1) m_conditions = (1u << 0) | (1u << 1);
        while (tokens[k][j] != '\0') {
            if (!isdigit(tokens[k][j])) {
                std::cout << "error: invalid length '" << tokens[k][j] << "'... see '--help'\n";
                return false;
            }
            j++;
        }
        m_size = static_cast<uint8_t>(atoi(tokens[k]));
    }

    return true;
}

// using palette conditions, generates valid symbols for desired password
std::string pwgen::gen_password() const {
    int palette_size;
    const char* palette = create_palette(&palette_size);
    std::string output; output.resize(m_size);
    srandom(std::time(nullptr));
    for (int i = 0; i < m_size; ++i) {
        output[i] = palette[1 + (random() % palette_size)];
    }
    return output;
}

const char* pwgen::create_palette(int* size) const {
    *size = 0;
    char* palette = static_cast<char*>(malloc(85));
    if (m_conditions & (1u << 0)) { memcpy(palette + *size, "abcdefghijglmnopqrstuvwxyz", 26); *size += 26; }
    if (m_conditions & (1u << 1)) { memcpy(palette + *size, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 26); *size += 26; }
    if (m_conditions & (1u << 2)) { memcpy(palette + *size, "0123456789"                , 10); *size += 10; }
    if (m_conditions & (1u << 3)) { memcpy(palette + *size, "!()-.?[]_`~;:@#$%^&*+="    , 23); *size += 23; }
    return palette;
}

void pwgen::print_help_message() {
    std::cout <<
        "PWGEN USAGE:\n"
        "\tpwgen [OPTIONS] [LENGTH--REQUIRED]\n"
        "OPTIONS:\n"
        "\t-l\tlowercase - includes lowercase letters in the generated password.\n"
        "\t-u\tuppercase - includes uppercase letters in the generated password.\n"
        "\t-n\tlowercase - includes numbers in the generated password.\n"
        "\t-s\tlowercase - includes special characters in the generated password.\n"
        "LENGTH:\n"
        "\tany integer ranging from 1 to 255 and denotes the length of the generated password.";
}