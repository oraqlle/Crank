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

#include <crank/crank.hpp>
#include <globals.hpp>

#include <string>


/// \brief crank::states namespace
namespace crank::states
{

    /// \brief Basic state
    ///
    /// \details A basic state class designed
    /// to showcase how a state might look.
    ///
    /// \note In the source definition of this state, 
    /// you have to define a `crank::states::<state>` 
    /// object at the top of the file, (below that 
    /// #include directives is ideal and outside the 
    /// `crank::states` namespace).
    /// eg.
    /// ```cpp
    /// crank::states::basic crank::states::basic::m_basic;
    /// ```
    class basic : public base
    {
    public:

        void init() noexcept;

        void cleanup() noexcept;

        void pause() noexcept;

        void resume() noexcept;

        void handle_events(engine* eng) noexcept;

        void update(engine* engine) noexcept;

        void draw(engine* engine) noexcept;

        /// \brief Get the state instance.
        ///
        /// \details Returns a static pointer to 
        /// the state instance held by this state. 
        static basic* instance()
        { return &m_basic; }

    protected:

        /// \brief Protected Default Constructor
        basic() = default;
    
    private:

        /// \brief Static instance of the this 
        /// state type.
        static basic m_basic;

    }; /// class basic

} /// namespace crank::states

#endif /// BASIC_HPP