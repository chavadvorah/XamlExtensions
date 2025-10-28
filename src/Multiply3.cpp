#include "pch.h"
#include "Multiply3.h"
#include "Multiply3.g.cpp"

namespace winrt::XamlExtensions::implementation {
    IMPLEMENT_INPUT_PROPERTY(Multiply3, XamlExtensions::Multiply3, A, double, 0.0)
    IMPLEMENT_INPUT_PROPERTY(Multiply3, XamlExtensions::Multiply3, B, double, 0.0)
    IMPLEMENT_INPUT_PROPERTY(Multiply3, XamlExtensions::Multiply3, C, double, 0.0)
    IMPLEMENT_RESULT_PROPERTY(Multiply3, XamlExtensions::Multiply3, double, 0.0)
    IMPLEMENT_PROPERTY_CHANGED_HANDLER(Multiply3)

    void Multiply3::UpdateResult(const mux::DependencyObject& target) {
        double a      = GetA(target);
        double b      = GetB(target);
        double c      = GetC(target);
        double result = a * b * c;
        target.SetValue(m_resultProperty, winrt::box_value(result));
    }
} // namespace winrt::XamlExtensions::implementation
