# <span class="fragment">Modern</span>
# C++

<div align="right">Pedro David</div>

Note: Modern? From C with objects to now.

---

## C++ is...?

Note: Ask audience if anyone has used C++, ask to keep hands up and ask about new and delete, ask those who use it to lower their hands.

----

> C++ is a general-purpose programming language. It has imperative, object-oriented and generic programming features, while also providing facilities for low-level memory manipulation.

[Wikipedia](https://en.wikipedia.org/wiki/C%2B%2B)

----

> It is used in high performance software, resource-constrained programming, large scale software infrastructure, and, most recently, energy-constrained environment (mobile and cloud).

[Sergey Zubkov, Quora](https://www.quora.com/What-is-C++-used-for/answer/Sergey-Zubkov-1)

----

> It is hard

[Pedro David](#/1/3)

and most users, specially newcomers <!-- .element: class="fragment" -->

---

## Variable initialization

<pre style="margin:0 auto;box-shadow: none"><code class="c++" data-trim data-noescape>
int x = 0;
int y(0);
</code></pre>
<pre class="fragment" style="margin:0 auto;box-shadow: none"><code class="c++" data-trim data-noescape>
int z{0};       // c++11 uniform initialization
int w = {0};    // "same" as z
</code></pre>

----

### Assignment vs Construction

<pre><code class="c++" data-trim data-noescape>
Bar e1;         // call default ctor
Bar e2 = e1;    <span class="fragment">// not an assignment; calls copy ctor</span>
ie1 = e2;       <span class="fragment">// an assignment; calls copy operator=</span>
</code></pre>

----

### Most Vexing Parse

<pre style="margin:0 auto;box-shadow: none"><code class="c++" data-trim data-noescape>
struct Bar{};
</code></pre>
<pre class="fragment" style="margin:0 auto;box-shadow: none"><code class="c++" data-trim data-noescape>
Bar fail();
</code></pre>

Note: Anything that can be parsed as a declaration must be interpreted as one.

----

### Uniform initialization
Avoids:
 - assignment ambiguity
 - most vexing parse

----

Works "everywhere"

 - Default initialization values (new to C++11) <!-- .element: class="fragment" -->
```c++
   class Bar{
       int x{1};   // fine, x's default value is 1
       int y = 1;  // ditto
       int z(0);   // error!
   }
```
 - Initalizing uncopyable objects              <!-- .element: class="fragment" -->
```c++
   std::atomic<int> ai1{0};   // fine
   std::atomic<int> ai1(0);   // fine
   std::atomic<int> ai1 = 0;  // error!
```

----

<span class="fragment" data-fragment-index="2">Prohibits implicit narrowing conversions among built-in types</span>

<pre style="margin:0 auto;box-shadow: none"><code class="c++" data-trim data-noescape>
int x(std::numeric_limits&ltlong&gt::max());    // okay...(truncated)
int y = std::numeric_limits&ltlong&gt::max();   // ditto
</code></pre>
<pre class="fragment" data-fragment-index="1" style="margin:0 auto;box-shadow: none"><code class="c++" data-trim data-noescape>
int z{std::numeric_limits&ltlong&gt::max()};    <span class="fragment" data-fragment-index="2">// compile-time error!</span>
</code></pre>

<div class="fragment" data-fragment-index="3" style="font-size:60%">
Great presentations
<div>Hubert Matthews - [The C++ Type System is your Friend](https://www.youtube.com/watch?v=MCiVdu7gScs)</div>
<div>Ben Deane - [Using Types Effectively](https://www.youtube.com/watch?v=ojZbFIQSdl8)</div>
</div>

Note: Ask audience opinion on this, then show links

----

 ### <span class="fragment" data-fragment-index="2" style="color:red">Don't</span> use it everywhere!

auto deduces std::initializer_list <!-- .element: class="fragment" data-fragment-index="1" -->[(N3922)](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n3922.html)<!-- .element: class="fragment" -->

```c++
auto x{1};
```

Note: Changed with N3922, this change is only standard for C++17 but implemented by a lot of compilers before (MSVC 19.0 - VS 2015, GCC 5.0, clang 3.8)

----

 <span class="fragment" data-fragment-index="2">**Strongly** prefers the overloads taking std::initializer_list
 <span class="fragment" data-fragment-index="4">, **really!**</span>

 <span class="fragment" data-fragment-index="6">Even if the best-match ctor **can't** be called!</span>

<pre style="margin:0 auto;box-shadow: none"><code class="c++" data-trim data-noescape>
struct Bar {
    Bar(int i, bool b);
    Bar(std::initializer_list&ltlong double&gt il);
    operator float() const;
};
Bar b1(10, true);   <span class="fragment" data-fragment-index="1">// first ctor</span>
Bar b2{10, true};   <span class="fragment" data-fragment-index="2">// std::initializer_list ctor</span>
Bar b5(b2);         <span class="fragment" data-fragment-index="3">// calls copy ctor</span>
Bar b6{b2};         <span class="fragment" data-fragment-index="4">// std::initializer_list ctor</span>
</code></pre>
<pre class="fragment" data-fragment-index="5" style="margin:0 auto;box-shadow: none"><code class="c++" data-trim data-noescape>
struct Foo { Foo(std::initializer_list&ltbool&gt); };
Foo b{10, 5.0};     <span class="fragment" data-fragment-index="6">// error! requires narrowing conversions</span>
</code></pre>

----

Unless there is no way to convert the types

```c++
struct Bar {
    Bar(int i, double b);
    Bar(std::initializer_list<std::string> il);
};
Bar b{10, 5.0}; // now calls first ctor
```

<span class="fragment" data-fragment-index="1">Or it's empty... </span>

<pre class="fragment" data-fragment-index="1" style="margin:0 auto;box-shadow: none"><code class="c++" data-trim data-noescape>
Bar b{};    // calls default ctor
</code></pre>
<pre class="fragment" data-fragment-index="2" style="margin:0 auto;box-shadow: none"><code class="c++" data-trim data-noescape>
Bar b{{}};  // calls init list ctor
</code></pre>

---

# How modern C++ makes things better

---

### Memory management

```c++
struct Base {
    Base(int value);
};
struct Derived {
    Derived(int value);
};
int main() {
    Bar* pointer = new Derived(0);
    delete pointer;
    return 0;
}
```

Note: Is error prone, boring

----

### [Smart Pointers](#/smart_pointers)

```c++
struct Base {
    const int value;
    Base(int value) : value{value} { }
};
struct Derived : Base {
    Derived(int value) : Base{value} { }
};
int main() {
    auto pointer = std::make_unique<Bar>(0);
    return 0;
}
```

Note: RAII(Resource acquisition is initialization)
        Exception-safe because C++ guarantees that all stack objects are destroyed at the end of the enclosing scope, known as stack unwinding(assembly pops);
        Destructors are exception-safe(noexcepetd(TODO: link)) and are always called if object is fully constructed, no exception came from constructor
        std::make_unique<T> is C++14 only;
        TODO: Add link to Smart Pointer slides;

---

### And let's not talk about this :'(
```c++
int main() {
    std::map<int, std::string> map;
    map[1] = "Hi"; map[2] = "World";
    int product = 1;
    for (std::map<int, std::string>::const_iterator itr = map.begin();
        itr != vec.end();
        ++itr) 
    {
        product *= itr->first;
        std::cout << itr->second;
    }
    return 0;
}
```

----

### [Initializer lists](#/initializer_lists)

```c++
int main() {
    const std::map<int, std::string> map{{1, "Hi"}, {2, "World"}};
    int product = 1;
    for (std::map<int, std::string>::const_iterator itr = map.begin();
        itr != vec.end();
        ++itr) 
    {
        product *= itr->first;
        std::cout << itr->second;
    }
    return 0;
}
```

----

### [auto](#/auto)

```c++
int main() {
    const std::map<int, std::string> map{{1, "Hi"}, {2, "World"}};
    int product = 1;
    for (auto itr = map.begin();
        itr != map.end();
        ++itr) 
    {
        product *= itr->first;
        std::cout << itr->second;
    }
    return 0;
}
```

----

### [Range-Based For Loop](#/range_based_fl)

```c++
int main() {
    const std::map<int, std::string> map{{1, "Hi"}, {2, "World"}};
    int product = 1;
    for (const auto& val : map) {
        product *= val.first;
        std::cout << val.second;
    }
    return 0;
}
```

----

### [Structured Bindings](#/structured_bindings)

```c++
int main() {
    const std::map<int, std::string> map{{1, "Hi"}, {2, "World"}};
    int product = 1;
    for (const auto& [key, name] : map) {
        product *= key;
        std::cout << name;
    }
    return 0;
}
```

Note: Available in C++17

---
<!-- .slide: id="smart_pointers" -->
## Smart-Pointers

```c++
std::unique_ptr<Bar> x{new Bar{0}};
auto y = std::make_unique<Bar>(0);
```

----

### Prefer std::make_unique and std::make_shared to direct use of new

----

## Implementation details

```c++
auto vec = std::make_unique<std::vec<int>>(10, 20); // 10 20's
```

```c++
template<typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts&&... params)
{
    return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
    // new T{std::forward<Ts>(params)...}
    //  this would make vec{10, 20}, a vec with 2 elements, 10 and 20
}
```

---

## <span class="fragment" data-fragment-index="1">Initializer List</span>

```c++
std::vector<int> vec;
vec.push_back(1); vec.push_back(2); vec.push_back(3);
```

<pre class="fragment" data-fragment-index="1" style="margin:0 auto;box-shadow: none"><code class="c++" data-trim data-noescape>
std::vector&ltint&gt vec{1, 2, 3};
</code></pre>

----

This works

```c++
struct Bar{
    Bar(int value);
};
std::vector<Bar> vec{1, 2, 3};    
```

This doesn't

```c++
struct Bar{
    explicit Bar(int value);
};
std::vector<Bar> vec{1, 2, 3};    
```

---

## <span class="fragment" data-fragment-index="1">Type Deduction<span>

```c++
std::unique_ptr<std::unordered_map<std::string, std::string>> uptrmapss = some_factory();
```

<pre class="fragment" data-fragment-index="1" style="margin:0 auto;box-shadow: none"><code class="c++" data-trim data-noescape>
auto uptrmapss = some_factory();
</code></pre>

Note: Functions can have auto return type since C++14
        Discuss about audience likeliness of auto
        Todo: Slides about type deduction

---

## <span class="fragment" data-fragment-index="1">Range-Based For Loop</span>

```c++
std::vector<Bar> vec;
for(std::vector<Bar>::const_iterator itr = vec.begin();
    itr != vec.end();
    ++itr)
{
    // ...
}
```

<pre class="fragment" data-fragment-index="1" style="margin:0 auto;box-shadow: none"><code class="c++" data-trim data-noescape>
std::vector&ltBar&gt vec;
for(const Bar b : vec) {
    // ...
}
</code></pre>

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

# Questions?

This slide can be found on

[Github]()