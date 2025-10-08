#include "pch.h"
#include "Neg.h"
#include "Neg.g.cpp"

namespace winrt::XamlExtensions::implementation
{
    mux::DependencyProperty Neg::m_aProperty =
        mux::DependencyProperty::RegisterAttached(
            L"A",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<XamlExtensions::Neg>(),
            mux::PropertyMetadata{ winrt::box_value(0.0), mux::PropertyChangedCallback{ &Neg::OnInputPropertyChanged } }
        );

    mux::DependencyProperty Neg::m_resultProperty =
        mux::DependencyProperty::RegisterAttached(
            L"Result",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<XamlExtensions::Neg>(),
            mux::PropertyMetadata{ winrt::box_value(0.0) }
        );

    mux::DependencyProperty Neg::AProperty()
    {
        return m_aProperty;
    }

    double Neg::GetA(mux::DependencyObject const& target)
    {
        return winrt::unbox_value<double>(target.GetValue(m_aProperty));
    }

    void Neg::SetA(mux::DependencyObject const& target, double value)
    {
        target.SetValue(m_aProperty, winrt::box_value(value));
    }

    mux::DependencyProperty Neg::ResultProperty()
    {
        return m_resultProperty;
    }

    double Neg::GetResult(mux::DependencyObject const& target)
    {
        return winrt::unbox_value<double>(target.GetValue(m_resultProperty));
    }

    void Neg::OnInputPropertyChanged(mux::DependencyObject const& d, mux::DependencyPropertyChangedEventArgs const& /*e*/)
    {
        UpdateResult(d);
    }

    void Neg::UpdateResult(mux::DependencyObject const& target)
    {
        double a = GetA(target);
        double result = -a;
        target.SetValue(m_resultProperty, winrt::box_value(result));
    }
}
