////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2025.07.18 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "text.hpp"

namespace griotte {

class label_t: public text_t
{
    color_t bgcolor;

public:
    label_t ();
    explicit label_t (std::string content);
    virtual ~label_t ();

    template <typename T, typename ...Args>
    typename std::enable_if<std::is_base_of<item, T>::value, T>::type &
    set_background_item (Args &&... args)
    {
        clear_background_item();

        auto ptr = new T(std::forward<Args>(args)...);
        this->add_child(ptr, ptr);
        return *ptr;
    }

    void render (renderer_ptr_t r) override;

private:
    void clear_background_item ();
};

} // namespace griotte
