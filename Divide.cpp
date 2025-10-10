#include "pch.h"
#include "Divide.h"
#include "Divide.g.cpp"

namespace winrt::XamlExtensions::implementation
{
    // Register dependency properties using helper macros
    IMPLEMENT_BINARY_OPERATION_PROPERTIES(Divide, XamlExtensions::Divide, double, 0.0)

    // Only the operation-specific logic remains
    void Divide::UpdateResult(mux::DependencyObject const& target)
    {
        double a = GetA(target);
        double b = GetB(target);
        double result = (b != 0.0) ? (a / b) : 0.0;
        SetValue(target, m_resultProperty, result);
    }
}
