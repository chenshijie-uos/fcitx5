/*
 * Copyright (C) 2016~2016 by CSSlayer
 * wengxt@gmail.com
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see the file COPYING. If not,
 * see <http://www.gnu.org/licenses/>.
 */
#ifndef _FCITX_UTILS_MISC_H_
#define _FCITX_UTILS_MISC_H_

#include <cstdint>
#include <memory>
#include <utility>

namespace fcitx {

template <class Parent, class Member>
inline std::ptrdiff_t offsetFromPointerToMember(const Member Parent::*ptr_to_member) {
    const Parent *const parent = 0;
    const char *const member = static_cast<const char *>(static_cast<const void *>(&(parent->*ptr_to_member)));
    return std::ptrdiff_t(member - static_cast<const char *>(static_cast<const void *>(parent)));
}

template <class Parent, class Member>
inline Parent *parentFromMember(Member *member, const Member Parent::*ptr_to_member) {
    return static_cast<Parent *>(static_cast<void *>(static_cast<char *>(static_cast<void *>(member)) -
                                                     offsetFromPointerToMember(ptr_to_member)));
}

template <class Parent, class Member>
inline const Parent *parentFromMember(const Member *member, const Member Parent::*ptr_to_member) {
    return static_cast<const Parent *>(static_cast<const void *>(
        static_cast<const char *>(static_cast<const void *>(member)) - offsetFromPointerToMember(ptr_to_member)));
}

template <typename Iter>
class KeyIterator {
public:
    typedef typename Iter::iterator_category iterator_category;
    typedef typename Iter::value_type::first_type value_type;
    typedef typename Iter::difference_type difference_type;
    typedef typename Iter::value_type::first_type &reference;
    typedef typename Iter::value_type::first_type *pointer;

    KeyIterator(Iter iter) : m_iter(iter) {}

    KeyIterator(const KeyIterator &other) = default;

    KeyIterator &operator=(const KeyIterator &other) = default;

    bool operator==(const KeyIterator &other) const noexcept { return m_iter == other.m_iter; }
    bool operator!=(const KeyIterator &other) const noexcept { return !operator==(other); }

    KeyIterator &operator++() {
        m_iter++;
        return *this;
    }

    KeyIterator operator++(int) {
        auto old = m_iter;
        ++(*this);
        return {old};
    }

    reference operator*() { return m_iter->first; }

    pointer operator->() { return &m_iter->first; }

private:
    Iter m_iter;
};

template <class Iter>
class IterRange : std::pair<Iter, Iter> {
public:
    typedef std::pair<Iter, Iter> super;
    using super::pair;
    Iter begin() const { return this->first; }
    Iter end() const { return this->second; }
};
}

#endif // _FCITX_UTILS_MISC_H_
