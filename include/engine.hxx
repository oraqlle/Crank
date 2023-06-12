/// -*- C++ -*- Header compatibility <engine.hxx>

/// \brief The basic engine class. Used to manage states and state transitions.
/// \file engine.hxx
///
/// author: Tyler Swann (tyler.swann05@gmail.com)
///
/// version: 0.2.0
///
/// date: 27-02-2023
///
/// copyright: Copyright (c) 2022-2023
///
/// license: MIT

#ifndef CRANK_ENGINE
#define CRANK_ENGINE

#include <crank.hxx>

#include <functional>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

namespace crank {
namespace states {
    class CRANK_PUBLIC state_interface; ///< Forward declaration of states::base_interface class.

} /// namespace states

/// \brief The basic engine class. Used to manage states
/// and state transitions.
class CRANK_PUBLIC engine {
public:
    using state_ptr_type = std::shared_ptr<states::state_interface>;
    using state_factory_type = std::function<state_ptr_type()>;
    using factory_map_type = std::unordered_map<int, state_factory_type>;
    using state_map_type = std::unordered_map<int, state_ptr_type>;
    using state_stack_type = std::vector<state_ptr_type>;

public:
    /// \brief Default Constructor.
    engine() noexcept;

    /// \brief Destructor.
    ~engine() noexcept;

    /// \brief Registers a state in the engine
    ///
    /// \details Registers a state and creates a
    /// factory function in the engine that enables
    /// generation of the state.
    ///
    /// \tparam State
    /// \tparam Args...
    /// \param id type: int
    /// \param args type: Args&&...
    template <typename State, typename... Args>
    auto make_factory_for(int id, Args&&... args) noexcept -> void;

    /// \brief Push a new state.
    ///
    /// \details Push a pointer of a state to
    /// the engine state stack.
    ///
    /// \param state The state to push.
    /// type: crank::states::state_interface&
    auto push_state(int id) noexcept -> void;

    /// \brief Pop the last state.
    ///
    /// \details Pops the last pointer to a
    /// state from the engine state stack.
    auto pop_state() noexcept -> void;

    /// \brief Change current state.
    ///
    /// \details Performs clean up of the last state
    /// on the stack, then pushes a new state.
    auto change_state(int id) noexcept -> void;

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

protected:
    bool m_running;
    bool m_resetting;
    factory_map_type m_factories;
    state_map_type m_state_map;
    state_stack_type m_state_stack;

}; /// class engine

template <typename State, typename... Args>
auto engine::make_factory_for(int id, Args&&... args) noexcept -> void
{
    auto [_, result] = m_factories.insert_or_assign(id, [... args = std::forward<Args>(args)]() { return std::make_shared<State>(args...); });
}

} /// namespace crank

#endif /// CRANK_ENGINE_H