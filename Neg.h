#pragma once

#include "pch.h"
#include "Neg.g.h"
#include "AttachedPropertyHelper.h"

namespace winrt::XamlExtensions::implementation {
    struct Neg : AttachedPropertyBase<Neg, double> {
            Neg() = delete;

            DECLARE_UNARY_OPERATION_PROPERTIES(Neg,
                                               XamlExtensions::Neg,
                                               double,
                                               0.0)

            static void UpdateResult(const mux::DependencyObject& target);
    };
} // namespace winrt::XamlExtensions::implementation

namespace winrt::XamlExtensions::factory_implementation {
    struct Neg : NegT<Neg, implementation::Neg> {};
} // namespace winrt::XamlExtensions::factory_implementation
