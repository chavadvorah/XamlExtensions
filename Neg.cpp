#include "pch.h"
#include "Neg.h"
#include "Neg.g.cpp"

namespace winrt::XamlExtensions::implementation
{
    // Register dependency properties using helper macros
    IMPLEMENT_UNARY_OPERATION_PROPERTIES(Neg, XamlExtensions::Neg, double, 0.0)

    // Only the operation-specific logic remains
    void Neg::UpdateResult(mux::DependencyObject const& target)
    {
        double a = GetA(target);
        double result = -a;
        SetValue(target, m_resultProperty, result);
    }
}
