/// \brief Shared data
/// \file data.hpp
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

#ifndef DATA_HPP
#define DATA_HPP 1

#include <engine/engine.hpp>

namespace crank
{

    /// \brief Data Class
    ///
    /// \details Used to store shared data between states.
    /// This is a virtual class, and is designed to be inherited
    /// by a user defined class that defines the possible member
    /// variables and methods available.
    ///
    /// \link Have a look at the [global variables](docs/global_data) 
    /// docs and examples for more details.
    class data
    {
    protected:

        data() = default;

    public:
    
        virtual ~data() = default;
    
    }; /// class data

} /// namespace crank

#endif /// DATA_HPP