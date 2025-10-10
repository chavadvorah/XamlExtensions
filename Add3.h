#pragma once

#include "pch.h"
#include "Add3.g.h"
#include "AttachedPropertyHelper.h"

namespace winrt::XamlExtensions::implementation {
    struct Add3 : AttachedPropertyBase<Add3, double> {
            Add3() = delete;

            DECLARE_TERNARY_OPERATION_PROPERTIES(Add3,
                                                 XamlExtensions::Add3,
                                                 double,
                                                 0.0)

            static void UpdateResult(const mux::DependencyObject& target);
    };
} // namespace winrt::XamlExtensions::implementation

namespace winrt::XamlExtensions::factory_implementation {
    struct Add3 : Add3T<Add3, implementation::Add3> {};
} // namespace winrt::XamlExtensions::factory_implementation
