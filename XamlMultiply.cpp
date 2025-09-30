#include "pch.h"
#include "XamlMultiply.h"
#include "XamlMultiply.g.cpp"

namespace winrt::XamlExtensions::implementation {
	double XamlMultiply::ProvideValue() {
		return A() * B();
	}
}
