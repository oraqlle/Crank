#include <crank/crank.hxx>
#include <example/basic.hxx>

#include <iostream>
#include <string>

using namespace std::literals;

struct id 
    : public crank::states::id_base
{
    enum
    {
        Basic1 = id_base::Base,
        Basic2
    };

};  /// class id

auto main() -> int
{
    auto engine = crank::engine{};
    engine.make_factory_for<crank::states::basic>(id::Basic1, 7, "Basic 1"s);
    engine.make_factory_for<crank::states::basic>(id::Basic2, 55, "Basic 2"s);

    engine.change_state(id::Basic1);

    std::cout << "---------------------------" << std::endl;

    auto i { 0 }; 
    while (i < 4 && engine.running())
    {
        engine.handle_events();
        engine.update();
        engine.render();
        std::cout << "loops: " << i++ << "\n---------------------------" << std::endl;
    }

    engine.push_state(id::Basic2);

    std::cout << "---------------------------" << std::endl;

    while (i < 8 && engine.running())
    {
        engine.handle_events();
        engine.update();
        engine.render();
        std::cout << "loops: " << i++ << "\n---------------------------" << std::endl;
    }

    engine.pop_state();

    while (i < 12 && engine.running())
    {
        engine.handle_events();
        engine.update();
        engine.render();
        std::cout << "loops: " << i++ << "\n---------------------------" << std::endl;
    }

    engine.quit();

    return 0;
}