#pragma once

#include "pch.h"
#include "GridLengthSum.g.h"

namespace winrt::XamlExtensions::implementation
{
    struct GridLengthSum
    {
        GridLengthSum() = delete;

        static mux::DependencyProperty ValuesProperty();
        static wf::Collections::IVector<mux::GridLength> GetValues(mux::DependencyObject const& target);
        static void SetValues(mux::DependencyObject const& target, wf::Collections::IVector<mux::GridLength> const& value);

        static mux::DependencyProperty ResultProperty();
        static mux::GridLength GetResult(mux::DependencyObject const& target);

        static void UpdateResult(mux::DependencyObject const& target);

    private:
        static mux::DependencyProperty m_valuesProperty;
        static mux::DependencyProperty m_resultProperty;

        static void OnValuesPropertyChanged(mux::DependencyObject const& d, mux::DependencyPropertyChangedEventArgs const& e);
    };
}

namespace winrt::XamlExtensions::factory_implementation
{
    struct GridLengthSum : GridLengthSumT<GridLengthSum, implementation::GridLengthSum>
    {
    };
}
