#pragma once

#include "pch.h"
#include "Multiply3.g.h"
#include "AttachedPropertyHelper.h"

namespace winrt::XamlExtensions::implementation {
    struct Multiply3 {
            Multiply3() = delete;

            DECLARE_INPUT_PROPERTY(A, double)
            DECLARE_INPUT_PROPERTY(B, double)
            DECLARE_INPUT_PROPERTY(C, double)
            DECLARE_RESULT_PROPERTY(double)
            DECLARE_PROPERTY_CHANGED_HANDLER()
            DECLARE_UPDATE_RESULT_HANDLER()
    };
} // namespace winrt::XamlExtensions::implementation

namespace winrt::XamlExtensions::factory_implementation {
    struct Multiply3 : Multiply3T<Multiply3, implementation::Multiply3> {};
} // namespace winrt::XamlExtensions::factory_implementation
