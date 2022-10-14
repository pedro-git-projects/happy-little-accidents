#ifndef UUID_H
#define UUID_H

#include <random>
#include <sstream>

namespace uuid {
static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_int_distribution<> dis(0,15);
static std::uniform_int_distribution<> dis2(8, 11);

std::string generateUUId();
}

#endif // UUID_H
