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

engine::engine() noexcept
    : m_running { true }
    , m_resetting { false }
    , m_factories { engine::factory_map_type {} }
    , m_states { engine::state_type {} }
{
}

engine::~engine() noexcept
{
    while (!m_states.empty()) {
        m_states.back()->cleanup();
        m_states.pop_back();
    }
}

auto engine::push_state(int id) noexcept -> void
{
    if (!m_states.empty())
        m_states.back()->pause();

    m_states.push_back(m_factories[id]());
    m_states.back()->init(*this);
}

auto engine::pop_state() noexcept -> void
{
    if (!m_states.empty()) {
        m_states.back()->cleanup();
        m_states.pop_back();
    }

    if (!m_states.empty())
        m_states.back()->resume();
}

auto engine::change_state(int id) noexcept -> void
{
    if (!m_states.empty()) {
        m_states.back()->cleanup();
        m_states.pop_back();
    }

    m_states.push_back(m_factories[id]());
    m_states.back()->init(*this);
}

auto engine::handle_events() noexcept -> void
{
    if (!m_states.empty())
        m_states.back()->handle_events(*this);
}

auto engine::update() noexcept -> void
{
    if (!m_states.empty())
        m_states.back()->update(*this);
}

auto engine::render() noexcept -> void
{
    if (!m_states.empty())
        m_states.back()->render(*this);
}

auto engine::quit() noexcept -> void
{
    m_running = false;
}

auto engine::running() const noexcept -> bool
{
    return m_running;
}

/// \brief Get resetting state.
auto engine::resetting() const noexcept -> bool
{
    return m_resetting;
}

} /// namespace crank