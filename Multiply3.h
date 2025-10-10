#pragma once

#include "pch.h"
#include "Multiply3.g.h"
#include "AttachedPropertyHelper.h"

namespace winrt::XamlExtensions::implementation {
    struct Multiply3 : AttachedPropertyBase<Multiply3, double> {
            Multiply3() = delete;

            DECLARE_TERNARY_OPERATION_PROPERTIES(Multiply3,
                                                 XamlExtensions::Multiply3,
                                                 double,
                                                 0.0)

            static void UpdateResult(const mux::DependencyObject& target);
    };
} // namespace winrt::XamlExtensions::implementation

namespace winrt::XamlExtensions::factory_implementation {
    struct Multiply3 : Multiply3T<Multiply3, implementation::Multiply3> {};
} // namespace winrt::XamlExtensions::factory_implementation
