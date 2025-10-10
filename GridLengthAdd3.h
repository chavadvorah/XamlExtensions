#pragma once

#include "pch.h"
#include "GridLengthAdd3.g.h"
#include "AttachedPropertyHelper.h"

namespace winrt::XamlExtensions::implementation {
    struct GridLengthAdd3 : AttachedPropertyBase<GridLengthAdd3, mux::GridLength> {
            GridLengthAdd3() = delete;

            DECLARE_TERNARY_OPERATION_PROPERTIES(GridLengthAdd3,
                                                 XamlExtensions::GridLengthAdd3,
                                                 mux::GridLength,
                                                 mux::GridLength(0.0))

            static void UpdateResult(const mux::DependencyObject& target);
    };
} // namespace winrt::XamlExtensions::implementation

namespace winrt::XamlExtensions::factory_implementation {
    struct GridLengthAdd3 : GridLengthAdd3T<GridLengthAdd3, implementation::GridLengthAdd3> {};
} // namespace winrt::XamlExtensions::factory_implementation
