#include "pch.h"
#include "GridLengthAdd3.h"
#include "GridLengthAdd3.g.cpp"

namespace winrt::XamlExtensions::implementation {
    IMPLEMENT_INPUT_PROPERTY(GridLengthAdd3,
                             XamlExtensions::GridLengthAdd3,
                             A,
                             mux::GridLength,
                             mux::GridLength(0.0))
    IMPLEMENT_INPUT_PROPERTY(GridLengthAdd3,
                             XamlExtensions::GridLengthAdd3,
                             B,
                             mux::GridLength,
                             mux::GridLength(0.0))
    IMPLEMENT_INPUT_PROPERTY(GridLengthAdd3,
                             XamlExtensions::GridLengthAdd3,
                             C,
                             mux::GridLength,
                             mux::GridLength(0.0))
    IMPLEMENT_RESULT_PROPERTY(GridLengthAdd3,
                              XamlExtensions::GridLengthAdd3,
                              mux::GridLength,
                              mux::GridLength(0.0))
    IMPLEMENT_PROPERTY_CHANGED_HANDLER(GridLengthAdd3)

    void GridLengthAdd3::UpdateResult(const mux::DependencyObject& target) {
        mux::GridLength a = GetA(target);
        mux::GridLength b = GetB(target);
        mux::GridLength c = GetC(target);

        // Only add if all three are pixel-based (not Auto or Star)
        if (a.GridUnitType == mux::GridUnitType::Pixel &&
            b.GridUnitType == mux::GridUnitType::Pixel &&
            c.GridUnitType == mux::GridUnitType::Pixel) {
            double          resultValue = a.Value + b.Value + c.Value;
            mux::GridLength result(resultValue, mux::GridUnitType::Pixel);
            target.SetValue(m_resultProperty, winrt::box_value(result));
        }
    }
} // namespace winrt::XamlExtensions::implementation
