/// -*- C++ -*- Header compatiability <basic.hpp>

/// \brief 
/// \file basic.hpp
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

#ifndef BASIC_HPP
#define BASIC_HPP 1

#include <engine.hpp>
#include <base.hpp>

namespace crank
{
    namespace states
    {
        class basic : public base
        {
        protected:
            basic() { };
        
        private:
            static basic m_basic;

        public:
            void init() noexcept;

            void cleanup() noexcept;

            void pause() noexcept;

            void resume() noexcept;

            void handle_events(engine& eng) noexcept;

            void update(engine& engine) noexcept;

            void draw(engine& engine) noexcept;

            static basic* instance()
            { return &m_basic; }

        }; /// class basic

    } /// namespace states

} /// namespace crank

#endif /// BASIC_HPP