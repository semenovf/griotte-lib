////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.15 Initial version.
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace griotte {

class node
{
protected:
    void * _pdata {nullptr};       // private data to store specific info, must contains only truv
    node * _parent {nullptr};
    node * _prev   {nullptr};
    node * _next   {nullptr};
    node * _child_first {nullptr}; // Pointer to the first child
    node * _child_last {nullptr};  // Pointer to the last child

public:
    node () = default;
    ~node () = default;

    node (node const &) = delete;
    node (node &&) = delete;
    node & operator = (node const &) = delete;
    node & operator = (node &&) = delete;

    void * pdata () const noexcept
    {
        return _pdata;
    }

    node * first_child ()
    {
        return _child_first;
    }

    node * last_child ()
    {
        return _child_last;
    }

    node * next (node * n)
    {
        return n != nullptr ? n->_next : nullptr;
    }

    node * prev (node * n)
    {
        return n != nullptr ? n->_prev : nullptr;
    }

    /**
     * Insert node before this one.
     */
    void insert_before (node * n, void * pdata);

    /**
     * Insert node after this one.
     */
    void insert_after (node * n, void * pdata);

    /**
     * Remove current node from list
     */
    void remove ();

    /**
     * Add child node
     */
    void add_child (node * n, void * pdata);

    /**
     * Remove child node.
     */
    void remove_child (node * n);
};

} // namespace griotte
