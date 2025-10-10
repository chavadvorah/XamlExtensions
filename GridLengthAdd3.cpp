#include "pch.h"
#include "GridLengthAdd3.h"
#include "GridLengthAdd3.g.cpp"

namespace winrt::XamlExtensions::implementation
{
    // Register dependency properties using helper macros
    IMPLEMENT_TERNARY_OPERATION_PROPERTIES(GridLengthAdd3, XamlExtensions::GridLengthAdd3, mux::GridLength, mux::GridLength(0.0))

    // Only the operation-specific logic remains
    void GridLengthAdd3::UpdateResult(mux::DependencyObject const& target)
    {
        mux::GridLength a = GetA(target);
        mux::GridLength b = GetB(target);
        mux::GridLength c = GetC(target);

        // Only add if all three are pixel-based (not Auto or Star)
        if (a.GridUnitType == mux::GridUnitType::Pixel &&
            b.GridUnitType == mux::GridUnitType::Pixel &&
            c.GridUnitType == mux::GridUnitType::Pixel)
        {
            double resultValue = a.Value + b.Value + c.Value;
            mux::GridLength result(resultValue, mux::GridUnitType::Pixel);
            SetValue(target, m_resultProperty, result);
        }
    }
}
