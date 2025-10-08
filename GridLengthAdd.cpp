#include "pch.h"
#include "GridLengthAdd.h"
#include "GridLengthAdd.g.cpp"

namespace winrt::XamlExtensions::implementation
{
    mux::DependencyProperty GridLengthAdd::m_aProperty =
        mux::DependencyProperty::RegisterAttached(
            L"A",
            winrt::xaml_typename<mux::GridLength>(),
            winrt::xaml_typename<XamlExtensions::GridLengthAdd>(),
            mux::PropertyMetadata{ winrt::box_value(mux::GridLength(0.0)), mux::PropertyChangedCallback{ &GridLengthAdd::OnInputPropertyChanged } }
        );

    mux::DependencyProperty GridLengthAdd::m_bProperty =
        mux::DependencyProperty::RegisterAttached(
            L"B",
            winrt::xaml_typename<mux::GridLength>(),
            winrt::xaml_typename<XamlExtensions::GridLengthAdd>(),
            mux::PropertyMetadata{ winrt::box_value(mux::GridLength(0.0)), mux::PropertyChangedCallback{ &GridLengthAdd::OnInputPropertyChanged } }
        );

    mux::DependencyProperty GridLengthAdd::m_resultProperty =
        mux::DependencyProperty::RegisterAttached(
            L"Result",
            winrt::xaml_typename<mux::GridLength>(),
            winrt::xaml_typename<XamlExtensions::GridLengthAdd>(),
            mux::PropertyMetadata{ winrt::box_value(mux::GridLength(0.0)) }
        );

    mux::DependencyProperty GridLengthAdd::AProperty()
    {
        return m_aProperty;
    }

    mux::GridLength GridLengthAdd::GetA(mux::DependencyObject const& target)
    {
        return winrt::unbox_value<mux::GridLength>(target.GetValue(m_aProperty));
    }

    void GridLengthAdd::SetA(mux::DependencyObject const& target, mux::GridLength const& value)
    {
        target.SetValue(m_aProperty, winrt::box_value(value));
    }

    mux::DependencyProperty GridLengthAdd::BProperty()
    {
        return m_bProperty;
    }

    mux::GridLength GridLengthAdd::GetB(mux::DependencyObject const& target)
    {
        return winrt::unbox_value<mux::GridLength>(target.GetValue(m_bProperty));
    }

    void GridLengthAdd::SetB(mux::DependencyObject const& target, mux::GridLength const& value)
    {
        target.SetValue(m_bProperty, winrt::box_value(value));
    }

    mux::DependencyProperty GridLengthAdd::ResultProperty()
    {
        return m_resultProperty;
    }

    mux::GridLength GridLengthAdd::GetResult(mux::DependencyObject const& target)
    {
        return winrt::unbox_value<mux::GridLength>(target.GetValue(m_resultProperty));
    }

    void GridLengthAdd::OnInputPropertyChanged(mux::DependencyObject const& d, mux::DependencyPropertyChangedEventArgs const& /*e*/)
    {
        UpdateResult(d);
    }

    void GridLengthAdd::UpdateResult(mux::DependencyObject const& target)
    {
        mux::GridLength a = GetA(target);
        mux::GridLength b = GetB(target);

        // Only add if both are pixel-based (not Auto or Star)
        if (a.GridUnitType == mux::GridUnitType::Pixel &&
            b.GridUnitType == mux::GridUnitType::Pixel)
        {
            double resultValue = a.Value + b.Value;
            mux::GridLength result(resultValue, mux::GridUnitType::Pixel);
            target.SetValue(m_resultProperty, winrt::box_value(result));
        }
    }
}
