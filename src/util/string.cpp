#include "string.hpp"

#include <cstdarg>
#include <sstream>

namespace util {

std::string format(const std::string& fmt, ...) {

	va_list args;
	va_start(args, fmt);
	int res = vsnprintf(nullptr, 0, fmt.c_str(), args);
	va_end(args);

	if (res < 0) {
		throw new std::runtime_error{"Could not format string: " + fmt};
	}

	std::string buffer;
	buffer.resize(res);

	va_start(args, fmt);
	res = vsnprintf(&buffer[0], res + 1, fmt.c_str(), args);
	va_end(args);

	if (res < 0) {
		// should be unreachable
		throw new std::runtime_error{"Could not format string: " + fmt};
	}
	return buffer;
}

} // namespace util