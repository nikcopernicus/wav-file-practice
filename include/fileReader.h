#include <vector>
#include <string>

class fileReader {
public: static std::vector<uint8_t> read(const std::string& filepath, size_t length = 0);

};
