#pragma once

#include "pch.h"
#include "GridLengthAdd.g.h"

namespace winrt::XamlExtensions::implementation
{
    struct GridLengthAdd
    {
        GridLengthAdd() = delete;

        static mux::DependencyProperty AProperty();
        static mux::GridLength GetA(mux::DependencyObject const& target);
        static void SetA(mux::DependencyObject const& target, mux::GridLength const& value);

        static mux::DependencyProperty BProperty();
        static mux::GridLength GetB(mux::DependencyObject const& target);
        static void SetB(mux::DependencyObject const& target, mux::GridLength const& value);

        static mux::DependencyProperty ResultProperty();
        static mux::GridLength GetResult(mux::DependencyObject const& target);

    private:
        static mux::DependencyProperty m_aProperty;
        static mux::DependencyProperty m_bProperty;
        static mux::DependencyProperty m_resultProperty;

        static void OnInputPropertyChanged(mux::DependencyObject const& d, mux::DependencyPropertyChangedEventArgs const& e);
        static void UpdateResult(mux::DependencyObject const& target);
    };
}

namespace winrt::XamlExtensions::factory_implementation
{
    struct GridLengthAdd : GridLengthAddT<GridLengthAdd, implementation::GridLengthAdd>
    {
    };
}
