# Modern C++

How to do something in modern C++

---

## C++ is...?

----

> C++ is a general-purpose programming language. It has imperative, object-oriented and generic programming features, while also providing facilities for low-level memory manipulation.
> - Wikipedia

----

# HARD

> - Most Users and all newcomers


---

## Variable initialization

```c++
int x = 0;
int y(0);
```
```c++
int z{0};       // c++11 uniform initialization
int w = {0};    // same as z (might differ in c++17)
```

----

### Assignment vs Construction

```c++
Bar e1;         // call default ctor
Bar e2 = e1;    // not an assignment; calls copy ctor
e1 = e2;        // an assignment; calls copy operator=
```

----

### Most Vexing Parse

```c++
struct Bar{};
Bar fail();
```

----

### Uniform initialization

 - Avoids:
  - assignment ambiguity
  - most vexing parse

----

 - Works "everywhere"

  - Default initialization values (new to C++11)
```c++
    class Bar{
        int x{1};   // fine, x's default value is 1
        int y = 1;  // ditto
        int z(0);   // error!
    }
```
  - Initalizing uncopyable objects
```c++
    std::atomic<int> ai1{0};   // fine
    std::atomic<int> ai1(0);   // fine
    std::atomic<int> ai1 = 0;  // error!
```

----

 - Prohibits implicit narrowing conversions among built-in types

```c++
int x{std::numeric_limits<long>::max()};    // compile-time error!
int y(std::numeric_limits<long>::max());    // okay...(truncated)
int z = std::numeric_limits<long>::max();   // ditto
```

----

 ### Use it everywhere! (not)

 - `auto` deduces std::initializer_list (changed in C++17)
 
```c++
auto x{1};  // std::initializer_list in C++11/14
            // int in C++17
```

----

 - **Strongly** prefers the overloads taking std::initializer_list

```c++
struct Bar {
    Bar(int i, bool b);
    Bar(std::initializer_list<long double> il);
}
Bar b1(10, true);   // first ctor
Bar b2{10, true};   // std::initializer_list ctor
```

```c++
struct Bar {
    ...
    operator float() const;     // convert to float
}
Bar b5(b2);                     // calls copy ctor
Bar b6{b2};                     // std::initializer_list ctor
```

----

 - **Really!** Even if the best-match ctor can't be called

```c++
struct Bar {
    Bar(int i, double b);
    Bar(std::initializer_list<bool> il);
}
Bar b{10, 5.0}; // error! requires narrowing conversions
```

 - Unless there is no way to convert the types

```c++
struct Bar {
    Bar(int i, double b);
    Bar(std::initializer_list<std::string> il);
}
Bar b{10, 5.0}; // now calls first ctor
```

 - Or it's empty...

```c++
Bar b{{}};      // in which case you have to call it this way
```

---

## Initializer List

```c++
std::vector<int> vec{1, 2, 3};
```

----

This works

```c++
struct Bar{
    Bar(int value);
}
std::vector<Bar> vec{1, 2, 3};    
```

This doesn't

```c++
struct Bar{
    explicit Bar(int value);
}
std::vector<Bar> vec{1, 2, 3};    
```

----

## Type Deduction


```c++
std::unique_ptr<std::unordered_map<std::string, std::string>> uptrmapss = ...;
```

```c++
auto uptrmapss = some_factory();
```

functions can have `auto` return type since C++14

---

## Range-Based For Loop

```c++
std::vector<Bar> vec{1, 2, 3};
for(const Bar b : vec) {
    // ...
}
```

---

## Lambdas

```c++
int one{1};
auto sum_one = [one](const int rhs){ return one + rhs; };
auto res = sum_one(2);
```

----

### Generic Lambdas (C++14)

```c++
int one{1};
auto sum_one = [one](const auto rhs){ return one + rhs; };
auto res = sum_one(2);
```

---

## Smart-Pointers

```c++
std::unique_ptr<Bar> x{new Bar{0}};
auto y = std::make_unique<Bar>(0);
```

TODO: std::make_unique() vs {} (test with vector)

---

# How Modern C++ makes things better

TODO: Insert sad or disgust emoji
```c++
int main() {
    const std::vector<int> vec;
    vec.push_back(1); vec.push_back(2); vec.push_back(3);
    int product = 1;
    for (std::vector<int>::const_iterator itr = vec.begin();
        itr != vec.end();
        ++itr) 
    {
        product *= *itr;
    }
}
```

----

### Initializer lists

```c++
int main() {
    const std::vector<int> vec{1, 2, 3};
    int product = 1;
    for (std::vector<int>::const_iterator itr = vec.begin();
        itr != vec.end();
        ++itr) 
    {
        product *= *itr;
    }
}
```

----

### `auto`


```c++
int main() {
    const std::vector<int> vec{1, 2, 3};
    int product = 1;
    for (auto itr = vec.begin();
        itr != vec.end();
        ++itr) 
    {
        product *= *itr;
    }
}
```

----

### Range-Based For Loop

```c++
int main() {
    const std::vector<int> vec{1, 2, 3};
    int product = 1;
    for (const auto val : vec) {
        product *= val;
    }
}
```

----

### Inline the container

```c++
int main() {
    int product = 1;
    for (const auto val : {1, 2, 3}) {
        product *= val;
    }
}
```