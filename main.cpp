#include "pwgen.h"

pwgen generator;

int main(int argc, char* argv[]) {

    if (!generator.process_command(argc, argv))
        return -1;

    std::cout << generator.gen_password() << std::endl;

    return 0;
}
