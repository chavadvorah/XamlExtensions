#include "pch.h"
#include "GridLengthMultiply.h"
#include "GridLengthMultiply.g.cpp"

namespace winrt::XamlExtensions::implementation {
    // Register dependency properties using modular macros
    IMPLEMENT_INPUT_PROPERTY(GridLengthMultiply,
                             XamlExtensions::GridLengthMultiply,
                             A,
                             mux::GridLength,
                             mux::GridLength(0.0))

    IMPLEMENT_INPUT_PROPERTY(GridLengthMultiply,
                             XamlExtensions::GridLengthMultiply,
                             B,
                             double,
                             0.0)

    IMPLEMENT_RESULT_PROPERTY(GridLengthMultiply,
                              XamlExtensions::GridLengthMultiply,
                              mux::GridLength,
                              mux::GridLength(0.0))

    IMPLEMENT_PROPERTY_CHANGED_HANDLER(GridLengthMultiply)

    void GridLengthMultiply::UpdateResult(const mux::DependencyObject& target) {
        mux::GridLength a = GetA(target);
        double          b = GetB(target);

        // Only multiply if A is pixel-based (not Auto or Star)
        if (a.GridUnitType == mux::GridUnitType::Pixel) {
            double          resultValue = a.Value * b;
            mux::GridLength result(resultValue, mux::GridUnitType::Pixel);
            target.SetValue(m_resultProperty, winrt::box_value(result));
        }
    }
} // namespace winrt::XamlExtensions::implementation
