#include <crank/crank.hpp>
#include <basic.hpp>

#include <iostream>
#include <string>


global_var global_var::m_globals(0, "global_var");


auto main() -> int
{
    auto engine = crank::engine();

    std::cout << "num: " << global_var::instance()->num << std::endl;
    std::cout << "str: " << global_var::instance()->str << std::endl;

    engine.init({640, 480}, {640, 480}, global_var::instance());

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