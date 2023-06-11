/// -*- C++ -*- Header compatibility <state_interface.hxx>

/// \brief Base state abstract virtual class.
/// \file state_interface.hxx
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

#ifndef CRANK_STATES_STATE_INTERFACE
#define CRANK_STATES_STATE_INTERFACE

#include <engine/crank.hxx>
#include <engine/engine.hxx>

#include <utility>

namespace crank::states {

/// \brief Base State Interface
///
/// \details An abstract virtual class designed
/// to create a basic interface for all states.
/// New states are derived from this class.
class CRANK_PUBLIC state_interface {
public:
    /// \brief Default Virtual Destructor
    virtual ~state_interface() = default;

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
    void change_state(crank::engine& eng, int id) noexcept
    {
        eng.change_state(id);
    }

protected:
    /// \brief Protected default constructor.
    state_interface() = default;

protected:
    int m_id;

}; /// class state_interface

} /// namespace crank::states

#endif /// CRANK_STATES_STATE_INTERFACE
