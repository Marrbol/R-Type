/*
** EPITECH PROJECT, 2023
** RType
** File description:
** sparse array
*/

#pragma once

#include <cstddef>
#include <vector>
#include <optional>

template <typename Component>
class sparse_array {
public:
    using value_type = std::optional<Component>;
    using reference_type = value_type &;
    using const_reference_type = value_type const &;
    using container_t = std::vector<value_type>;
    using size_type = typename container_t::size_type;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

public:
    sparse_array();
    sparse_array(sparse_array const &);
    sparse_array(sparse_array &&) noexcept;
    ~sparse_array();

    sparse_array &operator=(sparse_array const &);
    sparse_array &operator=(sparse_array &&) noexcept;
    reference_type operator[](size_t idx);
    const_reference_type operator[](size_t idx) const;
    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;
    size_type size() const;
    reference_type insert_at(size_type pos, Component const &);
    reference_type insert_at(size_type pos, Component &&);
    template <class... Params>
    reference_type emplace_at(size_type pos, Params &&...);
    void erase(size_type pos);
    size_type get_index(value_type const &) const;

private:
    container_t _data;
};

// IMPLEMENTATION (in header file because of templates)

template<typename Component>
sparse_array<Component>::sparse_array()
{
}

template<typename Component>
sparse_array<Component>::sparse_array(sparse_array const &other)
{
    _data = other._data;
}

template<typename Component>
sparse_array<Component>::sparse_array(sparse_array &&other) noexcept
{
    _data = std::move(other._data);
}

template<typename Component>
sparse_array<Component>::~sparse_array()
{
}

template<typename Component>
sparse_array<Component> &sparse_array<Component>::operator=(sparse_array const &other)
{
    _data = other._data;
    return *this;
}

template<typename Component>
sparse_array<Component> &sparse_array<Component>::operator=(sparse_array &&other) noexcept
{
    _data = std::move(other._data);
    return *this;
}

template<typename Component>
typename sparse_array<Component>::reference_type sparse_array<Component>::operator[](size_t idx)
{
    return _data[idx];
}

template<typename Component>
typename sparse_array<Component>::const_reference_type sparse_array<Component>::operator[](size_t idx) const
{
    return _data[idx];
}

template<typename Component>
typename sparse_array<Component>::iterator sparse_array<Component>::begin()
{
    return _data.begin();
}

template<typename Component>
typename sparse_array<Component>::const_iterator sparse_array<Component>::begin() const
{
    return _data.begin();
}

template<typename Component>
typename sparse_array<Component>::const_iterator sparse_array<Component>::cbegin() const
{
    return _data.cbegin();
}

template<typename Component>
typename sparse_array<Component>::iterator sparse_array<Component>::end()
{
    return _data.end();
}

template<typename Component>
typename sparse_array<Component>::const_iterator sparse_array<Component>::end() const
{
    return _data.end();
}

template<typename Component>
typename sparse_array<Component>::const_iterator sparse_array<Component>::cend() const
{
    return _data.cend();
}

template<typename Component>
typename sparse_array<Component>::size_type sparse_array<Component>::size() const
{
    return _data.size();
}

template<typename Component>
typename sparse_array<Component>::reference_type sparse_array<Component>::insert_at(size_type pos, Component const &component)
{
    _data.insert(_data.begin() + pos, std::optional<Component>(component));
    return _data[pos];
}

template<typename Component>
typename sparse_array<Component>::reference_type sparse_array<Component>::insert_at(size_type pos, Component &&component)
{
    _data.insert(_data.begin() + pos, std::optional<Component>(component));
    return _data[pos];
}

template<typename Component>
template<class... Params>

typename sparse_array<Component>::reference_type sparse_array<Component>::emplace_at(size_type pos, Params &&...params)
{
    _data.insert(_data.begin() + pos, std::optional<Component>(Component(std::forward<Params>(params)...)));
    return _data[pos];
}

template<typename Component>
void sparse_array<Component>::erase(size_type pos)
{
    _data[pos] = std::nullopt;
}

template<typename Component>
typename sparse_array<Component>::size_type sparse_array<Component>::get_index(value_type const &component) const
{
    for (size_type i = 0; i < _data.size(); i++) {
        if (std::addressof(_data[i]) == std::addressof(component))
            return i;
    }
    return -1;
}
