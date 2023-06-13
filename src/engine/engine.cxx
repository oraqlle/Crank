/// \brief source file for the engine class
/// \file engine.cpp
///
/// author: Tyler Swann (tyler.swann05@gmail.com)
///
/// version: 0.2.0
///
/// date: 26-06-2022
///
/// copyright: Copyright (c) 2022-2023
///
/// license: MIT

#include <engine.hxx>
#include <state_interface.hxx>

namespace crank {

engine::~engine() noexcept
{
    while (!m_state_stack.empty()) {
        m_state_stack.back()->cleanup();
        m_state_stack.pop_back();
    }
}

auto engine::handle_events() noexcept -> void
{
    if (!m_state_stack.empty())
        m_state_stack.back()->handle_events(*this);
}

auto engine::update() noexcept -> void
{
    if (!m_state_stack.empty())
        m_state_stack.back()->update(*this);
}

auto engine::render() noexcept -> void
{
    if (!m_state_stack.empty())
        m_state_stack.back()->render(*this);
}

auto engine::quit() noexcept -> void
{
    m_running = false;
}

auto engine::running() const noexcept -> bool
{
    return m_running;
}

} /// namespace crank
