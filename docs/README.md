# XamlExtensions - C++/WinRT Math Utilities

Windows Runtime Component providing XAML-compatible math operations at compile time via attached dependency properties, implemented in C++/WinRT, compatible with WinUI3.

---

## Quick Start

```powershell
# From XamlExtensions directory
.\scripts\build.ps1    # Build
```

---

## Overview

XamlExtensions enables mathematical calculations directly in XAML markup using attached properties and compiled bindings (`x:Bind`).

### Why Attached Properties?

**Alternative approaches that don't work:**
- ❌ **Custom MarkupExtensions** - Cannot be consumed across C#/C++ boundary in WinUI3
- ❌ **Value Converters** - Don't support multi-binding in WinUI3
- ✅ **Attached Properties** - Work perfectly with `x:Bind` compile-time binding

### Usage Pattern

```xaml
xmlns:xe="using:XamlExtensions"

<!-- Create the binding -->
<Element x:Name="ElementName"
         xe:Add.A="100"
         xe:Add.B="50"
         Width="{x:Bind xe:Add.GetResult(ElementName), Mode=OneTime}" />
<!-- Result: Width = 150 -->
```
 - `xe:[Operand].GetResult(target)` can be used in any property that accepts a integral value (i.e. `Width`, `Height`)
 - Use `xe:GridLengthAdd.A/B/GetResult` pattern for any property that accepts a GridLength value.

---

## Consuming XamlExtensions in Your Project

### Required: App Manifest Registration

**CRITICAL:** To use XamlExtensions in an unpackaged WinUI3 C++ application, you **must** register all activatable classes in your application's manifest file.

Add the following to your `app.manifest` (or create one if it doesn't exist):

```xml
<!-- Registration-free WinRT activation -->
<file name="XamlExtensions.dll">
  <activatableClass
    name="XamlExtensions.Add"
    threadingModel="both"
    xmlns="urn:schemas-microsoft-com:winrt.v1" />
  <activatableClass
    name="XamlExtensions.Multiply"
    threadingModel="both"
    xmlns="urn:schemas-microsoft-com:winrt.v1" />
  <activatableClass
    name="XamlExtensions.Divide"
    threadingModel="both"
    xmlns="urn:schemas-microsoft-com:winrt.v1" />
  <activatableClass
    name="XamlExtensions.Neg"
    threadingModel="both"
    xmlns="urn:schemas-microsoft-com:winrt.v1" />
  <activatableClass
    name="XamlExtensions.Add3"
    threadingModel="both"
    xmlns="urn:schemas-microsoft-com:winrt.v1" />
  <activatableClass
    name="XamlExtensions.Multiply3"
    threadingModel="both"
    xmlns="urn:schemas-microsoft-com:winrt.v1" />
  <activatableClass
    name="XamlExtensions.GridLengthAdd"
    threadingModel="both"
    xmlns="urn:schemas-microsoft-com:winrt.v1" />
  <activatableClass
    name="XamlExtensions.GridLengthAdd3"
    threadingModel="both"
    xmlns="urn:schemas-microsoft-com:winrt.v1" />
</file>
```

**Without this registration, XAML cannot instantiate XamlExtensions types and you will get runtime errors.**

### Project Reference

Add XamlExtensions as a project reference in your `.vcxproj`, or ensure the DLL is copied to your output directory.

---

## Architecture

### CRTP-Based Template System

All operations inherit from `AttachedPropertyBase<TDerived, TValue>` to eliminate code duplication.

**Base Template** (`AttachedPropertyHelper.h`):
```cpp
template<typename TDerived, typename TValue>
struct AttachedPropertyBase {
    // Property registration with callback
    template<typename TProjected>
    static mux::DependencyProperty RegisterProperty(const wchar_t* name, TValue defaultValue);

    // Result property (no callback)
    template<typename TProjected>
    static mux::DependencyProperty RegisterResultProperty(const wchar_t* name, TValue defaultValue);

    // Generic getters/setters
    static TValue GetValue(const mux::DependencyObject& target, const mux::DependencyProperty& property);
    static void SetValue(const mux::DependencyObject& target, const mux::DependencyProperty& property, TValue value);

    // Change handler delegates to derived UpdateResult
    static void OnInputPropertyChanged(const mux::DependencyObject& d, const mux::DependencyPropertyChangedEventArgs& e);
};
```

**Helper Macros:**
- `DECLARE_UNARY_OPERATION_PROPERTIES` - One input (e.g., Neg)
- `DECLARE_BINARY_OPERATION_PROPERTIES` - Two inputs (e.g., Add, Multiply)
- `DECLARE_TERNARY_OPERATION_PROPERTIES` - Three inputs (e.g., Add3)
- Corresponding `IMPLEMENT_*` macros for .cpp files

**Type Separation:**
- `TDerived` = Implementation type (e.g., `Add`) - used for CRTP callback
- `TProjected` = WinRT projected type (e.g., `XamlExtensions::Add`) - required by RegisterAttached
- This separation is critical because WinRT needs exact runtime type names

---

## Available Operations

### Math Operations (double)

| Operation | Inputs | Formula | Example XAML |
|-----------|--------|---------|--------------|
| **Add** | A, B | A + B | `xe:Add.A="5" xe:Add.B="3"` → 8 |
| **Multiply** | A, B | A * B | `xe:Multiply.A="4" xe:Multiply.B="3"` → 12 |
| **Divide** | A, B | A / B | `xe:Divide.A="10" xe:Divide.B="2"` → 5 |
| **Neg** | A | -A | `xe:Neg.A="5"` → -5 |
| **Add3** | A, B, C | A + B + C | `xe:Add3.A="1" xe:Add3.B="2" xe:Add3.C="3"` → 6 |
| **Multiply3** | A, B, C | A * B * C | `xe:Multiply3.A="2" xe:Multiply3.B="3" xe:Multiply3.C="4"` → 24 |

**Notes:**
- Divide returns 0.0 if B is zero (divide-by-zero protection)
- All operations trigger automatic recalculation when inputs change

### Layout Operations (GridLength)

| Operation | Inputs | Constraints | Example |
|-----------|--------|-------------|---------|
| **GridLengthAdd** | A, B | Pixel type only | Add two GridLength values |
| **GridLengthAdd3** | A, B, C | Pixel type only | Add three GridLength values |

**Important:** GridLength operations only work with `GridUnitType::Pixel`. If inputs are `Auto` or `Star`, the Result property is not updated (silent failure).

---

## Adding New Operations

### 1. Add to IDL (`XamlExtensions.idl`)

```idl
runtimeclass MyOperation {
    static Microsoft.UI.Xaml.DependencyProperty AProperty{ get; };
    static Double GetA(Microsoft.UI.Xaml.DependencyObject target);
    static void SetA(Microsoft.UI.Xaml.DependencyObject target, Double value);

    static Microsoft.UI.Xaml.DependencyProperty ResultProperty{ get; };
    static Double GetResult(Microsoft.UI.Xaml.DependencyObject target);
}
```

### 2. Create Header (`MyOperation.h`)

```cpp
#pragma once
#include "pch.h"
#include "MyOperation.g.h"
#include "AttachedPropertyHelper.h"

namespace winrt::XamlExtensions::implementation {
    struct MyOperation : AttachedPropertyBase<MyOperation, double> {
        MyOperation() = delete;

        DECLARE_UNARY_OPERATION_PROPERTIES(MyOperation,
                                           XamlExtensions::MyOperation,
                                           double,
                                           0.0)

        static void UpdateResult(const mux::DependencyObject& target);
    };
}

namespace winrt::XamlExtensions::factory_implementation {
    struct MyOperation : MyOperationT<MyOperation, implementation::MyOperation> {};
}
```

### 3. Implement Logic (`MyOperation.cpp`)

```cpp
#include "pch.h"
#include "MyOperation.h"
#include "MyOperation.g.cpp"

namespace winrt::XamlExtensions::implementation {
    IMPLEMENT_UNARY_OPERATION_PROPERTIES(MyOperation,
                                         XamlExtensions::MyOperation,
                                         double,
                                         0.0)

    void MyOperation::UpdateResult(const mux::DependencyObject& target) {
        double a = GetA(target);
        double result = /* your calculation */;
        SetValue(target, m_resultProperty, result);
    }
}
```

### 4. Add to Project

- Add `MyOperation.h` and `MyOperation.cpp` to `XamlExtensions.vcxproj`
- Or use Visual Studio to add files (automatically updates .vcxproj)

### 5. Register in Consuming Application's app.manifest

**CRITICAL STEP:** The consuming application must register the new class for activation.

Edit your application's `app.manifest`:
```xml
<file name="XamlExtensions.dll">
  <!-- ... existing classes ... -->
  <activatableClass
    name="XamlExtensions.MyOperation"
    threadingModel="both"
    xmlns="urn:schemas-microsoft-com:winrt.v1" />
</file>
```

Without this registration, XAML cannot instantiate your WinRT class!

### 6. Rebuild

```powershell
.\scripts\build.ps1
```

---

## Project Structure

```
XamlExtensions/
├── AttachedPropertyHelper.h     # CRTP base template + macros
├── Add.cpp/h                    # Binary: A + B
├── Multiply.cpp/h               # Binary: A * B
├── Divide.cpp/h                 # Binary: A / B (with zero check)
├── Neg.cpp/h                    # Unary: -A
├── Add3.cpp/h                   # Ternary: A + B + C
├── Multiply3.cpp/h              # Ternary: A * B * C
├── GridLengthAdd.cpp/h          # Binary GridLength addition
├── GridLengthAdd3.cpp/h         # Ternary GridLength addition
├── XamlExtensions.idl           # WinRT type definitions
├── XamlExtensions.def           # DLL exports
├── pch.h/cpp                    # Precompiled header
├── XamlExtensions.vcxproj       # MSBuild project
├── packages.config              # NuGet packages
├── scripts/
│   ├── build.ps1                # Build script
│   └── init.ps1                 # NuGet restore + projections
└── docs/                        # Additional documentation
```

---

*Last updated: 2025-10-09*
