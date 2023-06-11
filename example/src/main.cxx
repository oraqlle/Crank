#include <basic/basic.hxx>

#include <engine/engine.hxx>
#include <states/id.hxx>
#include <states/state_interface.hxx>

#include <iostream>
#include <string>

using namespace std::literals;

/// State ID's (user side)
enum id { Basic1,
    Basic2 };

auto main() -> int
{
    /// Create an engine
    auto engine = crank::engine {};

    /// Register Two different `Basic` states.
    /// You must register the type of the state
    /// as a template type parameter. We can also
    /// forward values to be used in the construction
    /// of the states. These arguments must follow
    /// the state ID.
    ///
    /// \note: The ID of a state is just an `int`
    /// thus, you can use regular enums as ID's
    /// to help decern ID's.
    engine.make_factory_for<crank::states::basic>(id::Basic1, 7, "Basic 1"s);
    engine.make_factory_for<crank::states::basic>(id::Basic2, 55, "Basic 2"s);

    /// Launch `Basic1` by changing state.
    engine.change_state(id::Basic1);

    std::cout << "---------------------------" << std::endl;

    /// Run full loop four times.
    auto i { 0 };
    while (i < 4 && engine.running()) {
        engine.handle_events();
        engine.update();
        engine.render();
        std::cout << "loops: " << i++ << "\n---------------------------" << std::endl;
    }

    /// Push new state, `Basic2` to stack.
    /// `Basic2` is now the current state.
    engine.push_state(id::Basic2);

    std::cout << "---------------------------" << std::endl;

    /// Run full loop four more times
    /// for new state.
    while (i < 8 && engine.running()) {
        engine.handle_events();
        engine.update();
        engine.render();
        std::cout << "loops: " << i++ << "\n---------------------------" << std::endl;
    }

    /// Pop top state (`Basic2`) from stack.
    /// `Basic1` is once again the current state.
    engine.pop_state();

    /// Run full loop four final times.
    while (i < 12 && engine.running()) {
        engine.handle_events();
        engine.update();
        engine.render();
        std::cout << "loops: " << i++ << "\n---------------------------" << std::endl;
    }

    /// Force the engine to quit.
    engine.quit();

    return 0;
}