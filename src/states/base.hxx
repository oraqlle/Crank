/// -*- C++ -*- Header compatiability <base.hpp>

/// \brief Base state abstract virtual class.
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

#include <engine/engine.hxx>

#include <utility>


/// \brief crank::states namespace
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
        /// \param self The shared pointer to this engine.
        /// type: std::shared_ptr<crank::engine>
        virtual void init(std::shared_ptr<crank::engine> eng) noexcept = 0;


        /// \brief Cleanup the state.
        virtual void cleanup() noexcept = 0;
        

        /// \brief Pause the state.
        virtual void pause() noexcept = 0;


        /// \brief Resume the state.
        virtual void resume() noexcept = 0;


        /// \brief Handle events.
        virtual void handle_events(std::shared_ptr<crank::engine> eng) noexcept = 0;


        /// \brief Update the state.
        ///
        /// \param self The shared pointer to this engine.
        /// type: std::shared_ptr<crank::engine>
        virtual void update(std::shared_ptr<crank::engine> eng) noexcept = 0;


        /// \brief Draw the state.
        ///
        /// \param self The shared pointer to this engine.
        /// type: std::shared_ptr<crank::engine>
        virtual void draw(std::shared_ptr<crank::engine> eng) noexcept = 0;
        

        /// \brief Change the state.
        ///
        /// \details Used to change the state.
        ///
        /// \param self The shared pointer to this engine.
        /// type: std::shared_ptr<crank::engine>
        void change_state(std::shared_ptr<crank::engine> eng, base* state) noexcept
        { eng->change_state(state); }

    protected:

        /// \brief Protected default constructor.
        base() = default;
    
    }; /// class base

} /// namespace crank::states

#endif /// BASE_HPP