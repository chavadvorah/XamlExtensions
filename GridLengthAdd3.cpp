#include "pch.h"
#include "GridLengthAdd3.h"
#include "GridLengthAdd3.g.cpp"

namespace winrt::XamlExtensions::implementation
{
    mux::DependencyProperty GridLengthAdd3::m_aProperty =
        mux::DependencyProperty::RegisterAttached(
            L"A",
            winrt::xaml_typename<mux::GridLength>(),
            winrt::xaml_typename<XamlExtensions::GridLengthAdd3>(),
            mux::PropertyMetadata{ winrt::box_value(mux::GridLength(0.0)), mux::PropertyChangedCallback{ &GridLengthAdd3::OnInputPropertyChanged } }
        );

    mux::DependencyProperty GridLengthAdd3::m_bProperty =
        mux::DependencyProperty::RegisterAttached(
            L"B",
            winrt::xaml_typename<mux::GridLength>(),
            winrt::xaml_typename<XamlExtensions::GridLengthAdd3>(),
            mux::PropertyMetadata{ winrt::box_value(mux::GridLength(0.0)), mux::PropertyChangedCallback{ &GridLengthAdd3::OnInputPropertyChanged } }
        );

    mux::DependencyProperty GridLengthAdd3::m_cProperty =
        mux::DependencyProperty::RegisterAttached(
            L"C",
            winrt::xaml_typename<mux::GridLength>(),
            winrt::xaml_typename<XamlExtensions::GridLengthAdd3>(),
            mux::PropertyMetadata{ winrt::box_value(mux::GridLength(0.0)), mux::PropertyChangedCallback{ &GridLengthAdd3::OnInputPropertyChanged } }
        );

    mux::DependencyProperty GridLengthAdd3::m_resultProperty =
        mux::DependencyProperty::RegisterAttached(
            L"Result",
            winrt::xaml_typename<mux::GridLength>(),
            winrt::xaml_typename<XamlExtensions::GridLengthAdd3>(),
            mux::PropertyMetadata{ winrt::box_value(mux::GridLength(0.0)) }
        );

    mux::DependencyProperty GridLengthAdd3::AProperty()
    {
        return m_aProperty;
    }

    mux::GridLength GridLengthAdd3::GetA(mux::DependencyObject const& target)
    {
        return winrt::unbox_value<mux::GridLength>(target.GetValue(m_aProperty));
    }

    void GridLengthAdd3::SetA(mux::DependencyObject const& target, mux::GridLength const& value)
    {
        target.SetValue(m_aProperty, winrt::box_value(value));
    }

    mux::DependencyProperty GridLengthAdd3::BProperty()
    {
        return m_bProperty;
    }

    mux::GridLength GridLengthAdd3::GetB(mux::DependencyObject const& target)
    {
        return winrt::unbox_value<mux::GridLength>(target.GetValue(m_bProperty));
    }

    void GridLengthAdd3::SetB(mux::DependencyObject const& target, mux::GridLength const& value)
    {
        target.SetValue(m_bProperty, winrt::box_value(value));
    }

    mux::DependencyProperty GridLengthAdd3::CProperty()
    {
        return m_cProperty;
    }

    mux::GridLength GridLengthAdd3::GetC(mux::DependencyObject const& target)
    {
        return winrt::unbox_value<mux::GridLength>(target.GetValue(m_cProperty));
    }

    void GridLengthAdd3::SetC(mux::DependencyObject const& target, mux::GridLength const& value)
    {
        target.SetValue(m_cProperty, winrt::box_value(value));
    }

    mux::DependencyProperty GridLengthAdd3::ResultProperty()
    {
        return m_resultProperty;
    }

    mux::GridLength GridLengthAdd3::GetResult(mux::DependencyObject const& target)
    {
        return winrt::unbox_value<mux::GridLength>(target.GetValue(m_resultProperty));
    }

    void GridLengthAdd3::OnInputPropertyChanged(mux::DependencyObject const& d, mux::DependencyPropertyChangedEventArgs const& /*e*/)
    {
        UpdateResult(d);
    }

    void GridLengthAdd3::UpdateResult(mux::DependencyObject const& target)
    {
        mux::GridLength a = GetA(target);
        mux::GridLength b = GetB(target);
        mux::GridLength c = GetC(target);

        // Only add if all three are pixel-based (not Auto or Star)
        if (a.GridUnitType == mux::GridUnitType::Pixel &&
            b.GridUnitType == mux::GridUnitType::Pixel &&
            c.GridUnitType == mux::GridUnitType::Pixel)
        {
            double resultValue = a.Value + b.Value + c.Value;
            mux::GridLength result(resultValue, mux::GridUnitType::Pixel);
            target.SetValue(m_resultProperty, winrt::box_value(result));
        }
    }
}
