#include "pch.h"
#include "GridLengthAdd.h"
#include "GridLengthAdd.g.cpp"
#include "winrt/impl/Microsoft.UI.Xaml.2.h"

namespace winrt::XamlExtensions::implementation {
    using typename GL = mux::GridLength;
    IMPLEMENT_INPUT_PROPERTY(GridLengthAdd, XamlExtensions::GridLengthAdd, A, GL, GL(0.0))
    IMPLEMENT_INPUT_PROPERTY(GridLengthAdd, XamlExtensions::GridLengthAdd, B, GL, GL(0.0))
    IMPLEMENT_RESULT_PROPERTY(GridLengthAdd, XamlExtensions::GridLengthAdd, GL, GL(0.0))
    IMPLEMENT_PROPERTY_CHANGED_HANDLER(GridLengthAdd)

    void GridLengthAdd::UpdateResult(const mux::DependencyObject& target) {
        GL a = GetA(target);
        GL b = GetB(target);

        // Only add if both are pixel-based (not Auto or Star)
        if (a.GridUnitType == mux::GridUnitType::Pixel && b.GridUnitType == mux::GridUnitType::Pixel) {
            double resultValue = a.Value + b.Value;
            GL     result(resultValue, mux::GridUnitType::Pixel);
            target.SetValue(m_resultProperty, winrt::box_value(result));
        }
    }
} // namespace winrt::XamlExtensions::implementation
