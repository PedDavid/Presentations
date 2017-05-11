#include <iostream>

template<typename T>
struct deduced_type;

template<typename T>
void f(T&&) {
	deduced_type<T>::show;
}

namespace ns::test
{
	struct x {};
}

struct C {
	C() { std::cout << "A new instance was made." << std::endl; }
	C(const C&) { std::cout << "A copy was made." << std::endl; }
};

C f() {
	C c{};
	std::cout << "F was called" << std::endl;
	return c;
}

int main()
{
	ns::test::x x;
	std::cout << "Hello World" << std::endl;
	C obj = f();
	return 0;
}
