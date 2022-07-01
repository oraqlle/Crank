#include <crank/crank.hpp>
#include <basic.hpp>

#include <iostream>
#include <string>


global_vars global_vars::m_globals(0, "global_var");


auto main() -> int
{
    auto engine = std::make_shared<crank::engine>();

    std::cout << "shared_ptr: " << engine.use_count() << std::endl;

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

    engine->push_state(crank::states::basic::instance());

    std::cout << "---------------------------" << std::endl;

    while (i < 8 && engine->running())
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