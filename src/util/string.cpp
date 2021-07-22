#include "string.hpp"

#include <cstdarg>
#include <sstream>

namespace util {

std::string format(const std::string& fmt, ...) {
	size_t currentSize = fmt.size() * 2;
	std::string buffer;
	for (int i = 0; i < 8; ++i) {
		buffer.resize(currentSize);

		va_list args;
		va_start(args, fmt);
		int res = vsnprintf(&buffer[0], currentSize, fmt.c_str(), args);
		va_end(args);

		if (res >= 0) {
			buffer.resize(res);
			return buffer;
		}

		currentSize += currentSize / 2 + 1;
	}

	throw new std::runtime_error{"Could not format string: " + fmt};
}

} // namespace util