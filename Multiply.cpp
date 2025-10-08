#include "pch.h"
#include "Multiply.h"
#include "Multiply.g.cpp"

namespace winrt::XamlExtensions::implementation
{
    mux::DependencyProperty Multiply::m_aProperty =
        mux::DependencyProperty::RegisterAttached(
            L"A",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<XamlExtensions::Multiply>(),
            mux::PropertyMetadata{ winrt::box_value(0.0), mux::PropertyChangedCallback{ &Multiply::OnInputPropertyChanged } }
        );

    mux::DependencyProperty Multiply::m_bProperty =
        mux::DependencyProperty::RegisterAttached(
            L"B",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<XamlExtensions::Multiply>(),
            mux::PropertyMetadata{ winrt::box_value(0.0), mux::PropertyChangedCallback{ &Multiply::OnInputPropertyChanged } }
        );

    mux::DependencyProperty Multiply::m_resultProperty =
        mux::DependencyProperty::RegisterAttached(
            L"Result",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<XamlExtensions::Multiply>(),
            mux::PropertyMetadata{ winrt::box_value(0.0) }
        );

    mux::DependencyProperty Multiply::AProperty()
    {
        return m_aProperty;
    }

    double Multiply::GetA(mux::DependencyObject const& target)
    {
        return winrt::unbox_value<double>(target.GetValue(m_aProperty));
    }

    void Multiply::SetA(mux::DependencyObject const& target, double value)
    {
        target.SetValue(m_aProperty, winrt::box_value(value));
    }

    mux::DependencyProperty Multiply::BProperty()
    {
        return m_bProperty;
    }

    double Multiply::GetB(mux::DependencyObject const& target)
    {
        return winrt::unbox_value<double>(target.GetValue(m_bProperty));
    }

    void Multiply::SetB(mux::DependencyObject const& target, double value)
    {
        target.SetValue(m_bProperty, winrt::box_value(value));
    }

    mux::DependencyProperty Multiply::ResultProperty()
    {
        return m_resultProperty;
    }

    double Multiply::GetResult(mux::DependencyObject const& target)
    {
        return winrt::unbox_value<double>(target.GetValue(m_resultProperty));
    }

    void Multiply::OnInputPropertyChanged(mux::DependencyObject const& d, mux::DependencyPropertyChangedEventArgs const& /*e*/)
    {
        UpdateResult(d);
    }

    void Multiply::UpdateResult(mux::DependencyObject const& target)
    {
        double a = GetA(target);
        double b = GetB(target);
        double result = a * b;
        target.SetValue(m_resultProperty, winrt::box_value(result));
    }
}
