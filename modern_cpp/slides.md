# <span class="fragment" data-fragment-index="2">Modern</span>
# C<span class="fragment" data-fragment-index="1">++</span>

<div align="right">Pedro David</div>

Note: 
    Hi, my name is Pedro;

    C? The ones who know C raise hands. malloc/free;

    C++? Lower hands people that don't know. C with classes? new/delete

    Modern? Who knew C++ is still evolving, ISO 98/03, 11/14/17/20?

---

## C++ is...?

----

> C++ is a general-purpose programming language. It has imperative, object-oriented and generic programming features, while also providing facilities for low-level memory manipulation.

[Wikipedia](https://en.wikipedia.org/wiki/C%2B%2B)

Note:
    A formal presentation

    But more importantly, for what is it used?

----

> It is used in high performance software, resource-constrained programming, large scale software infrastructure, and, most recently, energy-constrained environment (mobile and cloud).

[Sergey Zubkov, Quora](https://www.quora.com/What-is-C++-used-for/answer/Sergey-Zubkov-1)

Note:
    And...

----

> It is hard

[Pedro David](#/1/3)

and most users, specially newcomers <!-- .element: class="fragment" -->

Note:
    Specially when something as simple as initializing a variable...

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

Note:
    Is this complicated... Two ways of initlializing a variable... which to use

    And... There is 2 more now
    
    And that "same" comes from a book, and no longer is correct again

----

### Assignment vs Construction

<pre><code class="c++" data-trim data-noescape>
Bar e1;         // call default ctor
Bar e2 = e1;    <span class="fragment">// not an assignment; calls copy ctor</span>
ie1 = e2;       <span class="fragment">// an assignment; calls copy operator=</span>
</code></pre>

Note:
    Talk with audience about knowledge of different constructors in C++

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

 ### <span class="fragment" data-fragment-index="1" style="color:red">Don't</span> use it everywhere!

<span class="fragment" data-fragment-index="1">
    <span class="fragment strike" data-fragment-index="3">
        auto deduces std::initializer_list
    </span>
</span> 
<span class="fragment" data-fragment-index="3">
    [(N3922)](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n3922.html)
</span>

```c++
auto x{1};
```

Note: Changed with purposal N3922, this change is only standard for C++17 but implemented by a lot of compilers before (MSVC 19.0 - VS 2015, GCC 5.0, clang 3.8)

----

 <span class="fragment" data-fragment-index="2">
    **Strongly** prefers the overloads taking std::initializer_list
    <span class="fragment" data-fragment-index="4">
        , **really!**
    </span>
    <span class="fragment" data-fragment-index="6">
        Even if the best-match ctor **can't** be called!
    </span>
</span>

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

Note: 
    RAII(Resource acquisition is initialization)

    Stack unwinding(assembly pops) is guaranteed by C++

    If constructor didn't throw exception

    Destructor is called at end of scope
    
    Destructors are exception-safe(noexcept(TODO: link))

    std::make_unique<T> is C++14 only;

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

## <span class="fragment" data-fragment-index="1">auto<span>

```c++
std::unique_ptr<std::unordered_map<std::string, std::string>> uptrmapss = some_factory();
```

<pre class="fragment" data-fragment-index="1" style="margin:0 auto;box-shadow: none"><code class="c++" data-trim data-noescape>
auto uptrmapss = some_factory();
</code></pre>

Note: Discuss type inference with audience, some_factory is a terrible name to use type deduction! Talk about type aliases (typedef)

----

- Initialization is required

```c++
int x;      // potentially uninitialized
auto y;     // error! initializer required!
```

- Programmer mistakes

```c++
unsigned sz = v.size(); //std::vector<int>::size_type
std::unordered_map<std::string, int> map;
for(const std::pair<std::string, int>& pair : map) { }
```

Note:
    Show Demo

---

### <span class="fragment" data-fragment-index="1">Always Const</class>

<pre style="margin:0 auto;box-shadow: none"><code class="c++" data-trim data-noescape>
std::string tooMuchWork;
tooMuchWork = "A somewhat rather long string";
</code></pre>
<pre class="fragment" data-fragment-index="1" style="margin:0 auto;box-shadow: none"><code class="c++" data-trim data-noescape>
const std::string lessWork = "A somewhat rather long string";
</code></pre>

Note: 
    This slide is more an advice than a new feature

    First we're creating the string then reassigning it

    Always const, in this case the construction is roughly 32% more efficient

    But there are things that not even const can do... constexpr

---

## <span class="fragment" data-fragment-index="1">Lambdas</class>
### <span class="fragment" data-fragment-index="1">IIFE</class>

<pre style="margin:0 auto;box-shadow: none"><code class="c++" data-trim data-noescape>
const int i = std::rand();
std::string tooMuchWorkAgain;
switch(i % 4) {
    case 0: tooMuchWorkAgain = "long string is mod 0"; break;
    // ...
}
</code></pre>
<pre class="fragment" data-fragment-index="1" style="margin:0 auto;box-shadow: none"><code class="c++" data-trim data-noescape>
const std::string lessWork = [i](){
    switch(i % 4) {
        case 0: return "long string is mod 0";
        // ...
    }
}();
</code></pre>
<pre class="fragment" data-fragment-index="2" style="margin:0 auto;box-shadow: none"><code class="c++" data-trim data-noescape>
const auto sum2 = [](int value){ return value + 2; }; 
</code></pre>

Note: 
    IIFE(Immediately invocked function expression) 

    Lambdas are one case of types only known to compilers

    In C++14 lambdas can use auto parameters

    Using auto, compared to std::function is almost always smaller and faster

---

## Resources

Scott Meyers, "Effective Modern C++"

[Jason Turner, “Practical Performance Practices"](https://www.youtube.com/watch?v=uzF4u9KgUWI) 

[Jason Turner, "Intro To Modern Cpp"](https://github.com/lefticus/presentations/tree/master/IntroToModernCpp)

---

# Questions?

This slide can be found on

[Github](https://github.com/PedDavid/Presentations/tree/master/modern_cpp)

Note: Show factorial demo
        http://en.cppreference.com/w/cpp/compiler_support ;
        https://gcc.gnu.org/gcc-7/ ;
        http://releases.llvm.org/ ;
        https://blogs.msdn.microsoft.com/vcblog/2017/05/10/c17-features-in-vs-2017-3/ ;