#include "pch.h"
#include "GridLengthSum.h"
#include "GridLengthSum.g.cpp"

namespace winrt::XamlExtensions::implementation
{
    mux::DependencyProperty GridLengthSum::m_valuesProperty =
        mux::DependencyProperty::RegisterAttached(
            L"Values",
            winrt::xaml_typename<wf::Collections::IVector<mux::GridLength>>(),
            winrt::xaml_typename<XamlExtensions::GridLengthSum>(),
            mux::PropertyMetadata{ nullptr, mux::PropertyChangedCallback{ &GridLengthSum::OnValuesPropertyChanged } }
        );

    mux::DependencyProperty GridLengthSum::m_resultProperty =
        mux::DependencyProperty::RegisterAttached(
            L"Result",
            winrt::xaml_typename<mux::GridLength>(),
            winrt::xaml_typename<XamlExtensions::GridLengthSum>(),
            mux::PropertyMetadata{ winrt::box_value(mux::GridLength(0.0)) }
        );

    mux::DependencyProperty GridLengthSum::ValuesProperty()
    {
        return m_valuesProperty;
    }

    wf::Collections::IVector<mux::GridLength> GridLengthSum::GetValues(mux::DependencyObject const& target)
    {
        auto value = target.GetValue(m_valuesProperty);
        if (value == nullptr)
        {
            // Create a new vector if it doesn't exist
            auto vec = winrt::single_threaded_vector<mux::GridLength>();
            target.SetValue(m_valuesProperty, vec);
            return vec;
        }
        return value.as<wf::Collections::IVector<mux::GridLength>>();
    }

    void GridLengthSum::SetValues(mux::DependencyObject const& target, wf::Collections::IVector<mux::GridLength> const& value)
    {
        target.SetValue(m_valuesProperty, value);
    }

    mux::DependencyProperty GridLengthSum::ResultProperty()
    {
        return m_resultProperty;
    }

    mux::GridLength GridLengthSum::GetResult(mux::DependencyObject const& target)
    {
        return winrt::unbox_value<mux::GridLength>(target.GetValue(m_resultProperty));
    }

    void GridLengthSum::OnValuesPropertyChanged(mux::DependencyObject const& d, mux::DependencyPropertyChangedEventArgs const& /*e*/)
    {
        UpdateResult(d);
    }

    void GridLengthSum::UpdateResult(mux::DependencyObject const& target)
    {
        auto values = GetValues(target);
        if (values == nullptr || values.Size() == 0)
        {
            return;
        }

        double sum = 0.0;
        bool allPixels = true;

        for (auto const& gridLength : values)
        {
            if (gridLength.GridUnitType != mux::GridUnitType::Pixel)
            {
                allPixels = false;
                break;
            }
            sum += gridLength.Value;
        }

        if (allPixels)
        {
            mux::GridLength result(sum, mux::GridUnitType::Pixel);
            target.SetValue(m_resultProperty, winrt::box_value(result));
        }
    }
}
