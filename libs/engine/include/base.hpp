/// -*- C++ -*- Header compatiability <base.hpp>

/// \brief 
/// \file base.hpp
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

#ifndef BASE_HPP
#define BASE_HPP 1

#include <engine.hpp>

namespace crank::states
{

    class base
    {
    public:
        virtual void init() noexcept = 0;

        virtual void cleanup() noexcept = 0;

        virtual void pause() noexcept = 0;

        virtual void resume() noexcept = 0;

        virtual void handle_events(engine* eng) noexcept = 0;

        virtual void update(engine* engine) noexcept = 0;

        virtual void draw(engine* engine) noexcept = 0;

        void change_state(engine* engine, base* state) noexcept
        { engine->change_state(state); }

    protected:
        base() = default;

    }; /// class base

} /// namespace crank::states

#endif /// BASE_HPP