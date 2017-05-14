template<size_t N>
struct Factorial {
    static constexpr size_t value = N * Factorial<N -1>::value;
};

template<>
struct Factorial<0> {
    static constexpr size_t value = 1;
};

constexpr size_t factorial(size_t input) {
    return input == 0 ? 1 : input * factorial(input - 1);
}

int main()
{
    //static_assert(120 == Factorial<5>::value, "Not at compile time");
    //static_assert(120 == factorial(5), "Not at compile time");
    return Factorial<30>::value;
}