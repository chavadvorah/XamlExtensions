#include "pch.h"
#include "XamlSubtract.h"
#include "XamlSubtract.g.cpp"

namespace winrt::XamlExtensions::implementation {
	double XamlSubtract::ProvideValue() {
		return A() - B();
	}
}
