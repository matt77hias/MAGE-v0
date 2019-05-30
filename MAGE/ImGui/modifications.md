# Modifications

### `imconfig.h`

Added:
```cpp
#pragma once

#include "logging\logging.hpp"

...

#define IM_ASSERT(expr)  Assert(expr)

#define IMGUI_DISABLE_OBSOLETE_FUNCTIONS

...

#define IM_VEC2_CLASS_EXTRA \
        ImVec2(const mage::F32x2& f) noexcept : x(f[0u]), y(f[1u]) {} \
        operator mage::F32x2() const noexcept { return { x, y }; }

#define IM_VEC4_CLASS_EXTRA \
        ImVec4(const mage::F32x4& f) noexcept : x(f[0u]), y(f[1u]), z(f[2u]), w(f[3u]) {} \
        operator mage::F32x4() const noexcept { return { x, y, z, w }; }
```

### `imgui_impl_dx11.h`

Added:
```cpp
#pragma once

#include "imgui.h"
```

### `imgui_impl_dx11.cpp`

Replaced:
```cpp
output.col = input.col;\
```
with:
```cpp
output.col.xyz = pow(abs(input.col.xyz), 2.2f);\
output.col.w   = input.col.w;\
```

### `imgui_impl_win32.h`

Added:
```cpp
#pragma once

#include "imgui.h"
```

Uncommented:
```cpp
IMGUI_IMPL_API long     ImGui_ImplWin32_WndProcHandler(void* hWnd, unsigned int msg, unsigned int wParam, long lParam);
```
