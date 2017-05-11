#include <iostream>
#include <vector>
#include <algorithm>

struct X
{
	X(int val) { std::cout << "Constructor!" << std::endl; }
	X() : X{0} { }
	X(const X& toCopy) { std::cout << "Copy!" << std::endl; }
	X& operator=(int val) { 
		std::cout << "Assignment!" << std::endl; 
		return *this; 
	}
	void foo() { }
};

X xObject();
X trueXObject{};

int main()
{
	//Deceiving, looks lie an assignment, it's actually a declaration taht calls Constructor
	X x = 1;
	//Assignment
	x = 5;

	X x2{1};
	x = 5;

	int i = 0.0f;   // -> OK?
	//int i2{0.0f}; -> Compile-time error
	
	trueXObject.foo(); // -> OK
	//xObject.foo(); -> Compile-time error? What? Why? OH, declared as function

	std::cout << "v" << std::endl;
	std::vector<int> v{10, 20};
	std::for_each(v.cbegin(), v.cend(), [](const int& e){e++; std::cout << e << std::endl;});
	std::cout << "v2" << std::endl;
	std::vector<int> v2(10, 20);
	std::for_each(v2.cbegin(), v2.cend(), [](const int& e){std::cout << e << std::endl;});
	return 0;
}
