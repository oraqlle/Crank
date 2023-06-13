#include <basic/basic.hxx>

#include <iostream>

namespace crank::states {
basic::basic(int& n, std::string msg, int change_to_id) noexcept
    : m_i { n }
    , m_msg { msg }
    , m_change_to_id { change_to_id }
{
}

void basic::init([[maybe_unused]] crank::engine& eng) noexcept
{
    std::clog << "i = " << m_i << std::endl;
    std::clog << "msg = " << m_msg << std::endl;
    std::clog << m_msg + " - basic::init()" << std::endl;
}

void basic::cleanup() noexcept
{
    std::clog << m_msg + " - basic::cleanup()" << std::endl;
}

void basic::pause() noexcept
{
    std::clog << m_msg + " - basic::pause()" << std::endl;
}

void basic::resume() noexcept
{
    std::clog << m_msg + " - basic::resume()" << std::endl;
}

void basic::handle_events([[maybe_unused]] crank::engine& eng) noexcept
{
    std::clog << m_msg + " - basic::handle_events() with i: " << m_i << std::endl;
}

void basic::update([[maybe_unused]] crank::engine& eng) noexcept
{
    std::clog << m_msg + " - basic::update() with i: " << m_i << std::endl;

    if (m_i == 3) {
        auto r = eng.push_state(m_change_to_id);
    }

    if (m_i == 7) {
        auto id = eng.pop_state<int>();
    }
}

void basic::render([[maybe_unused]] crank::engine& eng) noexcept
{
    std::clog << m_msg + " - basic::render() with i: " << m_i << std::endl;
}

} /// namespace crank