#include <iostream>

class X
{
	public:
		constexpr X(int value) : _value{ value } { }
		constexpr int value() { return _value; }
	private:
		int _value;
};

constexpr int itox(X x) { return x.value(); }

int main()
{
	static_assert(1 == itox(X{ 1 }), "");
	X x{1};
	X* xp = &x;
	std::cout << xp->value() << std::endl;
	xp = nullptr;
	std::cout << xp->value() << std::endl;
	return 0;
}
