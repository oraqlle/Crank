#include <basic.hpp>

#include <iostream>


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