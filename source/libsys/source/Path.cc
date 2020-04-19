/*  Copyright (C) 2012-2020 by László Nagy
    This file is part of Bear.

    Bear is a tool to generate compilation database for clang tooling.

    Bear is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Bear is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "libsys/Path.h"

#include <numeric>

namespace {

    std::list<std::string> split_by(const std::string& input, const char sep)
    {
        std::list<std::string> result;

        std::string::size_type previous = 0;
        do {
            const std::string::size_type current = input.find(sep, previous);
            result.emplace_back(input.substr(previous, current - previous));
            previous = (current != std::string::npos) ? current + 1 : current;
        } while (previous != std::string::npos);

        return result;
    }

    std::string join_with(const std::list<std::string>& input, const char sep)
    {
        std::string result;
        std::accumulate(input.begin(), input.end(), result,
                        [&sep](std::string& acc, const std::string& item) {
                            return (acc.empty()) ? item : acc + sep + item;
                        });
        return result;
    }
}

namespace sys::path {

    std::list<std::string> split(const std::string& input)
    {
        return split_by(input, sys::path::OS_PATH_SEPARATOR);
    }

    std::string join(const std::list<std::string>& input)
    {
        return join_with(input, sys::path::OS_PATH_SEPARATOR);
    }
}