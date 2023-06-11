#include "pwgen.h"

pwgen generator;

int main(int argc, char* argv[]) {
#ifdef DEBUG
    int testc = 2;
    char* testv[2];
    testv[0] = static_cast<char*>(malloc(8)); strcpy(testv[0], "./pwgen");
    testv[1] = static_cast<char*>(malloc(2)); strcpy(testv[1], "8");

    if (!generator.process_command(testc, testv))
        return -1;
#else
    if (!generator.process_command(argc, argv))
        return -1;
#endif
    std::cout << generator.gen_password() << std::endl;
    return 0;
}
