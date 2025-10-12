#include "pch.h"
#include "GridLengthAdd.h"
#include "GridLengthAdd.g.cpp"

namespace winrt::XamlExtensions::implementation {
    IMPLEMENT_INPUT_PROPERTY(GridLengthAdd,
                             XamlExtensions::GridLengthAdd,
                             A,
                             mux::GridLength,
                             mux::GridLength(0.0))
    IMPLEMENT_INPUT_PROPERTY(GridLengthAdd,
                             XamlExtensions::GridLengthAdd,
                             B,
                             mux::GridLength,
                             mux::GridLength(0.0))
    IMPLEMENT_RESULT_PROPERTY(GridLengthAdd,
                              XamlExtensions::GridLengthAdd,
                              mux::GridLength,
                              mux::GridLength(0.0))
    IMPLEMENT_PROPERTY_CHANGED_HANDLER(GridLengthAdd)

    void GridLengthAdd::UpdateResult(const mux::DependencyObject& target) {
        mux::GridLength a = GetA(target);
        mux::GridLength b = GetB(target);

        // Only add if both are pixel-based (not Auto or Star)
        if (a.GridUnitType == mux::GridUnitType::Pixel &&
            b.GridUnitType == mux::GridUnitType::Pixel) {
            double          resultValue = a.Value + b.Value;
            mux::GridLength result(resultValue, mux::GridUnitType::Pixel);
            target.SetValue(m_resultProperty, winrt::box_value(result));
        }
    }
} // namespace winrt::XamlExtensions::implementation
