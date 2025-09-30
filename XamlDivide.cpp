#include "pch.h"
#include "XamlDivide.h"
#include "XamlDivide.g.cpp"

namespace winrt::XamlExtensions::implementation {
	double XamlDivide::ProvideValue() {
		if (B() != 0) return A() / B();
		return 0.0;
	}
}
