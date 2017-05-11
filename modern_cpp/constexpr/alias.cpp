#include <memory>
#include <unordered_map>

void foo(int, const std::string&) { }

template<typename T>
using gFP = void (*)(int, const T&);

int main()
{
	typedef std::unique_ptr<std::unordered_map<std::string, std::string>> UPtrMapSS;
	using UPtrMapSS = std::unique_ptr<std::unordered_map<std::string, std::string>>;
	typedef void (*tFP)(int, const std::string&);
	using aFP = void (*)(int, const std::string&);
	tFP tfoo = foo;
	tfoo(1, "hello");
	aFP afoo = foo;
	afoo(2, "hello");
	hFP<std::string>::type hfp = foo;
	gFP<std::string> gfp = foo;
	return 0;
}
