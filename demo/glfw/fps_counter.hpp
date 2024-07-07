////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Vladislav Trifochkin
//
// This file is part of [pfs-griotte](https://github.com/semenovf/pfs-griotte) library.
//
// Changelog:
//      2020.04.24 Initial version
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "pfs/fmt.hpp"

// [An FPS counter](http://www.opengl-tutorial.org/miscellaneous/an-fps-counter/)
template <typename Duration>
class fps_counter
{
    using uintegral_type = unsigned int;
    static constexpr Duration duration_epsilon {Duration{0} / Duration{1}};
    static constexpr uintegral_type default_tune_intervals {3};

    Duration _prev_time_point {0};
    Duration _start_time_point {0};
    Duration _interval {0};
    Duration _frame_duration {0};
    Duration _frame_duration_actual {0};
    uintegral_type _frame_count {0};
    uintegral_type _tune_intervals {default_tune_intervals};

public:
    fps_counter (Duration interval, uintegral_type tune_intervals)
        : _interval(interval)
        , _tune_intervals(tune_intervals)
    {}

    fps_counter (Duration interval) : fps_counter(interval, default_tune_intervals)
    {}

    inline void set_fps (uintegral_type value)
    {
        if (value > 0)
            _frame_duration = Duration{1} / value;
        else
            _frame_duration = Duration{0};

        _tune_intervals = default_tune_intervals;

        fmt::print("Set FPS: {}\n", value);
        fmt::print("Frame duration: {} (fps={})\n", _frame_duration, fps());
    }

    inline auto fps () const -> uintegral_type
    {
        if (_frame_duration <= duration_epsilon)
            return 0;

        auto result = Duration{1} / _frame_duration;
        return static_cast<uintegral_type>(result);
    }

    inline auto fps_actual () const -> uintegral_type
    {
        if (_frame_duration_actual <= duration_epsilon)
            return 0;

        auto result = Duration{1} / _frame_duration_actual;
        return static_cast<uintegral_type>(result);
    }

    void start (Duration tp)
    {
        _start_time_point = tp;

        auto elapsed = _start_time_point - _prev_time_point;

        if (elapsed >= _interval) {
            _frame_duration_actual = elapsed / _frame_count;
            _prev_time_point = _start_time_point;
            _frame_count = 0;

            fmt::print("FPS actual: {} ({})\n", fps_actual(), fps());

            --_tune_intervals;

            if (!_tune_intervals) {
                _tune_intervals = default_tune_intervals;
                _frame_duration = _frame_duration_actual;
            }
        }

        _frame_count++;
    }

    inline bool not_expired (Duration now) const
    {
        return (now - _start_time_point) < _frame_duration;
    }

    inline bool expired (Duration now) const
    {
        return !((now - _start_time_point) < _frame_duration);
    }
};
