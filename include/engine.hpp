// -*- C++ -*- Header compatiability <engine>
/**
 * @file engine
 * @author Tyler Swann (oraqlle@github.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef ENGINE_H
#define ENGINE_H 1

#include <vector>
#include <utility>
#include "global_variables"

namespace crank
{

    struct DIM
    { 
        std::size_t width : 13;
        std::size_t height : 12;
    };

    class base_state;

    class engine
    {
    protected:
        static bool m_running;
        bool m_resetting;

        std::size_t s_columns;
        std::size_t s_rows;

        std::vector<base_state*> m_states;
    
    public:
        DIM d_window;
        DIM d_viewport;

        g_vars_base m_gvars;

        engine() = default;

        void init(DIM&& __window, DIM&& __viewport) noexcept;

        ~engine();

        void cleanup() noexcept;




        void push_state(base_state* __state) noexcept;

        void pop_state() noexcept;

        void change_state(base_state* __state) noexcept;

        void reset() noexcept;




        void handle_events() noexcept;

        void update() noexcept;
        
        void draw() noexcept;




        void quit() noexcept;
        
        bool running() const noexcept;
        
        bool resetting() const noexcept;
    };

} // namespace crank

#endif // ENGINE_H