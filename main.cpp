#include <string>
#include "hasher.h"
#include "cracker.h"

extern "C" {

__attribute__((used))
const char* crackHash(const char* targetHash, const char* algorithm, const char* mode, const char* wordlistPath, int maxLength) {
    std::string hash(targetHash);
    std::string algo(algorithm);
    std::string modeStr(mode);

    static std::string result;

    if (modeStr == "dictionary") {
        result = dictionaryAttack(hash, algo, std::string(wordlistPath));
    } else if (modeStr == "brute") {
        result = bruteForce(hash, algo, maxLength);
    } else {
        result = "";
    }

    if (result.empty()) return "NOT_FOUND";
    return result.c_str();
}

}