#include "uuid.h"

std::string uuid::generateUUId() {
    std::stringstream ss;
    int i;
    ss << std::hex;
    for (i = 0; i < 4; i++) {
        ss << dis(gen);
    }
    return ss.str();
}
