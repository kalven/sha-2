#pragma once

#include <cstdint>

struct sha512_state
{
    std::uint64_t length;
    std::uint64_t state[8];
    std::uint32_t curlen;
    unsigned char buf[128];
};

void sha512_init(sha512_state& md);
void sha512_process(sha512_state& md, const void* in, std::uint32_t inlen);
void sha512_done(sha512_state& md, void* out);
