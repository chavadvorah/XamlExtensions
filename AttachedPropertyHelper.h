#pragma once
#include "pch.h"

namespace winrt::XamlExtensions::implementation {
    /// <summary>
    /// CRTP base template for attached dependency properties with automatic change
    /// notification. Eliminates boilerplate for property registration, getters, and
    /// setters.
    /// </summary>
    /// <typeparam name="TDerived">The derived class (for CRTP pattern)</typeparam>
    /// <typeparam name="TValue">The type of values (e.g., double,
    /// mux::GridLength)</typeparam>
    template <typename TDerived, typename TValue> struct AttachedPropertyBase {
            AttachedPropertyBase() = delete;

        protected:
            // Helper to create property with change callback
            // Note: TDerived must be the implementation class that contains
            // UpdateResult
            template <typename TProjected>
            static mux::DependencyProperty RegisterProperty(const wchar_t* name,
                                                            TValue defaultValue) {
                return mux::DependencyProperty::RegisterAttached(
                    name,
                    winrt::xaml_typename<TValue>(),
                    winrt::xaml_typename<TProjected>(),
                    mux::PropertyMetadata{winrt::box_value(defaultValue),
                                          mux::PropertyChangedCallback{
                                              &TDerived::OnInputPropertyChanged}});
            }

            // Helper to create result property (no change callback)
            template <typename TProjected>
            static mux::DependencyProperty
                RegisterResultProperty(const wchar_t* name, TValue defaultValue) {
                return mux::DependencyProperty::RegisterAttached(
                    name,
                    winrt::xaml_typename<TValue>(),
                    winrt::xaml_typename<TProjected>(),
                    mux::PropertyMetadata{winrt::box_value(defaultValue)});
            }

            // Generic getter
            static TValue GetValue(const mux::DependencyObject&   target,
                                   const mux::DependencyProperty& property) {
                return winrt::unbox_value<TValue>(target.GetValue(property));
            }

            // Generic setter
            static void SetValue(const mux::DependencyObject&   target,
                                 const mux::DependencyProperty& property,
                                 TValue                         value) {
                target.SetValue(property, winrt::box_value(value));
            }

            // Common change handler - delegates to derived class
            static void OnInputPropertyChanged(
                const mux::DependencyObject& d,
                const mux::DependencyPropertyChangedEventArgs& /*e*/) {
                TDerived::UpdateResult(d);
            }
    };
} // namespace winrt::XamlExtensions::implementation

// Macro for unary operations (A -> Result)
#define DECLARE_UNARY_OPERATION_PROPERTIES(ClassName,                        \
                                           ProjectedName,                    \
                                           ValueType,                        \
                                           DefaultValue)                     \
                                                                             \
private:                                                                     \
    static mux::DependencyProperty m_aProperty;                              \
    static mux::DependencyProperty m_resultProperty;                         \
                                                                             \
public:                                                                      \
    static mux::DependencyProperty AProperty() {                             \
        return m_aProperty;                                                  \
    }                                                                        \
    static ValueType GetA(mux::DependencyObject const& target) {             \
        return GetValue(target, m_aProperty);                                \
    }                                                                        \
    static void SetA(mux::DependencyObject const& target, ValueType value) { \
        SetValue(target, m_aProperty, value);                                \
    }                                                                        \
    static mux::DependencyProperty ResultProperty() {                        \
        return m_resultProperty;                                             \
    }                                                                        \
    static ValueType GetResult(mux::DependencyObject const& target) {        \
        return GetValue(target, m_resultProperty);                           \
    }

#define IMPLEMENT_UNARY_OPERATION_PROPERTIES(ClassName,                 \
                                             ProjectedName,             \
                                             ValueType,                 \
                                             DefaultValue)              \
    mux::DependencyProperty ClassName::m_aProperty =                    \
        RegisterProperty<ProjectedName>(L"A", DefaultValue);            \
    mux::DependencyProperty ClassName::m_resultProperty =               \
        RegisterResultProperty<ProjectedName>(L"Result", DefaultValue);

// Macro to reduce boilerplate for binary operations (A, B -> Result)
// Note: ClassName is the implementation class, ProjectedName is the WinRT projected
// type
#define DECLARE_BINARY_OPERATION_PROPERTIES(ClassName,                       \
                                            ProjectedName,                   \
                                            ValueType,                       \
                                            DefaultValue)                    \
                                                                             \
private:                                                                     \
    static mux::DependencyProperty m_aProperty;                              \
    static mux::DependencyProperty m_bProperty;                              \
    static mux::DependencyProperty m_resultProperty;                         \
                                                                             \
public:                                                                      \
    static mux::DependencyProperty AProperty() {                             \
        return m_aProperty;                                                  \
    }                                                                        \
    static ValueType GetA(mux::DependencyObject const& target) {             \
        return GetValue(target, m_aProperty);                                \
    }                                                                        \
    static void SetA(mux::DependencyObject const& target, ValueType value) { \
        SetValue(target, m_aProperty, value);                                \
    }                                                                        \
    static mux::DependencyProperty BProperty() {                             \
        return m_bProperty;                                                  \
    }                                                                        \
    static ValueType GetB(mux::DependencyObject const& target) {             \
        return GetValue(target, m_bProperty);                                \
    }                                                                        \
    static void SetB(mux::DependencyObject const& target, ValueType value) { \
        SetValue(target, m_bProperty, value);                                \
    }                                                                        \
    static mux::DependencyProperty ResultProperty() {                        \
        return m_resultProperty;                                             \
    }                                                                        \
    static ValueType GetResult(mux::DependencyObject const& target) {        \
        return GetValue(target, m_resultProperty);                           \
    }

// Implementation macro for binary operations
#define IMPLEMENT_BINARY_OPERATION_PROPERTIES(ClassName,                \
                                              ProjectedName,            \
                                              ValueType,                \
                                              DefaultValue)             \
    mux::DependencyProperty ClassName::m_aProperty =                    \
        RegisterProperty<ProjectedName>(L"A", DefaultValue);            \
    mux::DependencyProperty ClassName::m_bProperty =                    \
        RegisterProperty<ProjectedName>(L"B", DefaultValue);            \
    mux::DependencyProperty ClassName::m_resultProperty =               \
        RegisterResultProperty<ProjectedName>(L"Result", DefaultValue);

// Macro for ternary operations (A, B, C -> Result)
#define DECLARE_TERNARY_OPERATION_PROPERTIES(ClassName,                      \
                                             ProjectedName,                  \
                                             ValueType,                      \
                                             DefaultValue)                   \
                                                                             \
private:                                                                     \
    static mux::DependencyProperty m_aProperty;                              \
    static mux::DependencyProperty m_bProperty;                              \
    static mux::DependencyProperty m_cProperty;                              \
    static mux::DependencyProperty m_resultProperty;                         \
                                                                             \
public:                                                                      \
    static mux::DependencyProperty AProperty() {                             \
        return m_aProperty;                                                  \
    }                                                                        \
    static ValueType GetA(mux::DependencyObject const& target) {             \
        return GetValue(target, m_aProperty);                                \
    }                                                                        \
    static void SetA(mux::DependencyObject const& target, ValueType value) { \
        SetValue(target, m_aProperty, value);                                \
    }                                                                        \
    static mux::DependencyProperty BProperty() {                             \
        return m_bProperty;                                                  \
    }                                                                        \
    static ValueType GetB(mux::DependencyObject const& target) {             \
        return GetValue(target, m_bProperty);                                \
    }                                                                        \
    static void SetB(mux::DependencyObject const& target, ValueType value) { \
        SetValue(target, m_bProperty, value);                                \
    }                                                                        \
    static mux::DependencyProperty CProperty() {                             \
        return m_cProperty;                                                  \
    }                                                                        \
    static ValueType GetC(mux::DependencyObject const& target) {             \
        return GetValue(target, m_cProperty);                                \
    }                                                                        \
    static void SetC(mux::DependencyObject const& target, ValueType value) { \
        SetValue(target, m_cProperty, value);                                \
    }                                                                        \
    static mux::DependencyProperty ResultProperty() {                        \
        return m_resultProperty;                                             \
    }                                                                        \
    static ValueType GetResult(mux::DependencyObject const& target) {        \
        return GetValue(target, m_resultProperty);                           \
    }

#define IMPLEMENT_TERNARY_OPERATION_PROPERTIES(ClassName,               \
                                               ProjectedName,           \
                                               ValueType,               \
                                               DefaultValue)            \
    mux::DependencyProperty ClassName::m_aProperty =                    \
        RegisterProperty<ProjectedName>(L"A", DefaultValue);            \
    mux::DependencyProperty ClassName::m_bProperty =                    \
        RegisterProperty<ProjectedName>(L"B", DefaultValue);            \
    mux::DependencyProperty ClassName::m_cProperty =                    \
        RegisterProperty<ProjectedName>(L"C", DefaultValue);            \
    mux::DependencyProperty ClassName::m_resultProperty =               \
        RegisterResultProperty<ProjectedName>(L"Result", DefaultValue);
