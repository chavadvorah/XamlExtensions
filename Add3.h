#pragma once

#include "pch.h"
#include "Add3.g.h"
#include "AttachedPropertyHelper.h"

namespace winrt::XamlExtensions::implementation {
    struct Add3 {
            Add3() = delete;

            DECLARE_INPUT_PROPERTY(A, double)
            DECLARE_INPUT_PROPERTY(B, double)
            DECLARE_INPUT_PROPERTY(C, double)
            DECLARE_RESULT_PROPERTY(double)

        private:
            static void OnInputPropertyChanged(
                const mux::DependencyObject& d,
                const mux::DependencyPropertyChangedEventArgs& /*e*/);
            static void UpdateResult(const mux::DependencyObject& target);
    };
} // namespace winrt::XamlExtensions::implementation

namespace winrt::XamlExtensions::factory_implementation {
    struct Add3 : Add3T<Add3, implementation::Add3> {};
} // namespace winrt::XamlExtensions::factory_implementation
