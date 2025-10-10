#include "pch.h"
#include "Add.h"
#include "Add.g.cpp"

namespace winrt::XamlExtensions::implementation {
    // Register dependency properties using helper macros
    IMPLEMENT_BINARY_OPERATION_PROPERTIES(Add, XamlExtensions::Add, double, 0.0)

    // Only the operation-specific logic remains
    void Add::UpdateResult(const mux::DependencyObject& target) {
        double a      = GetA(target);
        double b      = GetB(target);
        double result = a + b;
        SetValue(target, m_resultProperty, result);
    }
} // namespace winrt::XamlExtensions::implementation
