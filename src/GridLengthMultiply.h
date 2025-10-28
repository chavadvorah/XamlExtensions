#pragma once

#include "pch.h"
#include "GridLengthMultiply.g.h"
#include "AttachedPropertyHelper.h"

namespace winrt::XamlExtensions::implementation {
    struct GridLengthMultiply {
            GridLengthMultiply() = delete;

            DECLARE_INPUT_PROPERTY(A, mux::GridLength)
            DECLARE_INPUT_PROPERTY(B, double)
            DECLARE_RESULT_PROPERTY(mux::GridLength)
            DECLARE_PROPERTY_CHANGED_HANDLER()
            DECLARE_UPDATE_RESULT_HANDLER()
    };
} // namespace winrt::XamlExtensions::implementation

namespace winrt::XamlExtensions::factory_implementation {
    struct GridLengthMultiply : GridLengthMultiplyT<GridLengthMultiply, implementation::GridLengthMultiply> {};
} // namespace winrt::XamlExtensions::factory_implementation
