#include "pch.h"
#include "Add3.h"
#include "Add3.g.cpp"

namespace winrt::XamlExtensions::implementation
{
    mux::DependencyProperty Add3::m_aProperty =
        mux::DependencyProperty::RegisterAttached(
            L"A",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<XamlExtensions::Add3>(),
            mux::PropertyMetadata{ winrt::box_value(0.0), mux::PropertyChangedCallback{ &Add3::OnInputPropertyChanged } }
        );

    mux::DependencyProperty Add3::m_bProperty =
        mux::DependencyProperty::RegisterAttached(
            L"B",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<XamlExtensions::Add3>(),
            mux::PropertyMetadata{ winrt::box_value(0.0), mux::PropertyChangedCallback{ &Add3::OnInputPropertyChanged } }
        );

    mux::DependencyProperty Add3::m_cProperty =
        mux::DependencyProperty::RegisterAttached(
            L"C",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<XamlExtensions::Add3>(),
            mux::PropertyMetadata{ winrt::box_value(0.0), mux::PropertyChangedCallback{ &Add3::OnInputPropertyChanged } }
        );

    mux::DependencyProperty Add3::m_resultProperty =
        mux::DependencyProperty::RegisterAttached(
            L"Result",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<XamlExtensions::Add3>(),
            mux::PropertyMetadata{ winrt::box_value(0.0) }
        );

    mux::DependencyProperty Add3::AProperty()
    {
        return m_aProperty;
    }

    double Add3::GetA(mux::DependencyObject const& target)
    {
        return winrt::unbox_value<double>(target.GetValue(m_aProperty));
    }

    void Add3::SetA(mux::DependencyObject const& target, double value)
    {
        target.SetValue(m_aProperty, winrt::box_value(value));
    }

    mux::DependencyProperty Add3::BProperty()
    {
        return m_bProperty;
    }

    double Add3::GetB(mux::DependencyObject const& target)
    {
        return winrt::unbox_value<double>(target.GetValue(m_bProperty));
    }

    void Add3::SetB(mux::DependencyObject const& target, double value)
    {
        target.SetValue(m_bProperty, winrt::box_value(value));
    }

    mux::DependencyProperty Add3::CProperty()
    {
        return m_cProperty;
    }

    double Add3::GetC(mux::DependencyObject const& target)
    {
        return winrt::unbox_value<double>(target.GetValue(m_cProperty));
    }

    void Add3::SetC(mux::DependencyObject const& target, double value)
    {
        target.SetValue(m_cProperty, winrt::box_value(value));
    }

    mux::DependencyProperty Add3::ResultProperty()
    {
        return m_resultProperty;
    }

    double Add3::GetResult(mux::DependencyObject const& target)
    {
        return winrt::unbox_value<double>(target.GetValue(m_resultProperty));
    }

    void Add3::OnInputPropertyChanged(mux::DependencyObject const& d, mux::DependencyPropertyChangedEventArgs const& /*e*/)
    {
        UpdateResult(d);
    }

    void Add3::UpdateResult(mux::DependencyObject const& target)
    {
        double a = GetA(target);
        double b = GetB(target);
        double c = GetC(target);
        double result = a + b + c;
        target.SetValue(m_resultProperty, winrt::box_value(result));
    }
}
