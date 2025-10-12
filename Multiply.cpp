#include "pch.h"
#include "Multiply.h"
#include "Multiply.g.cpp"

namespace winrt::XamlExtensions::implementation {
    IMPLEMENT_INPUT_PROPERTY(Multiply, XamlExtensions::Multiply, A, double, 0.0)
    IMPLEMENT_INPUT_PROPERTY(Multiply, XamlExtensions::Multiply, B, double, 0.0)
    IMPLEMENT_RESULT_PROPERTY(Multiply, XamlExtensions::Multiply, double, 0.0)
    IMPLEMENT_PROPERTY_CHANGED_HANDLER(Multiply)

    void Multiply::UpdateResult(const mux::DependencyObject& target) {
        double a      = GetA(target);
        double b      = GetB(target);
        double result = a * b;
        target.SetValue(m_resultProperty, winrt::box_value(result));
    }
} // namespace winrt::XamlExtensions::implementation
