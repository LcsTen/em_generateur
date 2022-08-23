#ifdef __cpp_lib_format
	#include <format>
#endif

template<typename... Args>
std::string format(const std::string& fmt, Args... args){
	#ifdef __cpp_lib_format
		return std::format(fmt, args...);
	#else
		int size = std::snprintf(nullptr, 0, fmt.data(), args...);
		std::string res(size, '\0');
		std::snprintf(res.data(), size + 1, fmt.data(), args...);
		return res;
	#endif
}
