/**
 * @file engine.cpp
 * @author Tyler Swann (oraqlle@github.com)
 * @brief source file for the engine class
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../include/engine"
#include "../include/base_state"


namespace crank
{
    void engine::init(DIM&& __window, DIM&& __viewport) noexcept
    {
        m_running = true;
        m_resetting = false;

        d_window = std::move(__window);
        d_viewport = std::move(__viewport);
        
        s_columns = d_viewport.width;
        s_rows = d_viewport.height;
    }

    engine::~engine() noexcept
    { }

    void engine::cleanup() noexcept
    {
        while(!m_states.empty())
        {
            m_states.back()->cleanup();
            m_states.pop_back();
        }
    }


    void engine::push_state(base_state* __state) noexcept
    {
        if (!m_states.empty()) 
        { m_states.back()->pause(); }

        m_states.push_back(__state);
        m_states.back()->init(this);
    }

    void engine::pop_state() noexcept
    {
        if (!m_states.empty())
        {
            m_states.back()->cleanup();
            m_states.pop_back();
        }

        if (!m_states.empty())
        { m_states.back()->resume(); }
    }

    void engine::change_state(base_state* __state) noexcept
    {
        if (!m_states.empty())
        {
            m_states.back()->cleanup();
            m_states.pop_back();
        }

        m_states.push_back(__state);
        m_states.back()->init(this);        
    }

    void engine::reset() noexcept
    {
        m_resetting = true;
        m_running = false;

        this->cleanup();
        this->init(std::forward<DIM>(d_window), std::forward<DIM>(d_viewport));
    }

    void engine::handle_events() noexcept
    {
        if (!m_states.empty())
        { m_states.back()->handle_events(this); }
    }

    void engine::update() noexcept
    {
        if (!m_states.empty())
        { m_states.back()->update(this); }
    }

    void engine::draw() noexcept
    {
        if (!m_states.empty())
        { m_states.back()->draw(this); }
    }

    void engine::quit() noexcept
    { m_running = false; }

    bool engine::running() const noexcept
    { return m_running; }

    bool engine::resetting() const noexcept
    { return m_resetting; }
    
} // namespace crank