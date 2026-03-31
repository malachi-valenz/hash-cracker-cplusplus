#include "cracker.h"
#include "hasher.h"
#include <fstream>
#include <iostream>

std::string hashWord(const std::string& word, const std::string& algorithm) {
    if (algorithm == "md5")     return md5(word);
    if (algorithm == "sha1")    return sha1(word);
    if (algorithm == "sha256")  return sha256(word);
    return "";
}

std::string dictionaryAttack(const std::string& targetHash, const std::string& algorithm, const std::string& wordlistPath) {
    std::ifstream file(wordlistPath);
    if (!file.is_open()) {
        std::cout << "Could not open wordlist: " << wordlistPath << std::endl;
        return "";
    }

    std::string word;
    long long tried = 0;
    while (std::getline(file, word)) {
        if (!word.empty() && word.back() == '\r')
            word.pop_back();
        if (hashWord(word, algorithm) == targetHash) {
            std::cout << "\n[+] Found: " << word << std::endl;
            return word;
        }
        tried++;
        if (tried % 100000 == 0)
            std::cout << "\r[*] Tried " << tried << " words..." << std::flush;
    }
    return "";
}

std::string bruteForce(const std::string& targetHash, const std::string& algorithm, int maxLength) {
    const std::string charset = "abcdefghijklmnopqrstuvwxyz0123456789";
    std::string candidate(1, charset[0]);

    auto increment = [&](std::string& s) {
        for (int i = s.size() - 1; i >= 0; i--) {
            size_t pos = charset.find(s[i]);
            if (pos + 1 < charset.size()) {
                s[i] = charset[pos + 1];
                return true;
            }
            s[i] = charset[0];
        }
        s = std::string(s.size() + 1, charset[0]);
        return s.size() <= (size_t)maxLength; 
    };

    long long tried = 0;
    while (candidate.size() <= (size_t)maxLength) {
        if (hashWord(candidate, algorithm) == targetHash) {
            std::cout << "\n[+] Found: " << candidate << std::endl;
            return candidate;
        }
        tried++;
        if (tried % 100000 == 0)
            std::cout << "\r[*] Tried " << tried << " candidates..." << std::flush;
        if (!increment(candidate)) break; 
    }
    return "";
}