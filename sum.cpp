// SHA-256. This code is Public Domain
#include "sha256.hpp"

#include <cstdio>
#include <fstream>
#include <iostream>

void process_file(std::istream& in, const char* name)
{
    sha256_state md;
    sha256_init(md);

    char buf[64];
    do
    {
        in.read(buf, sizeof(buf));
        sha256_process(md, buf, in.gcount());
    }
    while(in.gcount());

    unsigned char res[32];
    sha256_done(md, res);

    for(int i = 0; i != 32; ++i)
        std::printf("%02x", res[i]);
    std::printf("  %s\n", name);
}

// Emulates the basic functionality of sha256sum from coreutils.
int main(int argc, char** argv)
{
    if(argv[1])
    {
        for(char** file = argv+1; *file; ++file)
        {
            std::ifstream in(*file, std::ifstream::binary);
            if(in.is_open())
                process_file(in, *file);
        }
    }
    else
    {
        process_file(std::cin, "-");
    }
}
