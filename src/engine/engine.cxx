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

// TODO: Add exception handling for non-existing IDs
auto engine::push_state(int id) noexcept -> void
{
    if (!m_state_stack.empty())
        m_state_stack.back()->pause();

    if (!m_state_map.contains(id)) {
        auto state = m_factories.at(id)();
        // auto [_, result] = m_state_map.insert_or_assign(id, state);
        m_state_map.insert_or_assign(id, state);
        m_state_stack.push_back(state);
    } else {
        m_state_stack.push_back(m_state_map.at(id));
    }

    m_state_stack.back()->init(*this);
}

auto engine::pop_state() noexcept -> void
{
    if (!m_state_stack.empty()) {
        m_state_stack.back()->cleanup();
        m_state_stack.pop_back();
    }

    if (!m_state_stack.empty())
        m_state_stack.back()->resume();
}

auto engine::change_state(int id) noexcept -> void
{
    if (!m_state_stack.empty()) {
        m_state_stack.back()->cleanup();
        m_state_stack.pop_back();
    }

    if (!m_state_map.contains(id)) {
        auto state = m_factories.at(id)();
        // auto [_, result] = m_state_map.insert_or_assign(id, state);
        m_state_map.insert_or_assign(id, state);
        m_state_stack.push_back(state);
    } else {
        m_state_stack.push_back(m_state_map.at(id));
    }

    m_state_stack.back()->init(*this);
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

/// \brief Get resetting state.
auto engine::resetting() const noexcept -> bool
{
    return m_resetting;
}

} /// namespace crank
