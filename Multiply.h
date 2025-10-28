#pragma once

#include "pch.h"
#include "Multiply.g.h"
#include "AttachedPropertyHelper.h"

namespace winrt::XamlExtensions::implementation {
    struct Multiply {
            Multiply() = delete;

            DECLARE_INPUT_PROPERTY(A, double)
            DECLARE_INPUT_PROPERTY(B, double)
            DECLARE_RESULT_PROPERTY(double)
            DECLARE_PROPERTY_CHANGED_HANDLER()
            DECLARE_UPDATE_RESULT_HANDLER()
    };
} // namespace winrt::XamlExtensions::implementation

namespace winrt::XamlExtensions::factory_implementation {
    struct Multiply : MultiplyT<Multiply, implementation::Multiply> {};
} // namespace winrt::XamlExtensions::factory_implementation
