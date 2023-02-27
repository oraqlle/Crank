/// -*- C++ -*- Header compatibility <basic.hxx>

/// \brief 
/// \file basic.hxx
///
/// author: Tyler Swann (tyler.swann05@gmail.com)
///
/// version: 0.2.0
///
/// date: 28-02-2023
///
/// copyright: Copyright (c) 2022-2023
///
/// license: MIT

#ifndef BASIC_HPP
#   define BASIC_HPP

#include <crank/crank.hxx>

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
    class basic : public state_interface
    {
    public:

        explicit basic(int n, std::string msg) noexcept;

        void init(crank::engine& eng) noexcept;

        void cleanup() noexcept;

        void pause() noexcept;

        void resume() noexcept;

        void handle_events(crank::engine& eng) noexcept;

        void update(crank::engine& eng) noexcept;

        void render(crank::engine& eng) noexcept;

        /// \brief Get the state instance.
        ///
        /// \details Returns a static pointer to 
        /// the state instance held by this state. 
        // static basic& instance()
        // { return m_basic; }

    protected:

        /// \brief Protected Default Constructor
        basic() = default;
    
    private:

        /// \brief Static instance of the this 
        /// state type.
        // static basic m_basic;

        int m_i;
        std::string m_msg;

    }; /// class basic

} /// namespace crank::states

#endif /// BASIC_HPP