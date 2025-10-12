#include "pch.h"
#include "Neg.h"
#include "Neg.g.cpp"

namespace winrt::XamlExtensions::implementation {
    IMPLEMENT_INPUT_PROPERTY(Neg, XamlExtensions::Neg, A, double, 0.0)
    IMPLEMENT_RESULT_PROPERTY(Neg, XamlExtensions::Neg, double, 0.0)
    IMPLEMENT_PROPERTY_CHANGED_HANDLER(Neg)

    void Neg::UpdateResult(const mux::DependencyObject& target) {
        double a      = GetA(target);
        double result = -a;
        target.SetValue(m_resultProperty, winrt::box_value(result));
    }
} // namespace winrt::XamlExtensions::implementation
