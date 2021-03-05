//****************************************************************************
// Copyright © 2021 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2021-01-13.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <stdexcept>

namespace Ypng
{
    class YpngException : public std::runtime_error
    {
    public:
        explicit YpngException(const std::string& message) noexcept
            : std::runtime_error(message)
        {}
    };
}

#define YPNG_THROW_3_(file, line, msg) \
    throw ::Ypng::YpngException(file ":" #line ": " msg)

#define YPNG_THROW_2_(file, line, msg) \
    YPNG_THROW_3_(file, line, msg)

#define YPNG_THROW(msg) \
    YPNG_THROW_2_(__FILE__, __LINE__, msg)
