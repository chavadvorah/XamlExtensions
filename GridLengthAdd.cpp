#include "pch.h"
#include "GridLengthAdd.h"
#include "GridLengthAdd.g.cpp"

namespace winrt::XamlExtensions::implementation
{
    // Register dependency properties using helper macros
    IMPLEMENT_BINARY_OPERATION_PROPERTIES(GridLengthAdd, XamlExtensions::GridLengthAdd, mux::GridLength, mux::GridLength(0.0))

    // Only the operation-specific logic remains
    void GridLengthAdd::UpdateResult(mux::DependencyObject const& target)
    {
        mux::GridLength a = GetA(target);
        mux::GridLength b = GetB(target);

        // Only add if both are pixel-based (not Auto or Star)
        if (a.GridUnitType == mux::GridUnitType::Pixel &&
            b.GridUnitType == mux::GridUnitType::Pixel)
        {
            double resultValue = a.Value + b.Value;
            mux::GridLength result(resultValue, mux::GridUnitType::Pixel);
            SetValue(target, m_resultProperty, result);
        }
    }
}
