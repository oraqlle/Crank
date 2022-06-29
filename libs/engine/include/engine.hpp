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

/// \brief crank namespace
namespace crank
{

    /// \brief details namespace
    namespace details
    {
        /// \brief Two dimensional sizes. 
        struct dim
        { 
            std::size_t height;
            std::size_t width;
        }; /// struct dim
    
    } /// namespace details


    /// \brief states namespace
    namespace states 
    {
        class base; ///< Forward declaration of states::base class.
    }; /// namespace states


    /// \brief The basic engine class. Used to manage states 
    /// and state transistions.
    class engine
    {
    protected:
        bool m_running;
        bool m_resetting;

        std::vector<states::base*> m_states;
    
    public:

        details::dim m_window;
        details::dim m_viewport;

    public:

        /// \brief Default Constructor.
        engine() = default;


        /// \brief Initializes the engine with 
        /// window and viewport dimensions.
        ///
        /// \details The window and viewport dimensions
        /// are moved into the engine.
        ///
        /// @param window The window dimensions.
        /// type: crank::details::dim | qualifiers: [rvalue]
        /// @param viewport The viewport dimensions.
        /// type: crank::details::dim | qualifiers: [rvalue]
        void init(details::dim&& window, details::dim&& viewport) noexcept;


        /// \brief Destructor.
        ~engine();


        /// \brief Performs clean up 
        ///
        /// \details Cleans up all states that
        /// are stored in the state stack.
        void cleanup() noexcept;


        /// \brief Push a new state.
        ///
        /// \details Push a pointer of a state to
        /// the engine state stack.
        ///
        /// @param state The state to push.
        /// type: crank::states::base*
        void push_state(states::base* state) noexcept;


        /// \brief Pop the last state.
        ///
        /// \details Pops the last pointer to a 
        /// state from the engine state stack.
        void pop_state() noexcept;


        /// \brief Change current state.
        /// 
        /// \details Performs clean up of the last state
        /// on the stack, then pushes a new state.
        void change_state(states::base* state) noexcept;


        /// \brief Reset engine
        ///
        /// \details Performs clean up of all states
        /// on the stack, then resets the engine.
        void reset() noexcept;


        /// \brief Handle events.
        ///
        /// \details Calls the `handle_events` method
        /// of the current (last) state in the stack.
        void handle_events() noexcept;
        

        /// \brief Update.
        ///
        /// \details Calls the `update` method of
        /// the current (last) state in the stack. 
        void update() noexcept;
        

        /// \brief Draw.
        ///
        /// \details Calls the `draw` method of
        /// the current (last) state in the stack.
        void draw() noexcept;


        /// \brief Quit current engine.
        void quit() noexcept;
        

        /// \brief Get running state.
        bool running() const noexcept;
        

        /// \brief Get resetting state.
        bool resetting() const noexcept;
        
    }; /// class engine

} /// namespace crank

#endif /// CRANK_ENGINE_H