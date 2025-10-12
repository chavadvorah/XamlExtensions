#include "pch.h"
#include "Divide.h"
#include "Divide.g.cpp"

namespace winrt::XamlExtensions::implementation {
    IMPLEMENT_INPUT_PROPERTY(Divide, XamlExtensions::Divide, A, double, 0.0)
    IMPLEMENT_INPUT_PROPERTY(Divide, XamlExtensions::Divide, B, double, 0.0)
    IMPLEMENT_RESULT_PROPERTY(Divide, XamlExtensions::Divide, double, 0.0)
    IMPLEMENT_PROPERTY_CHANGED_HANDLER(Divide)

    void Divide::UpdateResult(const mux::DependencyObject& target) {
        double a      = GetA(target);
        double b      = GetB(target);
        double result = (b != 0.0) ? (a / b) : 0.0;
        target.SetValue(m_resultProperty, winrt::box_value(result));
    }
} // namespace winrt::XamlExtensions::implementation
