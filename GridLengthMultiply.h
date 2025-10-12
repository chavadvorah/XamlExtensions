#pragma once

#include "pch.h"
#include "GridLengthMultiply.g.h"
#include "AttachedPropertyHelper.h"

namespace winrt::XamlExtensions::implementation {
    struct GridLengthMultiply {
            GridLengthMultiply() = delete;

            // Declare input properties using modular macros
            DECLARE_INPUT_PROPERTY(A, mux::GridLength)
            DECLARE_INPUT_PROPERTY(B, double)

            // Declare result property
            DECLARE_RESULT_PROPERTY(mux::GridLength)

        private:
            static void OnInputPropertyChanged(
                const mux::DependencyObject& d,
                const mux::DependencyPropertyChangedEventArgs& /*e*/);
            static void UpdateResult(const mux::DependencyObject& target);
    };
} // namespace winrt::XamlExtensions::implementation

namespace winrt::XamlExtensions::factory_implementation {
    struct GridLengthMultiply :
        GridLengthMultiplyT<GridLengthMultiply, implementation::GridLengthMultiply> {
    };
} // namespace winrt::XamlExtensions::factory_implementation
