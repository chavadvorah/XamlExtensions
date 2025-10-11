# XamlExtensions - C++/WinRT Math Utilities

Windows Runtime Component providing XAML-compatible math operations at compile time via attached dependency properties, implemented in C++/WinRT, compatible with WinUI3.

---

## Overview

XamlExtensions enables mathematical calculations directly in XAML markup using attached properties and compiled bindings (`x:Bind`).

### Why Attached Properties?

- [❌] **Custom MarkupExtensions** - Cannot be consumed across C#/C++ boundary in WinUI3
- [❌] **Value Converters** - Don't support multi-binding in WinUI3
- [✅] **Attached Properties** - Work with `x:Bind` to produce compile-time binding

### Usage Pattern

```xaml
<Element x:Name="ElementName"
         xe:Add.A="100"
         xe:Add.B="50"
         Width="{x:Bind xe:Add.GetResult(ElementName), Mode=OneTime}" />
<!-- Result: Width = 150 -->
```
See [Available Operation](#available-operations) for more details

---

## Integrating XamlExtensions into Your WinUI3 C++ Project

Follow these steps to add XamlExtensions to your WinUI3 C++/WinRT application.

### Step 1: Clone XamlExtensions

```bash
git clone git@github.com:chavadvorah/XamlExtensions path/to/XamlExtensions
```

### Step 2: Add ProjectReference to Your .vcxproj

Edit your application's `.vcxproj` and add:

```xml
<ItemGroup>
  <ProjectReference Include="path\to\XamlExtensions\XamlExtensions.vcxproj">
    <Project>{ed6ed822-2818-4497-a7b4-cf4971739bfe}</Project>
  </ProjectReference>
</ItemGroup>
```
**CRITICAL:** This forces your project to build (and produce winrt headers for) XamlExtensions prior to building itself. This is required for the compiler to know about the added XamlTypes.

### Step 3: Include XamlExtensions Header in pch.h

Add to your precompiled header (`pch.h`):

```cpp
#include <winrt/XamlExtensions.h>
```

**CRITICAL:** This gives access to the XamlTypes to the xaml compiler, and is **REQUIRED** even if you don't use the C++ code directly.

**Important:** You will need to build XamlExtensions once after including it in your project to get winrt projection headers. You will likely get IntelliSense errors until then.

### Step 4: Register Activatable Classes in app.manifest

**CRITICAL:** Add this to your `app.manifest`. If you don't have an `app.manifest`, create one in your project root:

```xml
<?xml version="1.0" encoding="utf-8"?>
<assembly manifestVersion="1.0" xmlns="urn:schemas-microsoft-com:asm.v1">
  <assemblyIdentity version="1.0.0.0" name="YourApp.app"/>

  <!-- DPI Awareness (recommended for WinUI3) -->
  <application xmlns="urn:schemas-microsoft-com:asm.v3">
    <windowsSettings>
      <dpiAwareness xmlns="http://schemas.microsoft.com/SMI/2016/WindowsSettings">PerMonitorV2</dpiAwareness>
    </windowsSettings>
  </application>

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
</assembly>
```

Then add the manifest to your `.vcxproj`:

```xml
<ItemGroup>
  <Manifest Include="app.manifest" />
</ItemGroup>
```

**CRITICAL:** This is required to register the classes with the xaml compiler. Your project will not build without it.

### Step 5: Use in XAML

You can now use XamlExtensions in your XAML:

```xaml
<Page ...
      xmlns:xe="using:XamlExtensions"
      ... >

<!-- Create the binding -->
<Element x:Name="ElementName"
         xe:Add.A="100"
         xe:Add.B="50"
         Width="{x:Bind xe:Add.GetResult(ElementName), Mode=OneTime}" />
<!-- Result: Width = 150 -->
```

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

## Extending XamlExtensions (Adding New Operations)

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

**Important:** Based on your desired operation, and the operands it takes, you may want to use the `_BINARY_` or `_TERNARY_` versions of macros. Adding more operands would require adding additional macros.

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

**CRITICAL:** The consuming application must register the new class for activation.

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

---

*Last updated: 2025-10-09*
