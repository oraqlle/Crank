#include <example/basic.hxx>

#include <iostream>

namespace crank::states
{   
    basic::basic(int n, std::string msg) noexcept
        : m_i { n }
        , m_msg { msg }
    { }

    void basic::init([[maybe_unused]] crank::engine& eng) noexcept
    {
        std::clog << "i = " << m_i << std::endl;
        std::clog << "msg = " << m_msg << std::endl;
        std::clog << m_msg + " - basic::init()" << std::endl;
        m_i += 1;

        std::clog << "i = " << m_i << std::endl;
    }

    void basic::cleanup() noexcept
    { std::clog << m_msg + " - basic::cleanup()" << std::endl; }

    void basic::pause() noexcept
    { std::clog << m_msg + " - basic::pause()" << std::endl; }

    void basic::resume() noexcept
    { std::clog << m_msg + " - basic::resume()" << std::endl; }

    void basic::handle_events([[maybe_unused]] crank::engine& eng) noexcept
    { 
        std::clog << m_msg + " - basic::handle_events() with i: " << m_i << std::endl; 
        m_i += 1;
    }

    void basic::update([[maybe_unused]] crank::engine& eng) noexcept
    { 
        std::clog << m_msg + " - basic::update() with i: " << m_i << std::endl;
        m_i += 1;
    }

    void basic::render([[maybe_unused]] crank::engine& eng) noexcept
    { 
        std::clog << m_msg + " - basic::render() with i: " << m_i << std::endl;
        m_i += 1; 
    }

} /// namespace crank