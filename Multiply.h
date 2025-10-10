#pragma once

#include "pch.h"
#include "Multiply.g.h"
#include "AttachedPropertyHelper.h"

namespace winrt::XamlExtensions::implementation {
    struct Multiply : AttachedPropertyBase<Multiply, double> {
            Multiply() = delete;

            DECLARE_BINARY_OPERATION_PROPERTIES(Multiply,
                                                XamlExtensions::Multiply,
                                                double,
                                                0.0)

            static void UpdateResult(const mux::DependencyObject& target);
    };
} // namespace winrt::XamlExtensions::implementation

namespace winrt::XamlExtensions::factory_implementation {
    struct Multiply : MultiplyT<Multiply, implementation::Multiply> {};
} // namespace winrt::XamlExtensions::factory_implementation
