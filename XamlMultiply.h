#pragma once

#include "XamlMultiply.g.h"

namespace winrt::XamlExtensions::implementation
{
    struct XamlMultiply : XamlMultiplyT<XamlMultiply> {
    public:
        XamlMultiply() = default;
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
    struct XamlMultiply : XamlMultiplyT<XamlMultiply, implementation::XamlMultiply> {
    };
}