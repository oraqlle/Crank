#include <engine.hpp>
#include <base.hpp>
#include <basic.hpp>

#include <iostream>


    crank::states::basic crank::states::basic::m_basic;

namespace crank::states
{
    void basic::init([[maybe_unused]] engine* eng) noexcept
    { std::cout << "basic::init()" << std::endl; }

    void basic::cleanup() noexcept
    { std::cout << "basic::cleanup()" << std::endl; }

    void basic::pause() noexcept
    { std::cout << "basic::pause()" << std::endl; }

    void basic::resume() noexcept
    { std::cout << "basic::resume()" << std::endl; }

    void basic::handle_events([[maybe_unused]] engine* eng) noexcept
    { std::cout << "basic::handle_events()" << std::endl; }

    void basic::update([[maybe_unused]] engine* eng) noexcept
    { std::cout << "basic::update()" << std::endl; }

    void basic::draw([[maybe_unused]] engine* eng) noexcept
    { std::cout << "basic::draw()" << std::endl; }

} /// namespace crank