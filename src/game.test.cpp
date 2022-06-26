#include <crank.hpp>

auto main() -> int
{
    auto engine = crank::engine();
    engine.init({640, 480}, {640, 480});

    engine.change_state(crank::states::basic::instance());

    auto i { 0 }; 
    while (i++ < 4 || engine.running())
    {
        engine.handle_events();
        engine.update();
        engine.draw();
    }

    return 0;
}