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
#define BASIC_HPP

#include <engine.hxx>
#include <state_interface.hxx>

#include <string>

/// \brief crank::states namespace
namespace crank::states {

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
class basic : public state_interface {
public:
    explicit basic(int& n, std::string msg, int change_to_id) noexcept;

    void init(crank::engine& eng) noexcept final;

    void cleanup() noexcept final;

    void pause() noexcept final;

    void resume() noexcept final;

    void handle_events(crank::engine& eng) noexcept final;

    void update(crank::engine& eng) noexcept final;

    void render(crank::engine& eng) noexcept final;

protected:
    /// \brief Protected Default Constructor
    basic() = default;

private:
    int& m_i;
    std::string m_msg;
    int m_change_to_id;

}; /// class basic

} /// namespace crank::states

#endif /// BASIC_HPP