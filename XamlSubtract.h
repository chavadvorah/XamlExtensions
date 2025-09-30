#pragma once

#include "XamlSubtract.g.h"

namespace winrt::XamlExtensions::implementation
{
    struct XamlSubtract : XamlSubtractT<XamlSubtract> {
    public:
        XamlSubtract() = default;
        void A(double value) { m_A = value; }
        void B(double value) { m_B = value; }
        double A() { return m_A; }
        double B() { return m_B; }

        double ProvideValue();

    private:
        double m_A;
        double m_B;
    };
}

namespace winrt::XamlExtensions::factory_implementation
{
    struct XamlSubtract : XamlSubtractT<XamlSubtract, implementation::XamlSubtract> {
    };
}