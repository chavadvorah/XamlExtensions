#include "pch.h"
#include "Add.h"
#include "Add.g.cpp"

namespace winrt::XamlExtensions::implementation
{
    mux::DependencyProperty Add::m_aProperty =
        mux::DependencyProperty::RegisterAttached(
            L"A",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<XamlExtensions::Add>(),
            mux::PropertyMetadata{ winrt::box_value(0.0), mux::PropertyChangedCallback{ &Add::OnInputPropertyChanged } }
        );

    mux::DependencyProperty Add::m_bProperty =
        mux::DependencyProperty::RegisterAttached(
            L"B",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<XamlExtensions::Add>(),
            mux::PropertyMetadata{ winrt::box_value(0.0), mux::PropertyChangedCallback{ &Add::OnInputPropertyChanged } }
        );

    mux::DependencyProperty Add::m_resultProperty =
        mux::DependencyProperty::RegisterAttached(
            L"Result",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<XamlExtensions::Add>(),
            mux::PropertyMetadata{ winrt::box_value(0.0) }
        );

    mux::DependencyProperty Add::AProperty()
    {
        return m_aProperty;
    }

    double Add::GetA(mux::DependencyObject const& target)
    {
        return winrt::unbox_value<double>(target.GetValue(m_aProperty));
    }

    void Add::SetA(mux::DependencyObject const& target, double value)
    {
        target.SetValue(m_aProperty, winrt::box_value(value));
    }

    mux::DependencyProperty Add::BProperty()
    {
        return m_bProperty;
    }

    double Add::GetB(mux::DependencyObject const& target)
    {
        return winrt::unbox_value<double>(target.GetValue(m_bProperty));
    }

    void Add::SetB(mux::DependencyObject const& target, double value)
    {
        target.SetValue(m_bProperty, winrt::box_value(value));
    }

    mux::DependencyProperty Add::ResultProperty()
    {
        return m_resultProperty;
    }

    double Add::GetResult(mux::DependencyObject const& target)
    {
        return winrt::unbox_value<double>(target.GetValue(m_resultProperty));
    }

    void Add::OnInputPropertyChanged(mux::DependencyObject const& d, mux::DependencyPropertyChangedEventArgs const& /*e*/)
    {
        UpdateResult(d);
    }

    void Add::UpdateResult(mux::DependencyObject const& target)
    {
        double a = GetA(target);
        double b = GetB(target);
        double result = a + b;
        target.SetValue(m_resultProperty, winrt::box_value(result));
    }
}
