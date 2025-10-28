#pragma once
#include "pch.h"

// ==============================================================================
// Modular Property Macros
// ==============================================================================

// Declare a single input property (declaration in header)
#define DECLARE_INPUT_PROPERTY(PropertyName, ValueType)                       \
                                                                              \
private:                                                                      \
    static mux::DependencyProperty m_##PropertyName##Property;                \
                                                                              \
public:                                                                       \
    static mux::DependencyProperty PropertyName##Property() {                 \
        return m_##PropertyName##Property;                                    \
    }                                                                         \
    static ValueType Get##PropertyName(mux::DependencyObject const& target) { \
        return winrt::unbox_value<ValueType>(                                 \
            target.GetValue(m_##PropertyName##Property));                     \
    }                                                                         \
    static void Set##PropertyName(mux::DependencyObject const& target,        \
                                  ValueType                    value) {       \
        target.SetValue(m_##PropertyName##Property, winrt::box_value(value)); \
    }

// Declare the result property (declaration in header)
#define DECLARE_RESULT_PROPERTY(ValueType)                                       \
                                                                                 \
private:                                                                         \
    static mux::DependencyProperty m_resultProperty;                             \
                                                                                 \
public:                                                                          \
    static mux::DependencyProperty ResultProperty() {                            \
        return m_resultProperty;                                                 \
    }                                                                            \
    static ValueType GetResult(mux::DependencyObject const& target) {            \
        return winrt::unbox_value<ValueType>(target.GetValue(m_resultProperty)); \
    }

// Declare the OnInputPropertyChanged handler
#define DECLARE_PROPERTY_CHANGED_HANDLER()               \
                                                         \
private:                                                 \
    static void OnInputPropertyChanged(                  \
        const mux::DependencyObject& d,                  \
        const mux::DependencyPropertyChangedEventArgs&);

// Declare the UpdateResult handler
#define DECLARE_UPDATE_RESULT_HANDLER()                     \
                                                            \
private:                                                    \
    static void UpdateResult(const mux::DependencyObject&);

// Implement a single input property (implementation in cpp)
#define IMPLEMENT_INPUT_PROPERTY(ClassName,                                         \
                                 ProjectedName,                                     \
                                 PropertyName,                                      \
                                 ValueType,                                         \
                                 DefaultValue)                                      \
    mux::DependencyProperty ClassName::m_##PropertyName##Property =                 \
        mux::DependencyProperty::RegisterAttached(                                  \
            L#PropertyName,                                                         \
            winrt::xaml_typename<ValueType>(),                                      \
            winrt::xaml_typename<ProjectedName>(),                                  \
            mux::PropertyMetadata{                                                  \
                winrt::box_value(DefaultValue),                                     \
                mux::PropertyChangedCallback{&ClassName::OnInputPropertyChanged}});

// Implement the result property (implementation in cpp)
#define IMPLEMENT_RESULT_PROPERTY(ClassName,                        \
                                  ProjectedName,                    \
                                  ValueType,                        \
                                  DefaultValue)                     \
    mux::DependencyProperty ClassName::m_resultProperty =           \
        mux::DependencyProperty::RegisterAttached(                  \
            L"Result",                                              \
            winrt::xaml_typename<ValueType>(),                      \
            winrt::xaml_typename<ProjectedName>(),                  \
            mux::PropertyMetadata{winrt::box_value(DefaultValue)});

// Implement standard OnInputPropertyChanged handler (implementation in cpp)
#define IMPLEMENT_PROPERTY_CHANGED_HANDLER(ClassName)           \
    void ClassName::OnInputPropertyChanged(                     \
        mux::DependencyObject const& d,                         \
        mux::DependencyPropertyChangedEventArgs const& /*e*/) { \
        UpdateResult(d);                                        \
    }
