// -*- C++ -*- Header compatiability <base_state>
/**
 * @file base_state
 * @author Tyler Swann (oraqlle@github.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef BASE_STATE_H
#define BASE_STATE_H 1

#include "engine"

namespace crank
{
    class base_state
    {
    protected:
        base_state() { };

    public:
        virtual void init(engine* __engine) noexcept = 0;

        virtual void cleanup() noexcept = 0;

        virtual void pause() noexcept = 0;

        virtual void resume() noexcept = 0;

        virtual void handle_events(engine* __engine) noexcept = 0;

        virtual void update(engine* __engine) noexcept = 0;

        virtual void draw(engine* __engine) noexcept = 0;

        void change_state(engine* __engine, base_state* __state) noexcept
        { __engine->change_state(__state); }
    };

} // namespace crank

#endif // BASE_STATE_H