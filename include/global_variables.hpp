// -*- C++ -*- Header compatiability <global_variables>
/**
 * @file global_variables
 * @author Tyler Swann (oraqlle@github.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H 1

#include <string>

namespace crank
{

    using path = std::string;
    struct g_vars_base 
    {
        std::string g_title = "";
        std::string g_window_name = "";
        path g_window_icon_path = "";
        path g_window_icon_path_alt = "";
    };


    struct g_vars : g_vars_base { };
    
} // namespace crank

#endif // GLOBAL_VARIABLES_H