#include <engine/src/engine.hpp>
#include <states/src/base.hpp>
#include <states/src/basic.hpp>

#include <iostream>

namespace crank
{

    void states::basic::init() noexcept
    { std::cout << "basic::init()" << std::endl; }

    void states::basic::cleanup() noexcept
    { std::cout << "basic::cleanup()" << std::endl; }

    void states::basic::pause() noexcept
    { std::cout << "basic::pause()" << std::endl; }

    void states::basic::resume() noexcept
    { std::cout << "basic::resume()" << std::endl; }

    void states::basic::handle_events(engine& eng) noexcept
    { std::cout << "basic::handle_events()" << std::endl; }

    void states::basic::update(engine& eng) noexcept
    { std::cout << "basic::update()" << std::endl; }

    void states::basic::draw(engine& eng) noexcept
    { std::cout << "basic::draw()" << std::endl; }

} /// namespace crank