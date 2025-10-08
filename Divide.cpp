#include "pch.h"
#include "Divide.h"
#include "Divide.g.cpp"

namespace winrt::XamlExtensions::implementation
{
    mux::DependencyProperty Divide::m_aProperty =
        mux::DependencyProperty::RegisterAttached(
            L"A",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<XamlExtensions::Divide>(),
            mux::PropertyMetadata{ winrt::box_value(0.0), mux::PropertyChangedCallback{ &Divide::OnInputPropertyChanged } }
        );

    mux::DependencyProperty Divide::m_bProperty =
        mux::DependencyProperty::RegisterAttached(
            L"B",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<XamlExtensions::Divide>(),
            mux::PropertyMetadata{ winrt::box_value(0.0), mux::PropertyChangedCallback{ &Divide::OnInputPropertyChanged } }
        );

    mux::DependencyProperty Divide::m_resultProperty =
        mux::DependencyProperty::RegisterAttached(
            L"Result",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<XamlExtensions::Divide>(),
            mux::PropertyMetadata{ winrt::box_value(0.0) }
        );

    mux::DependencyProperty Divide::AProperty()
    {
        return m_aProperty;
    }

    double Divide::GetA(mux::DependencyObject const& target)
    {
        return winrt::unbox_value<double>(target.GetValue(m_aProperty));
    }

    void Divide::SetA(mux::DependencyObject const& target, double value)
    {
        target.SetValue(m_aProperty, winrt::box_value(value));
    }

    mux::DependencyProperty Divide::BProperty()
    {
        return m_bProperty;
    }

    double Divide::GetB(mux::DependencyObject const& target)
    {
        return winrt::unbox_value<double>(target.GetValue(m_bProperty));
    }

    void Divide::SetB(mux::DependencyObject const& target, double value)
    {
        target.SetValue(m_bProperty, winrt::box_value(value));
    }

    mux::DependencyProperty Divide::ResultProperty()
    {
        return m_resultProperty;
    }

    double Divide::GetResult(mux::DependencyObject const& target)
    {
        return winrt::unbox_value<double>(target.GetValue(m_resultProperty));
    }

    void Divide::OnInputPropertyChanged(mux::DependencyObject const& d, mux::DependencyPropertyChangedEventArgs const& /*e*/)
    {
        UpdateResult(d);
    }

    void Divide::UpdateResult(mux::DependencyObject const& target)
    {
        double a = GetA(target);
        double b = GetB(target);
        double result = (b != 0.0) ? (a / b) : 0.0;
        target.SetValue(m_resultProperty, winrt::box_value(result));
    }
}
