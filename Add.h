#pragma once

#include "pch.h"
#include "Add.g.h"

namespace winrt::XamlExtensions::implementation
{
    struct Add
    {
        Add() = delete;

        static mux::DependencyProperty AProperty();
        static double GetA(mux::DependencyObject const& target);
        static void SetA(mux::DependencyObject const& target, double value);

        static mux::DependencyProperty BProperty();
        static double GetB(mux::DependencyObject const& target);
        static void SetB(mux::DependencyObject const& target, double value);

        static mux::DependencyProperty ResultProperty();
        static double GetResult(mux::DependencyObject const& target);

    private:
        static void OnInputPropertyChanged(mux::DependencyObject const& d, mux::DependencyPropertyChangedEventArgs const& e);
        static void UpdateResult(mux::DependencyObject const& target);

        static mux::DependencyProperty m_aProperty;
        static mux::DependencyProperty m_bProperty;
        static mux::DependencyProperty m_resultProperty;
    };
}

namespace winrt::XamlExtensions::factory_implementation
{
    struct Add : AddT<Add, implementation::Add>
    {
    };
}
