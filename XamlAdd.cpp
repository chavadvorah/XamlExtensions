#include "pch.h"
#include "XamlAdd.h"
#include "XamlAdd.g.cpp"

namespace winrt::XamlExtensions::implementation {
	double XamlAdd::ProvideValue() {
		return A() + B();
	}
}
