# The Crank Framework

[![Contributor Covenant](https://img.shields.io/badge/Contributor%20Covenant-2.1-4baaaa.svg)](CODE_OF_CONDUCT.md)
[![License](https://img.shields.io/github/license/oraqlle/crank)](LICENSE)
![Current Release](https://img.shields.io/github/v/release/oraqlle/crank?include_prerelease)
![bpt Version](https://img.shields.io/badge/bpt%20version%3A-1.0.0--beta--1-blue)
![C++ Standard](https://img.shields.io/badge/C%2B%2B%20Standard-C%2B%2B11..20-red)
![GCC](https://img.shields.io/badge/GCC-11.1.0-yellow)
![Clang](https://img.shields.io/badge/clang-12.0.0-yellow)

## Welcome

Crank is a simple and state management framework. It allows you to create state pages that are pushed and popped onto a state-stack. Pages are polymorphic types that are derived from a base state class which becomes the blueprint for how the state is managed by the engine.

Crank is designed to by as simple as possible and only provides a runtime framework for managing states. It is not designed to be able to render images/displays or handle other forms of processing.

Crank is built using the [bpt](https://bpt.pizza) build tool and is hosted on the [Trove Package Index](https://trovepi.dev). You'll need both resources to use Crank. A full list of [links and resources](#links-and-resources) are at the bottom of the README.

## Contents

- [The Crank Framework](#the-crank-framework)
  - [Welcome](#welcome)
  - [Contents](#contents)
  - [Adding to your project](#adding-to-your-project)
  - [Design and Use](#design-and-use)
    - [The Runtime Engine](#the-runtime-engine)
    - [States](#states)
    - [Data and Shared Resources](#data-and-shared-resources)
  - [Example](#example)
    - [A simple state](#a-simple-state)
    - [Global variables](#global-variables)
    - [Making an Engine Object](#making-an-engine-object)
    - [Final Result](#final-result)
  - [Links and Resources](#links-and-resources)
    - [bpt](#bpt)
    - [Trove](#trove)

---

## Adding to your project

To add crank to your project you'll need to two things. First, you're project or package must be using the bpt build tool and have a subsequent `bpt.yaml` file. In the file add the specifier `dependencies:` (if you haven't already got other dependencies) followed by the crank package.

e.g.

```yaml
# ...

dependencies:
- crank@0.1.0

# ...
```

This will tell bpt that you are using a package called `crank`. If your project or package uses many libraries, you have to specify which libraries are using `crank`. Details in the [links](#links-and-resources) section below.

To use this package, you have to specify where to look for the package to the bpt CLI. This is done using the `--use-repo=` sub-command. This command allows you to use the [Trove](https://trovepi.dev) public repo.

e.g.

```sh
bpt build -t :c++20:gcc-11 --use-repo="https://trovepi.dev"
```

This will allow bpt to find and crank, download it and build against it. This sub-command is important as otherwise bpt will not know where to find the package. Details on bpt's design rational regarding this can be found [here](https://bpt.pizza).

To include the crank engine you only need to use the `<crank.hpp>` header and any headers you make containing derived state classes.

---

## Design and Use

This framework has two major components, the runtime engine which manages the state-stack and flow of operations and the states.

Crank uses the _Input, Update, Output_ (IUO) model to runa  program. In crank these are methods available in both the `crank::engine` class and `crank::states::base` class called _handle_events(), update(),_ and _draw()_ respectively.

- `handle_events()` - Handles events suchs as keyboard input.
- `update()` - Updates the internal state of a given state object
- `draw()` - Outputs the updated state such as rendering to the screen or output to a console.

An example of a simple running program can be found in the [example](#example) section below.

### The Runtime Engine

The `crank::engine` class is very simple. It's main job is to manage the stack of states and provide an interface for calling the _IUO_ methods. Because of the design of the engine class, an engine instance is managed by a `std::shared_ptr`. This creates the engine. The engine is then initialised using it's `init()` method which takes the screen and viewport dimensions as well as a copy of the `std::shared_ptr` to the engine resource.

The engine class also features some _meta-methods_ that help diagnose the state of the engine. Two such methods are the  `running()` method which indicates whether engine is currently running or if it is in the quit phase and the `quit()` method which shuts down the current engine and leaves it in its pre-init phase. This allows you to run a countinues loop while the engine is running and have a state manage if the engine should quit.

The engine class uses the `handle_events()`, `update()` and `draw()` methods to run the top most state's corresponding methods.

The engine also has three more vital methods. The `push_state()`, `change_state()` and `pop_state()` methods. The push and pop methods are pretty self explainatory, they push or pop a state to/from the state-stack, calling the states init, cleanup or pause/resume methods respectively.

Change state is a bit different, if you want to change to a new state but don't want to recover the last state, `change_state()` will clean up the current state and replace it with the indicated state. (e.g. when going from a game state to a game over).

### States

The `crank::states::base` class is a pure virtual class design to blueprint the interface that a state should provide. These are only the minimum requirements for the engine to use the state, in derived state classes, you can implement other methods for handle other operations specific to that states processing.

The main methods provided by `crank::states::base` are the `handle_events()`, `update()` and `draw()` methods. These methods are called by the engine when the corresponding engine methods are called. They are used to ahndle the main processes that can occur in a game or program.

The base class provides and interface for a `init()` method; called whenever the state is pushed to the engines state-stack and a `cleanup()` method called whenever the state is changed from the engines state-stack.

A few of the methods take a `std::shared_ptr` to the engine object that called them. These include; `init()`, `handle_events()`, `update()` and `draw()`. This is so you can access a particular engine resource or created your own shared reference.

Derived states use a static self reference to pass instances to the engine. Because of this, any user defined state class that derives from `crank::states::base` need to have (ideally private) a static member of its own type and and a method called `instance()` which returns a static pointer of the states self type. This is declared in the header of the state. In the source file of the state (which should contain the implementation of the derived interface), you also have to fully implement the type of the static member.

e.g.

```cpp
crank::states::basic crank::states::basic::m_basic;
```

A full implementation is available [below](#example).

The base class also interfaces a `pause()` and `resume()` methods which are used to freeze a state in its current state or unfreeze it to resume processing respectivley. These methods are called when a new state is pushed on top of the current state or is popped off the top.

The final requirement for a derived state class is that the default constructor should be _defaulted_ (i.e. `base() = default`) and should be a protected member.

### Data and Shared Resources

One thing to note about states is that you are able to create whatever members and methods you want that can be used by a state but you cannot transfer these variables between states. To this you have to use a global variable model. Crank doesn't enforce a particular model for shared data and resources but the example below implements one for convayence.

---

## Example

Here I will give a full implmentation of a basic state and a main function that runs the engine for a few loop iterations. The state will be called `basic` and will be injected in the `crank::states` namespace. It is **_not_** recommended to inject your own states into this namespace.

### A simple state

Here I have implemented the interface for the `basic` class. The main thing to notice is the use of the static self member and the `instance()` method.

```hpp
#ifndef BASIC_HPP
#define BASIC_HPP 1

#include <crank/crank.hpp>
#include <example/globals.hpp>

#include <string>

namespace crank::states
{

    class basic : public base
    {
    public:

        void init(std::shared_ptr<engine> eng) noexcept;

        void cleanup() noexcept;

        void pause() noexcept;

        void resume() noexcept;

        void handle_events(std::shared_ptr<crank::engine> eng) noexcept;

        void update(std::shared_ptr<crank::engine> eng) noexcept;

        void draw(std::shared_ptr<crank::engine> eng) noexcept;

        static basic* instance()
        { return &m_basic; }

    protected:

        basic() = default;
    
    private:

        static basic m_basic;

    }; /// class basic

} /// namespace crank::states

#endif /// BASIC_HPP
```

The implementation is nothing special, it just prints the current method so it can be seen what is being called and when. There are two things to notice, the first is the first line below the include directives, this helps to complete the type definition of the static member. Second thing to notice is the `global_vars` type. It's `instance()` method is used to access the data through a pointer. The defintition of the `global_vars` class is [below](#global-variables).

```cpp
#include <example/basic.hpp>

#include <iostream>


/// \brief Completes the type definition
crank::states::basic crank::states::basic::m_basic;

namespace crank::states
{   
    void basic::init([[maybe_unused]] std::shared_ptr<crank::engine> eng) noexcept
    { 
        std::cout << "basic::init() with engine ptr count: " << eng.use_count() << std::endl;
        std::cout << "init::m_globals->num = " << global_vars::instance()->num << std::endl;
        std::cout << "init::m_globals->str = " << global_vars::instance()->str << std::endl;

        if (global_vars::instance()->num == 0)
        {
            global_vars::instance()->num = 1;
            global_vars::instance()->str = "hello";
        }
    }

    void basic::cleanup() noexcept
    { std::cout << "basic::cleanup()" << std::endl; }

    void basic::pause() noexcept
    { std::cout << "basic::pause()" << std::endl; }

    void basic::resume() noexcept
    { std::cout << "basic::resume()" << std::endl; }

    void basic::handle_events([[maybe_unused]] std::shared_ptr<crank::engine> eng) noexcept
    { std::cout << "basic::handle_events() with engine ptr count: " << eng.use_count() << std::endl; }

    void basic::update([[maybe_unused]] std::shared_ptr<crank::engine> eng) noexcept
    { std::cout << "basic::update() with engine ptr count: " << eng.use_count() << std::endl; }

    void basic::draw([[maybe_unused]] std::shared_ptr<crank::engine> eng) noexcept
    { std::cout << "basic::draw() with engine ptr count: " << eng.use_count() << std::endl; }

} /// namespace crank
```

### Global variables

The task of sharing data across states is a difficult problem. File crank doesn't offer a direct way to manage shared data through the engine or the states, there is a `crank::data` class that acts as a decorator to create global data.

What you'll notice is the explicit constructor, this is used so that the global data's construction can be specified and customised. Here it only copies the data.

The second thing to notice is that this variation of `global_vars` is similar to how we implemented the `basic` class. A stati self member and a method (`instance()`) for accessing a pointer to the self reference. This allows you to use the `instance()` method to access the global data like a struct pointer.

```hpp
#include <crank/crank.hpp>
#include <string>

class global_vars : public crank::data
{
protected:
    global_vars() = default;

public:
    explicit global_vars(int n, const std::string& s) 
    : num(n) 
    , str(s)
    {}

    static global_vars* instance()
    { return &m_globals; }

private:

    static global_vars m_globals;

public:

    int num;
    std::string str;
};
```

In the main file, you'll have to implement the full type of the `global_vars` class similar to what we did for the `basic` class.

### Making an Engine Object

To create an engine object is super simple, all you need is to include the `<memory>` standard header and use the `std::make_shared` method. To initialise the engine, you have to call the engine's `init()` method with the screen and viewport dimensions along with the engine's `shared_ptr`.

```cpp
#include <crank/crank.hpp>
#include <example/basic.hpp>

#include <memory>
#include <iostream>
#include <string>

auto main() -> int
{
    auto engine = std::make_shared<crank::engine>();

    engine->init({640, 480}, {640, 480}, engine);

    return 0;
}
```

### Final Result

To put it all together we will implement the full type of th `global_var` class and create a short loop that will run through the _IUO_ methods 4 times.

Because we made the the `global_vars` only have a string and int as members, the type of `m_globals` only takes `0` and `"global_var"`.

Also notice how we access the instance of the `basic` state class, in the call to `engine::change_state`, we have to call it through the namespace operators `::`.

```cpp
#include <crank/crank.hpp>
#include <example/basic.hpp>

#include <memory>
#include <iostream>
#include <string>


global_vars global_vars::m_globals(0, "global_var");


auto main() -> int
{
    auto engine = std::make_shared<crank::engine>();

    engine->init({640, 480}, {640, 480}, engine);

    engine->change_state(crank::states::basic::instance());

    std::cout << "---------------------------" << std::endl;

    auto i { 0 }; 
    while (i < 4 && engine->running())
    {
        engine->handle_events();
        engine->update();
        engine->draw();
        std::cout << "shared_ptr: " << engine.use_count() << std::endl;
        std::cout << "loops: " << i++ << "\n---------------------------" << std::endl;
    }

    engine->quit();
    engine->cleanup();

    return 0;
}
```

Output:

```sh
basic::init() with engine ptr count: 3
init::m_globals->num = 0
init::m_globals->str = global_var
---------------------------
basic::handle_events() with engine ptr count: 3
basic::update() with engine ptr count: 3
basic::draw() with engine ptr count: 3
shared_ptr: 2
loops: 0
---------------------------
basic::handle_events() with engine ptr count: 3
basic::update() with engine ptr count: 3
basic::draw() with engine ptr count: 3
shared_ptr: 2
loops: 1
---------------------------
basic::handle_events() with engine ptr count: 3
basic::update() with engine ptr count: 3
basic::draw() with engine ptr count: 3
shared_ptr: 2
loops: 2
---------------------------
basic::handle_events() with engine ptr count: 3
basic::update() with engine ptr count: 3
basic::draw() with engine ptr count: 3
shared_ptr: 2
loops: 3
---------------------------
basic::cleanup()
```

---

## Links and Resources

### bpt

- [bpt](https://bpt.pizza)
- [bpt install guide]()
- [Adding dependencies]()
- [Library dependencies]()

### Trove

- ["Hello World!" with bpt]()
- [Trove](https://trovepi.dev)
- [Using packages from Trove for your projects](https://trovepi.dev)
