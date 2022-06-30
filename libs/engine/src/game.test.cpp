#include <crank.hpp>

#include <iostream>
#include <string>


auto main() -> int
{
    auto engine = crank::engine();
    engine.init({640, 480}, {640, 480});

    engine.change_state(crank::states::basic::instance());

    std::cout << "---------------------------" << std::endl;

    auto i { 0 }; 
    while (i < 4 && engine.running())
    {
        engine.handle_events();
        engine.update();
        engine.draw();
        std::cout << "loops: " << i++ << "\n---------------------------" << std::endl;
    }

    engine.push_state(crank::states::basic::instance());

    std::cout << "---------------------------" << std::endl;

    while (i < 8 && engine.running())
    {
        engine.handle_events();
        engine.update();
        engine.draw();
        std::cout << "loops: " << i++ << "\n---------------------------" << std::endl;
    }

    engine.quit();
    engine.cleanup();

    return 0;
}