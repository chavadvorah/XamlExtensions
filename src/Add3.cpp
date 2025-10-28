#include "pch.h"
#include "Add3.h"
#include "Add3.g.cpp"

namespace winrt::XamlExtensions::implementation {
    IMPLEMENT_INPUT_PROPERTY(Add3, XamlExtensions::Add3, A, double, 0.0)
    IMPLEMENT_INPUT_PROPERTY(Add3, XamlExtensions::Add3, B, double, 0.0)
    IMPLEMENT_INPUT_PROPERTY(Add3, XamlExtensions::Add3, C, double, 0.0)
    IMPLEMENT_RESULT_PROPERTY(Add3, XamlExtensions::Add3, double, 0.0)
    IMPLEMENT_PROPERTY_CHANGED_HANDLER(Add3)

    void Add3::UpdateResult(const mux::DependencyObject& target) {
        double a      = GetA(target);
        double b      = GetB(target);
        double c      = GetC(target);
        double result = a + b + c;
        target.SetValue(m_resultProperty, winrt::box_value(result));
    }
} // namespace winrt::XamlExtensions::implementation
