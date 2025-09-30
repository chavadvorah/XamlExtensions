# XAMLExtensions (C++/WinRT Component)

- Purpose: Reusable XAML Markup Extensions (XMLMath + Add/Subtract/Multiply/Divide).
- Output: WinRT component producing a `.winmd` and `.dll` to be referenced by WinUI apps.
- Namespace: currently `winui3_colorpicker` (will be renamed later for reuse).

Build/Use
- Add this project to your solution and add a ProjectReference from your app.
- Use markup in XAML: `{local:XMLAdd A=1 B=3}` once the component is referenced and namespace mapped.

TODO
- Implement actual math in `Operation(...)` and cover GridLength and string targets.
- Optional: rename runtime namespace from `winui3_colorpicker` to a neutral one.
