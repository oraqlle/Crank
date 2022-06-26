/// -*- C++ -*- Header compatiability <engine.hpp>

/// \brief The basic engine class. Used to manage states and state transistions.
/// \file engine.hpp
///
/// author: Tyler Swann (oraqlle@github.com)
///
/// version: 0.1.0
///
/// date: 27-06-2022
///
/// copyright: Copyright (c) 2022
///
/// license: MIT

#ifndef CRANK_ENGINE_H
#define CRANK_ENGINE_H 1

#include <vector>
#include <utility>
#include <concepts>

namespace crank
{

    namespace details
    {
        struct __dim
        { 
            std::size_t width : 13;
            std::size_t height : 12;
        };
    } /// namespace details


    namespace states 
    {
        class base;
    };


    class engine
    {
    protected:
        static bool m_running;
        bool m_resetting;

        std::vector<states::base*> m_states;
    
    public:
        details::__dim m_window;
        details::__dim m_viewport;

        engine() = default;

        void init(details::__dim&& window, details::__dim&& viewport) noexcept;

        ~engine();

        void cleanup() noexcept;

        void push_state(states::base* state) noexcept;

        void pop_state() noexcept;

        void change_state(states::base* state) noexcept;

        void reset() noexcept;

        void handle_events() noexcept;

        void update() noexcept;
        
        void draw() noexcept;

        void quit() noexcept;
        
        bool running() const noexcept;
        
        bool resetting() const noexcept;
        
    }; /// class engine

} /// namespace crank

#endif /// CRANK_ENGINE_H