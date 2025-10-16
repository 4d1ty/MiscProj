#include <string>
#include <cctype>
#include <algorithm>

void toLowerCase(std::string& s) {
	std::transform(s.begin(), s.end(), s.begin(), tolower);
}

void toUpperCase(std::string& s) {
	std::transform(s.begin(), s.end(), s.begin(), toupper);
}