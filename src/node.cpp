////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Vladislav Trifochkin
//
// This file is part of `griotte-lib`.
//
// Changelog:
//      2024.07.15 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "griotte/node.hpp"
#include <pfs/assert.hpp>

namespace griotte {

void node::insert_before (node * n)
{
    n->_parent = _parent;
    n->_prev = _prev;
    n->_next = this;
    _prev = n;
}

void node::insert_after (node * n)
{
    n->_parent = _parent;
    n->_prev = this;
    n->_next = _next;
    _next = n;
}

void node::remove ()
{
    if (_next != nullptr)
        _next->_prev = _prev;

    if (_prev != nullptr)
        _prev->_next = _next;
}

void node::add_child (node * n)
{
    n->_parent = this;
    n->_prev = nullptr;
    n->_next = nullptr;

    if (_child_first == nullptr) {
        _child_first = n;
    }

    if (_child_last == nullptr) {
        _child_last = n;
    } else {
        n->_prev = _child_last;
        _child_last->_next = n;
        _child_last = n;
    }
}

void node::remove_child (node * n)
{
    if (n->_parent != this)
        return;

    if (_child_first == nullptr)
        return;

    if (n == _child_first && n == _child_last) {
        _child_first = nullptr;
        _child_last = nullptr;
        return;
    }

    node * pos = _child_first;

    while (pos != n && pos != nullptr)
        ++pos;

    // Not found
    if (pos == nullptr)
        return;

    if (pos == _child_first) {
        _child_first = pos->_next;
        PFS__TERMINATE(pos->_next != nullptr, "FIXME");
        pos->_next->_prev = nullptr;
    } else if (pos == _child_last) {
        _child_last = pos->_prev;
        PFS__TERMINATE(pos->_prev != nullptr, "FIXME");
        pos->_prev->_next = nullptr;
    } else {
        pos->_prev->_next = pos->_next;
        pos->_next->_prev = pos->_prev;
    }

    if (_child_first == nullptr)
        _child_last = nullptr;
}

} // namespace griotte

