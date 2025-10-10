#pragma once

#include "pch.h"
#include "GridLengthAdd.g.h"
#include "AttachedPropertyHelper.h"

namespace winrt::XamlExtensions::implementation {
    struct GridLengthAdd : AttachedPropertyBase<GridLengthAdd, mux::GridLength> {
            GridLengthAdd() = delete;

            DECLARE_BINARY_OPERATION_PROPERTIES(GridLengthAdd,
                                                XamlExtensions::GridLengthAdd,
                                                mux::GridLength,
                                                mux::GridLength(0.0))

            static void UpdateResult(const mux::DependencyObject& target);
    };
} // namespace winrt::XamlExtensions::implementation

namespace winrt::XamlExtensions::factory_implementation {
    struct GridLengthAdd : GridLengthAddT<GridLengthAdd, implementation::GridLengthAdd> {};
} // namespace winrt::XamlExtensions::factory_implementation
