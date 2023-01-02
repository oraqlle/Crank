/// -*- C++ -*- Header compatiability <base.hpp>

/// \brief Base state abstract virtual class.
/// \file base.hpp
///
/// author: Tyler Swann (oraqlle@github.com)
///
/// version: 0.2.0
///
/// date: 02-01-2023
///
/// copyright: Copyright (c) 2022-2023
///
/// license: MIT

#ifndef CRANK_STATES_BASE
#   define CRANK_STATES_BASE

#include <engine/engine.hxx>

#include <utility>


namespace crank::states
{

    /// \brief Base state 
    ///
    /// \details An abstract virtual class designed 
    /// to create a basic interface for all states.
    /// New states are derived from this class.
    class base
    {
    public:

        /// \brief Default Virtual Destructor
        virtual ~base() = default;


        /// \brief Initialize the state.
        ///
        /// \details Used to initialize the state.
        /// This is called before the state is pushed to.
        /// In the derived states, you can define state
        /// initializer parameters, which are taken by `init`.
        ///
        /// \param eng type: crank::engine&
        virtual void init(crank::engine& eng) noexcept = 0;

        /// \brief Cleanup the state.
        virtual void cleanup() noexcept = 0;
        
        /// \brief Pause the state.
        virtual void pause() noexcept = 0;

        /// \brief Resume the state.
        virtual void resume() noexcept = 0;

        /// \brief Handle events.
        ///
        /// \param eng type: crank::engine&
        virtual void handle_events(crank::engine& eng) noexcept = 0;

        /// \brief Update the state.
        ///
        /// \param eng type: crank::engine&
        virtual void update(crank::engine& eng) noexcept = 0;

        /// \brief Render the state.
        ///
        /// \param eng type: crank::engine&
        virtual void render(crank::engine& eng) noexcept = 0;
        
        /// \brief Change the state.
        ///
        /// \details Used to change the state.
        ///
        /// \param eng type: crank::engine&
        void change_state(crank::engine& eng, base& state) noexcept
        { eng.change_state(state); }

    protected:

        /// \brief Protected default constructor.
        base() = default;
    
    };  /// class base

}  /// namespace crank::states

#endif /// CRANK_STATES_BASE
