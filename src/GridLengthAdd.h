#pragma once

#include "pch.h"
#include "GridLengthAdd.g.h"
#include "AttachedPropertyHelper.h"

namespace winrt::XamlExtensions::implementation {
    struct GridLengthAdd {
            GridLengthAdd() = delete;

            DECLARE_INPUT_PROPERTY(A, mux::GridLength)
            DECLARE_INPUT_PROPERTY(B, mux::GridLength)
            DECLARE_RESULT_PROPERTY(mux::GridLength)
            DECLARE_PROPERTY_CHANGED_HANDLER()
            DECLARE_UPDATE_RESULT_HANDLER()
    };
} // namespace winrt::XamlExtensions::implementation

namespace winrt::XamlExtensions::factory_implementation {
    struct GridLengthAdd : GridLengthAddT<GridLengthAdd, implementation::GridLengthAdd> {};
} // namespace winrt::XamlExtensions::factory_implementation
