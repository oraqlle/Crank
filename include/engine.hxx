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

#include <algorithm>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

namespace crank {
namespace states {
    class CRANK_PUBLIC state_interface; ///< Forward declaration of states::base_interface class.

} /// namespace states

/// \brief std::variant used as an
/// result monad.
/// \tparam Ok
/// \tparam Err
template <typename Ok, typename Err>
using result_type = std::variant<Ok, Err>;

/// \brief The basic engine class. Used to
/// manage states and state transitions.
class CRANK_PUBLIC engine {
public:
    using size_type = std::size_t;
    using state_ptr_type = std::shared_ptr<states::state_interface>;
    using state_factory_type = std::function<state_ptr_type()>;
    using factory_map_type = std::unordered_map<size_type, state_factory_type>;
    using state_map_type = std::unordered_map<size_type, state_ptr_type>;
    using state_stack_type = std::vector<state_ptr_type>;

    /// \brief Default Constructor.
    engine() noexcept = default;

    /// \brief Destructor.
    ~engine() noexcept;

    /// \brief Registers a state in the engine
    ///
    /// \details Registers a state and creates a
    /// factory function in the engine that enables
    /// generation of the state. Overrides the
    /// existing factory if an ID is reused.
    ///
    /// \tparam State
    /// \tparam ID
    /// \tparam Args...
    /// \param id type: ID
    /// \param args type: Args&&...
    template <typename State, typename ID, typename... Args>
    auto make_factory_for(ID id, Args&&... args) noexcept -> void;

    /// \brief Push a new state.
    ///
    /// \details Push a pointer of the state
    /// with the given ID to stake stack.
    /// Returns a result object that either
    /// contains the unit value (`std::monostate`)
    /// indicating success or a string containing
    /// an error message.
    ///
    /// \tparam ID
    /// \param id type: ID
    ///
    /// \returns result_type<std::monostate, std::string>
    template <typename ID>
    [[nodiscard]] auto push_state(ID id) noexcept
        -> result_type<std::monostate, std::string>;

    /// \brief Pop the last state.
    ///
    /// \details Pops the state at the top
    /// of the state stack. Returns a result
    /// object that either contains the ID
    /// of the popped state indicating
    /// success or a string containing an
    /// error message.
    ///
    /// \returns result_type<ID, std::string>
    template <typename ID>
    [[nodiscard]] auto pop_state() noexcept
        -> result_type<ID, std::string>;

    /// \brief Change current state.
    ///
    /// \details Performs clean up of the state
    /// at the top of the stack, then replaces
    /// it with a new state with the given ID,
    /// either creating it from the state factory
    /// map or from an existing state of the
    /// same ID. Returns a result object that
    /// either contains the unit value (`std::monostate`)
    /// indicating success or a string containing
    /// an error message.
    ///
    /// \tparam ID
    /// \param id type: ID
    ///
    /// \returns result_type<std::monostate, std::string>
    template <typename ID>
    [[nodiscard]] auto change_state(ID id) noexcept
        -> result_type<std::monostate, std::string>;

    /// \brief Handle events.
    ///
    /// \details Calls the `handle_events` method
    /// of the current (last) state in the stack.
    auto handle_events() noexcept -> void;

    /// \brief Update.
    ///
    /// \details Calls the `update` method of
    /// the state at the top of the state stack.
    auto update() noexcept -> void;

    /// \brief Render.
    ///
    /// \details Calls the `render` method of
    /// the state at the top of the state stack.
    auto render() noexcept -> void;

    /// \brief Force quit current engine
    /// and clean up states.
    auto quit() noexcept -> void;

    /// \brief Get running state.
    ///
    /// \returns bool
    [[nodiscard]] auto running() const noexcept -> bool;

private:
    bool m_running = true;
    factory_map_type m_factories;
    state_map_type m_state_map;
    state_stack_type m_state_stack;

}; /// class engine

template <typename State, typename ID, typename... Args>
auto engine::make_factory_for(ID id, Args&&... args) noexcept -> void
{
    auto id_ = static_cast<size_type>(id);
    // auto [_, result] = m_factories.insert_or_assign(id, [... args = std::forward<Args>(args)]() { return std::make_shared<State>(args...); });
    m_factories.insert_or_assign(id_, [... args = std::forward<Args>(args)]() { return std::make_shared<State>(args...); });
}

template <typename ID>
[[nodiscard]] auto engine::push_state(ID id) noexcept
    -> result_type<std::monostate, std::string>
{
    auto id_ = static_cast<size_type>(id);

    if (m_factories.contains(id_)) [[likely]] {

        if (!m_state_stack.empty())
            m_state_stack.back()->pause();

        if (m_state_map.contains(id_)) [[likely]] {
            m_state_stack.push_back(m_state_map.at(id_));
        } else {
            auto state = m_factories.at(id_)();
            // auto [_, result] = m_state_map.insert_or_assign(id, state);
            m_state_map.insert_or_assign(id_, state);
            m_state_stack.push_back(state);
        }

        m_state_stack.back()->init(*this);
        return std::monostate {};
    } else {
        return std::string { "No factory for given ID: " } + std::to_string(id_);
    }
}

template <typename ID>
[[nodiscard]] auto engine::pop_state() noexcept
    -> result_type<ID, std::string>
{
    if (!m_state_stack.empty()) {
        m_state_stack.back()->cleanup();
        auto back = m_state_stack.back();
        m_state_stack.pop_back();

        auto it = std::ranges::find(m_state_map, back, [](auto& kv_pair) { return kv_pair.second; });
        return it->second;
    }

    if (!m_state_stack.empty())
        m_state_stack.back()->resume();
}

template <typename ID>
[[nodiscard]] auto engine::change_state(ID id) noexcept
    -> result_type<std::monostate, std::string>
{
    auto id_ = static_cast<size_type>(id);

    if (m_factories.contains(id_)) [[likely]] {

        if (!m_state_stack.empty()) {
            m_state_stack.back()->cleanup();
            m_state_stack.pop_back();
        }

        if (m_state_map.contains(id_)) [[likely]] {
            m_state_stack.push_back(m_state_map.at(id_));
        } else {
            auto state = m_factories.at(id_)();
            // auto [_, result] = m_state_map.insert_or_assign(id, state);
            m_state_map.insert_or_assign(id_, state);
            m_state_stack.push_back(state);
        }

        m_state_stack.back()->init(*this);
        return std::monostate {};
    } else {
        return std::string { "No factory for given ID: " } + std::to_string(id_);
    }
}

} /// namespace crank

#endif /// CRANK_ENGINE_H