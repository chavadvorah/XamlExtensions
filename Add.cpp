#include "pch.h"
#include "Add.h"
#include "Add.g.cpp"

namespace winrt::XamlExtensions::implementation {
    IMPLEMENT_INPUT_PROPERTY(Add, XamlExtensions::Add, A, double, 0.0)
    IMPLEMENT_INPUT_PROPERTY(Add, XamlExtensions::Add, B, double, 0.0)
    IMPLEMENT_RESULT_PROPERTY(Add, XamlExtensions::Add, double, 0.0)
    IMPLEMENT_PROPERTY_CHANGED_HANDLER(Add)

    void Add::UpdateResult(const mux::DependencyObject& target) {
        double a      = GetA(target);
        double b      = GetB(target);
        double result = a + b;
        target.SetValue(m_resultProperty, winrt::box_value(result));
    }
} // namespace winrt::XamlExtensions::implementation
