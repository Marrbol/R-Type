/*
** EPITECH PROJECT, 2023
** RType
** File description:
** entity
*/

#pragma once

#include <cstddef>

class entity {
public:
    explicit entity(std::size_t value) : _data(value) {}

    operator std::size_t() const {
        return _data;
    }

private:
    std::size_t _data = 0;
};
