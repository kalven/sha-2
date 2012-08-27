// SHA-512. This code is Public Domain
#include "sha512.hpp"

#include <cstdio>
#include <fstream>
#include <iostream>

void process_file(std::istream& in, const char* name)
{
    sha512_state md;
    sha512_init(md);

    char buf[64];
    do
    {
        in.read(buf, sizeof(buf));
        sha512_process(md, buf, in.gcount());
    }
    while(in.gcount());

    unsigned char res[64];
    sha512_done(md, res);

    for(int i = 0; i != 64; ++i)
        std::printf("%02x", res[i]);
    std::printf("  %s\n", name);
}

// Emulates the basic functionality of sha512sum from coreutils.
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
