#pragma once
#include <string>

std::string dictionaryAttack(const std::string& targetHash, const std::string& algorithm, const std::string& wordlistPath);
std::string bruteForce(const std::string& targetHash, const std::string& algorithm, int maxLength);