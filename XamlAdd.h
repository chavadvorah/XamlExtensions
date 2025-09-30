#pragma once

#include "XamlAdd.g.h"

namespace winrt::XamlExtensions::implementation
{
    struct XamlAdd : XamlAddT<XamlAdd> {
        public:
            XamlAdd() = default;
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
    struct XamlAdd : XamlAddT<XamlAdd, implementation::XamlAdd> {
    };
}