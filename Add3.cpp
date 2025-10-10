#include "pch.h"
#include "Add3.h"
#include "Add3.g.cpp"

namespace winrt::XamlExtensions::implementation
{
    // Register dependency properties using helper macros
    IMPLEMENT_TERNARY_OPERATION_PROPERTIES(Add3, XamlExtensions::Add3, double, 0.0)

    // Only the operation-specific logic remains
    void Add3::UpdateResult(mux::DependencyObject const& target)
    {
        double a = GetA(target);
        double b = GetB(target);
        double c = GetC(target);
        double result = a + b + c;
        SetValue(target, m_resultProperty, result);
    }
}
