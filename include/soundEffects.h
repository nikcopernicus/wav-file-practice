#include <vector>
#include <string>

class soundEffects
{
private: std::vector<uint8_t> parsedSound;

public: void read(const std::string& filepath, const size_t size = 0);

public: void showFirstNormal(const size_t length = 16, const size_t width = 16);

public: void showFirstHex(const size_t length = 16, const size_t width = 16);

};
