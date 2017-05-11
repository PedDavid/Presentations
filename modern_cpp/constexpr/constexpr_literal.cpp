constexpr int sum5(int arg) { return arg + 5; }

int main()
{
	int zero = 0;
	int five = sum5(zero);
	//static_assert(5 == sum5(zero), "");
	return 0;
}
