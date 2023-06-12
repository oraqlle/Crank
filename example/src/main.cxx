#include <basic/basic.hxx>

#include <engine.hxx>
#include <state_interface.hxx>

#include <iostream>
#include <string>

/// State ID's (user side)
/// Using enums so ID values are named.
enum id {
    Basic1,
    Basic2
};

auto main() -> int
{
    using namespace std::literals;

    /// Create an engine
    auto engine = crank::engine {};

    /// Loop number that will be tracked
    /// in main and by states.
    auto i { 0 };

    /// Register Two different `Basic` states.
    /// You must register the type of the state
    /// as a template type parameter. We can also
    /// forward values to be used in the construction
    /// of the states. These arguments must follow
    /// the state ID.
    ///
    /// \note: The ID of a state is just an `int`
    /// but I have you can use regular enums so
    /// ID values are named to offer better distinction
    /// between ID's and allow ID's to be associated
    /// to the state instance they represent.
    engine.make_factory_for<crank::states::basic>(id::Basic1, std::reference_wrapper<int> { i }, "Basic 1"s, id::Basic2);
    engine.make_factory_for<crank::states::basic>(id::Basic2, std::reference_wrapper<int> { i }, "Basic 2"s, id::Basic1);

    /// Launch `Basic1` by changing state.
    engine.change_state(id::Basic1);

    std::cout << "Block 1" << std::endl;
    std::cout << "---------------------------" << std::endl;

    /// Run full loop four times.
    while (i < 4 && engine.running()) {
        engine.handle_events();
        engine.update();
        engine.render();
        std::cout << "loop #: " << i << "\n---------------------------" << std::endl;
        i += 1;
    }

    // State `Basic2` is now the active state

    std::cout << "Block 2" << std::endl;
    std::cout << "---------------------------" << std::endl;

    /// Run full loop four more times
    /// for new state.
    while (i < 8 && engine.running()) {
        engine.handle_events();
        engine.update();
        engine.render();
        std::cout << "loop #: " << i << "\n---------------------------" << std::endl;
        i += 1;
    }

    /// `Basic1` is once again the current state.

    std::cout << "Block 3" << std::endl;
    std::cout << "---------------------------" << std::endl;

    /// Run full loop four final times.
    while (i < 12 && engine.running()) {
        engine.handle_events();
        engine.update();
        engine.render();
        std::cout << "loop #: " << i << "\n---------------------------" << std::endl;
        i += 1;
    }

    /// Force the engine to quit.
    engine.quit();

    return 0;
}