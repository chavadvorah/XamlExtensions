#pragma once

#include "pch.h"
#include "Add.g.h"
#include "AttachedPropertyHelper.h"

namespace winrt::XamlExtensions::implementation {
    struct Add : AttachedPropertyBase<Add, double> {
            Add() = delete;

            DECLARE_BINARY_OPERATION_PROPERTIES(Add,
                                                XamlExtensions::Add,
                                                double,
                                                0.0)

            static void UpdateResult(const mux::DependencyObject& target);
    };
} // namespace winrt::XamlExtensions::implementation

namespace winrt::XamlExtensions::factory_implementation {
    struct Add : AddT<Add, implementation::Add> {};
} // namespace winrt::XamlExtensions::factory_implementation
