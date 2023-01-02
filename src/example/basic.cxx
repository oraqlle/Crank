#include <example/basic.hxx>

#include <iostream>


crank::states::basic crank::states::basic::m_basic;

namespace crank::states
{   
    void basic::init([[maybe_unused]] crank::engine& eng) noexcept
    { 
        std::cout << "i = " << i << std::endl;
        i += 1;

        std::cout << "global_vars::instance().num = " << global_vars::instance().num << std::endl;
        std::cout << "global_vars::instance().str = " << global_vars::instance().str << std::endl;

        if (global_vars::instance().num == 0)
        {
            global_vars::instance().num = 1;
            global_vars::instance().str = "hello";
        }
    }

    void basic::cleanup() noexcept
    { std::cout << "basic::cleanup()" << std::endl; }

    void basic::pause() noexcept
    { std::cout << "basic::pause()" << std::endl; }

    void basic::resume() noexcept
    { std::cout << "basic::resume()" << std::endl; }

    void basic::handle_events([[maybe_unused]] crank::engine& eng) noexcept
    { 
        std::cout << "basic::handle_events() with i: " << i << std::endl; 
        i += 1;
    }

    void basic::update([[maybe_unused]] crank::engine& eng) noexcept
    { 
        std::cout << "basic::update() with i: " << i << std::endl;
        i += 1;
    }

    void basic::render([[maybe_unused]] crank::engine& eng) noexcept
    { 
        std::cout << "basic::render() with i: " << i << std::endl;
        i += 1; 
    }

} /// namespace crank