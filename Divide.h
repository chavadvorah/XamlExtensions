#pragma once

#include "pch.h"
#include "Divide.g.h"
#include "AttachedPropertyHelper.h"

namespace winrt::XamlExtensions::implementation {
    struct Divide : AttachedPropertyBase<Divide, double> {
            Divide() = delete;

            DECLARE_BINARY_OPERATION_PROPERTIES(Divide,
                                                XamlExtensions::Divide,
                                                double,
                                                0.0)

            static void UpdateResult(const mux::DependencyObject& target);
    };
} // namespace winrt::XamlExtensions::implementation

namespace winrt::XamlExtensions::factory_implementation {
    struct Divide : DivideT<Divide, implementation::Divide> {};
} // namespace winrt::XamlExtensions::factory_implementation
