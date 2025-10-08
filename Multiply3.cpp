#include "pch.h"
#include "Multiply3.h"
#include "Multiply3.g.cpp"

namespace winrt::XamlExtensions::implementation
{
    mux::DependencyProperty Multiply3::m_aProperty =
        mux::DependencyProperty::RegisterAttached(
            L"A",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<XamlExtensions::Multiply3>(),
            mux::PropertyMetadata{ winrt::box_value(0.0), mux::PropertyChangedCallback{ &Multiply3::OnInputPropertyChanged } }
        );

    mux::DependencyProperty Multiply3::m_bProperty =
        mux::DependencyProperty::RegisterAttached(
            L"B",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<XamlExtensions::Multiply3>(),
            mux::PropertyMetadata{ winrt::box_value(0.0), mux::PropertyChangedCallback{ &Multiply3::OnInputPropertyChanged } }
        );

    mux::DependencyProperty Multiply3::m_cProperty =
        mux::DependencyProperty::RegisterAttached(
            L"C",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<XamlExtensions::Multiply3>(),
            mux::PropertyMetadata{ winrt::box_value(0.0), mux::PropertyChangedCallback{ &Multiply3::OnInputPropertyChanged } }
        );

    mux::DependencyProperty Multiply3::m_resultProperty =
        mux::DependencyProperty::RegisterAttached(
            L"Result",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<XamlExtensions::Multiply3>(),
            mux::PropertyMetadata{ winrt::box_value(0.0) }
        );

    mux::DependencyProperty Multiply3::AProperty()
    {
        return m_aProperty;
    }

    double Multiply3::GetA(mux::DependencyObject const& target)
    {
        return winrt::unbox_value<double>(target.GetValue(m_aProperty));
    }

    void Multiply3::SetA(mux::DependencyObject const& target, double value)
    {
        target.SetValue(m_aProperty, winrt::box_value(value));
    }

    mux::DependencyProperty Multiply3::BProperty()
    {
        return m_bProperty;
    }

    double Multiply3::GetB(mux::DependencyObject const& target)
    {
        return winrt::unbox_value<double>(target.GetValue(m_bProperty));
    }

    void Multiply3::SetB(mux::DependencyObject const& target, double value)
    {
        target.SetValue(m_bProperty, winrt::box_value(value));
    }

    mux::DependencyProperty Multiply3::CProperty()
    {
        return m_cProperty;
    }

    double Multiply3::GetC(mux::DependencyObject const& target)
    {
        return winrt::unbox_value<double>(target.GetValue(m_cProperty));
    }

    void Multiply3::SetC(mux::DependencyObject const& target, double value)
    {
        target.SetValue(m_cProperty, winrt::box_value(value));
    }

    mux::DependencyProperty Multiply3::ResultProperty()
    {
        return m_resultProperty;
    }

    double Multiply3::GetResult(mux::DependencyObject const& target)
    {
        return winrt::unbox_value<double>(target.GetValue(m_resultProperty));
    }

    void Multiply3::OnInputPropertyChanged(mux::DependencyObject const& d, mux::DependencyPropertyChangedEventArgs const& /*e*/)
    {
        UpdateResult(d);
    }

    void Multiply3::UpdateResult(mux::DependencyObject const& target)
    {
        double a = GetA(target);
        double b = GetB(target);
        double c = GetC(target);
        double result = a * b * c;
        target.SetValue(m_resultProperty, winrt::box_value(result));
    }
}
