#include "funcs.hpp"
#include <random>

std::string generate(const std::vector<std::string>& bank, int length) {
	static std::random_device rd{};
	static std::mt19937 engine{ rd() };
	std::uniform_int_distribution<> dist{ 0, static_cast<int>(bank.size()-1) };

	std::string password = std::string("");
	for (int i = 0; i < length; i++) {
		password += (bank[dist(engine)]);
	}
	return password;
}