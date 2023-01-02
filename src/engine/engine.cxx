/// \brief source file for the engine class
/// \file engine.cpp
/// 
/// author: Tyler Swann (oraqlle@github.com)
/// 
/// version: 0.1.0
/// 
/// date: 26-06-2022
/// 
/// copyright: Copyright (c) 2022
///
/// license: MIT

#include <engine/engine.hxx>
#include <states/base.hxx>


namespace crank
{

    auto engine::init() noexcept -> void
    {
        m_running = true;
        m_resetting = false;
    }

    auto engine::cleanup() noexcept -> void
    {
        while(!m_states.empty())
        {
            m_states.back().get().cleanup();
            m_states.pop_back();
        }
    }

    auto engine::push_state(states::base& state) noexcept -> void
    {
        if (!m_states.empty()) 
            m_states.back().get().pause();

        m_states.push_back(state);
        m_states.back().get().init(*this);
    }

    auto engine::pop_state() noexcept -> void
    {
        if (!m_states.empty())
        {
            m_states.back().get().cleanup();
            m_states.pop_back();
        }

        if (!m_states.empty())
            m_states.back().get().resume();
    }
    
    auto engine::change_state(states::base& state) noexcept -> void
    {
        if (!m_states.empty())
        {
            m_states.back().get().cleanup();
            m_states.pop_back();
        }

        m_states.push_back(state);
        m_states.back().get().init(*this);      
    }

    auto engine::handle_events() noexcept -> void
    {
        if (!m_states.empty())
            m_states.back().get().handle_events(*this);
    }

    auto engine::update() noexcept -> void
    {
        if (!m_states.empty())
            m_states.back().get().update(*this);
    }

    auto engine::render() noexcept -> void
    {
        if (!m_states.empty())
            m_states.back().get().render(*this);
    }

    auto engine::quit() noexcept -> void
    { m_running = false; }


    auto engine::running() const noexcept -> bool
    { return m_running; }

    /// \brief Get resetting state.
    auto engine::resetting() const noexcept -> bool
    { return m_resetting; }
    
} /// namespace crank