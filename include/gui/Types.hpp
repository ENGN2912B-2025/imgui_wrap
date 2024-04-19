//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#pragma once

#include <array>

namespace gui
{
  template <typename T>
  struct Vec2
  {
    T x, y;

    using value_type = T;

    template <typename U>
    Vec2<U> cast() const
    {
      return {static_cast<U>(x), static_cast<U>(y)};
    }

    template <typename U>
    std::array<U, 2> to() const
    {
      return {static_cast<U>(x), static_cast<U>(y)};
    }
  };

  using Vec2i = Vec2<int>;

  template <typename V, typename U>
  static V make(const U& x, const U& y)
  {
    using T = typename V::value_type;
    return V{static_cast<T>(x), static_cast<T>(y)};
  }

} // namespace gui
