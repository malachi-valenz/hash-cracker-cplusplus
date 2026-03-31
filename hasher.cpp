#include "hasher.h"
#include "picosha2.h"
extern "C" {
    #include "md5.h"
}
#include <sstream>
#include <iomanip>

std::string md5(const std::string& input) {
    unsigned char digest[16];
    MD5_CTX ctx;
    md5_init(&ctx);
    md5_update(&ctx, (const unsigned char*)input.c_str(), input.size());
    md5_final(&ctx, digest);

    std::stringstream ss;
    for (int i = 0; i < 16; i++)
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)digest[i];
    return ss.str();
}

std::string sha1(const std::string& input) {
    return "";
}

std::string sha256(const std::string& input) {
    return picosha2::hash256_hex_string(input);
}