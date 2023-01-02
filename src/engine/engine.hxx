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

#ifndef CRANK_ENGINE
#   define CRANK_ENGINE

#include <vector>
#include <utility>
#include <memory>


namespace crank
{
    namespace states 
    {
        class base;  ///< Forward declaration of states::base class.

    }  /// namespace states


    class data;  ///< Forward declaration of crank::data class.


    /// \brief The basic engine class. Used to manage states 
    /// and state transitions.
    class engine
    {
    protected:

        bool m_running;
        bool m_resetting;

        mutable std::vector<std::reference_wrapper<states::base>> m_states;

    public:

        /// \brief Default Constructor.
        engine() = default;

        /// \brief Initializes the engine.
        auto init() noexcept -> void;

        /// \brief Destructor.
        ~engine() = default;

        /// \brief Performs clean up 
        ///
        /// \details Cleans up all states that
        /// are stored in the state stack.
        auto cleanup() noexcept -> void;

        /// \brief Push a new state.
        ///
        /// \details Push a pointer of a state to
        /// the engine state stack.
        ///
        /// \param state The state to push.
        /// type: crank::states::base&
        auto push_state(states::base&) noexcept -> void;

        /// \brief Pop the last state.
        ///
        /// \details Pops the last pointer to a 
        /// state from the engine state stack.
        auto pop_state() noexcept -> void;

        /// \brief Change current state.
        /// 
        /// \details Performs clean up of the last state
        /// on the stack, then pushes a new state.
        auto change_state(states::base& state) noexcept -> void;


        /// \brief Handle events.
        ///
        /// \details Calls the `handle_events` method
        /// of the current (last) state in the stack.
        auto handle_events() noexcept -> void;
        
        /// \brief Update.
        ///
        /// \details Calls the `update` method of
        /// the current (last) state in the stack. 
        auto update() noexcept -> void;
        
        /// \brief Render.
        ///
        /// \details Calls the `render` method of
        /// the current (last) state in the stack.
        auto render() noexcept -> void;

        /// \brief Quit current engine.
        auto quit() noexcept -> void;
        
        /// \brief Get running state.
        auto running() const noexcept -> bool;
        
        /// \brief Get resetting state.
        auto resetting() const noexcept -> bool;
        
    }; /// class engine

} /// namespace crank

#endif /// CRANK_ENGINE_H