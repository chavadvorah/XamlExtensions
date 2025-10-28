#pragma once

#include "pch.h"
#include "Neg.g.h"
#include "AttachedPropertyHelper.h"

namespace winrt::XamlExtensions::implementation {
    struct Neg {
            Neg() = delete;

            DECLARE_INPUT_PROPERTY(A, double)
            DECLARE_RESULT_PROPERTY(double)
            DECLARE_PROPERTY_CHANGED_HANDLER()
            DECLARE_UPDATE_RESULT_HANDLER()
    };
} // namespace winrt::XamlExtensions::implementation

namespace winrt::XamlExtensions::factory_implementation {
    struct Neg : NegT<Neg, implementation::Neg> {};
} // namespace winrt::XamlExtensions::factory_implementation
