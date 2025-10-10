#include "pch.h"
#include "Multiply.h"
#include "Multiply.g.cpp"

namespace winrt::XamlExtensions::implementation
{
    // Register dependency properties using helper macros
    IMPLEMENT_BINARY_OPERATION_PROPERTIES(Multiply, XamlExtensions::Multiply, double, 0.0)

    // Only the operation-specific logic remains
    void Multiply::UpdateResult(mux::DependencyObject const& target)
    {
        double a = GetA(target);
        double b = GetB(target);
        double result = a * b;
        SetValue(target, m_resultProperty, result);
    }
}
