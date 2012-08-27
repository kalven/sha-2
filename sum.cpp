// SHA-2. This code is Public Domain
#include "sha224.hpp"
#include "sha256.hpp"
#include "sha384.hpp"
#include "sha512.hpp"

#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>

template<class State>
void process(int bits, std::istream& in, const char* name)
{
    State md;
    sha_init(md);

    char buf[64];
    do
    {
        in.read(buf, sizeof(buf));
        sha_process(md, buf, in.gcount());
    }
    while(in.gcount());

    unsigned char res[bits/8];
    sha_done(md, res);

    for(int i = 0; i != bits/8; ++i)
        std::printf("%02x", res[i]);
    std::printf("  %s\n", name);
}

void process_file(char* argv0, std::istream& in, const char* name)
{
    if(std::strstr(argv0, "512"))
        process<sha512_state>(512, in, name);
    if(std::strstr(argv0, "384"))
        process<sha384_state>(384, in, name);
    if(std::strstr(argv0, "256"))
        process<sha256_state>(256, in, name);
    if(std::strstr(argv0, "224"))
        process<sha224_state>(224, in, name);
}

// Emulates the basic functionality of sha{224,256,384,512}sum from coreutils.
int main(int argc, char** argv)
{
    if(argv[1])
    {
        for(char** file = argv+1; *file; ++file)
        {
            std::ifstream in(*file, std::ifstream::binary);
            if(in.is_open())
                process_file(argv[0], in, *file);
        }
    }
    else
    {
        process_file(argv[0], std::cin, "-");
    }
}
