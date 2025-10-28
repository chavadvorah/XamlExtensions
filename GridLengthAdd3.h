#pragma once

#include "pch.h"
#include "GridLengthAdd3.g.h"
#include "AttachedPropertyHelper.h"

namespace winrt::XamlExtensions::implementation {
    struct GridLengthAdd3 {
            GridLengthAdd3() = delete;

            DECLARE_INPUT_PROPERTY(A, mux::GridLength)
            DECLARE_INPUT_PROPERTY(B, mux::GridLength)
            DECLARE_INPUT_PROPERTY(C, mux::GridLength)
            DECLARE_RESULT_PROPERTY(mux::GridLength)
            DECLARE_PROPERTY_CHANGED_HANDLER()
            DECLARE_UPDATE_RESULT_HANDLER()
    };
} // namespace winrt::XamlExtensions::implementation

namespace winrt::XamlExtensions::factory_implementation {
    struct GridLengthAdd3 : GridLengthAdd3T<GridLengthAdd3, implementation::GridLengthAdd3> {};
} // namespace winrt::XamlExtensions::factory_implementation
