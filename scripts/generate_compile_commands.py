#!/usr/bin/env python3
"""
Generate compile_commands.json for C++/WinRT projects.
This file provides compilation database entries for all projects under src/.
"""

import json
import os
from pathlib import Path

# Base directories
ROOT_DIR = Path(__file__).parent.parent
SRC_DIR = ROOT_DIR / "src"

# Common compiler flags
COMMON_FLAGS = [
    "/nologo",
    "/TP",
    "/Zc:wchar_t",
    "/Zc:forScope",
    "/Zc:inline",
    "/EHsc",
    "/MDd",
    "/Od",
    "/Zi",
    "/FC",
    "/bigobj",
    "/std:c++23",
]

# Common include directories (Windows SDK paths)
WINDOWS_SDK_VERSION = "10.0.26100.0"

# Auto-detect MSVC version
def detect_msvc_version():
    """Detect the installed MSVC version"""
    msvc_path = Path("C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC")
    if msvc_path.exists():
        versions = sorted([d.name for d in msvc_path.iterdir() if d.is_dir()], reverse=True)
        if versions:
            return versions[0]
    return "14.44.35207"  # fallback

MSVC_VERSION = detect_msvc_version()

COMMON_INCLUDES = [
    f"C:/Program Files (x86)/Windows Kits/10/Include/{WINDOWS_SDK_VERSION}/cppwinrt",
    f"C:/Program Files (x86)/Windows Kits/10/Include/{WINDOWS_SDK_VERSION}/shared",
    f"C:/Program Files (x86)/Windows Kits/10/Include/{WINDOWS_SDK_VERSION}/ucrt",
    f"C:/Program Files (x86)/Windows Kits/10/Include/{WINDOWS_SDK_VERSION}/um",
    f"C:/Program Files (x86)/Windows Kits/10/Include/{WINDOWS_SDK_VERSION}/winrt",
    f"C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/{MSVC_VERSION}/include",
]

# NuGet package includes (from user profile)
NUGET_INCLUDES = [
    "C:/Users/Chava/.nuget/packages/microsoft.windows.implementationlibrary/1.0.250325.1/include",
    "C:/Users/Chava/.nuget/packages/microsoft.windowsappsdk.dwrite/1.8.25090401/include",
    "C:/Users/Chava/.nuget/packages/microsoft.windowsappsdk.foundation/1.8.250906002/include",
    "C:/Users/Chava/.nuget/packages/microsoft.windowsappsdk.interactiveexperiences/1.8.250906004/include",
    "C:/Users/Chava/.nuget/packages/microsoft.windowsappsdk.ml/1.8.2091/include",
    "C:/Users/Chava/.nuget/packages/microsoft.windowsappsdk.runtime/1.8.250916003/include",
    "C:/Users/Chava/.nuget/packages/microsoft.windowsappsdk.winui/1.8.250906003/include",
]


def discover_sources(directory):
    """Discover all .cpp and .h files in a directory (non-recursive)"""
    sources = []
    headers = []

    if not directory.exists():
        return sources, headers

    for file in directory.iterdir():
        if file.is_file():
            if file.suffix == ".cpp":
                sources.append(file)
            elif file.suffix == ".h":
                headers.append(file)

    return sorted(sources), sorted(headers)


def discover_all_src_directories():
    """Discover all directories under src/"""
    if not SRC_DIR.exists():
        return []

    directories = []
    for item in SRC_DIR.iterdir():
        if item.is_dir():
            directories.append(item)

    return sorted(directories)


def discover_all_header_only_directories():
    """Discover directories under src/ that only contain headers (no .cpp files)"""
    header_only_dirs = []

    for directory in discover_all_src_directories():
        sources, headers = discover_sources(directory)
        if not sources and headers:  # Has headers but no .cpp files
            header_only_dirs.append(directory)

    return header_only_dirs


def get_all_src_include_paths():
    """Get include paths for all directories under src/"""
    includes = []
    for directory in discover_all_src_directories():
        includes.append(str(directory).replace("\\", "/"))

        # Add Generated Files directory if it exists
        generated_files = directory / "Generated Files"
        if generated_files.exists():
            includes.append(str(generated_files).replace("\\", "/"))

    return includes


def discover_packages_includes(directory):
    """Discover NuGet package include directories for a project"""
    packages_dir = directory / "packages"
    includes = []

    if not packages_dir.exists():
        return includes

    for package in packages_dir.iterdir():
        if package.is_dir():
            # Check common NuGet package include paths
            for subpath in ["build/native/include", "build/native/include-winrt", "include"]:
                include_path = package / subpath
                if include_path.exists():
                    includes.append(str(include_path).replace("\\", "/"))

    return includes


def parse_vcxproj_includes(project_dir):
    """Parse AdditionalIncludeDirectories from .vcxproj file"""
    includes = []
    vcxproj_file = project_dir / f"{project_dir.name}.vcxproj"

    if not vcxproj_file.exists():
        return includes

    try:
        with open(vcxproj_file, 'r', encoding='utf-8') as f:
            content = f.read()

        # Find all AdditionalIncludeDirectories entries
        import re
        pattern = r'<AdditionalIncludeDirectories>(.*?)</AdditionalIncludeDirectories>'
        matches = re.findall(pattern, content, re.DOTALL)

        for match in matches:
            # Split by semicolon
            paths = match.split(';')
            for path in paths:
                path = path.strip()

                # Skip MSBuild variables/macros
                if path.startswith('%') or not path:
                    continue

                # Resolve MSBuild variables
                path = path.replace('$(ProjectDir)', str(project_dir))
                path = path.replace('$(SolutionDir)', str(ROOT_DIR))

                # Convert to absolute path
                if not Path(path).is_absolute():
                    path = project_dir / path
                else:
                    path = Path(path)

                # Normalize the path
                try:
                    path = path.resolve()
                    if path.exists():
                        includes.append(str(path).replace("\\", "/"))
                except:
                    pass
    except:
        pass

    return includes


def get_project_config(project_dir):
    """Generate configuration for a project directory"""
    sources, headers = discover_sources(project_dir)

    # Build project-specific includes
    project_includes = [str(project_dir).replace("\\", "/")]

    # Add includes from .vcxproj file
    project_includes.extend(parse_vcxproj_includes(project_dir))

    # Add all src/ directories to includes
    project_includes.extend(get_all_src_include_paths())

    # Add package includes
    project_includes.extend(discover_packages_includes(project_dir))

    # Add debug output directory if it exists
    debug_dir = project_dir / project_dir.name / "x64" / "Debug"
    if debug_dir.exists():
        project_includes.append(str(debug_dir).replace("\\", "/"))

    # Determine if this is a DLL project by checking the .vcxproj file
    is_dll = False
    vcxproj_file = project_dir / f"{project_dir.name}.vcxproj"
    if vcxproj_file.exists():
        try:
            with open(vcxproj_file, 'r', encoding='utf-8') as f:
                vcxproj_content = f.read()
                # Check for <ConfigurationType>DynamicLibrary</ConfigurationType>
                is_dll = '<ConfigurationType>DynamicLibrary</ConfigurationType>' in vcxproj_content
        except:
            pass

    # Build defines based on project type
    defines = [
        "_DEBUG",
        "WIN32",
        "_UNICODE",
        "UNICODE",
        "WINAPI_FAMILY=WINAPI_FAMILY_DESKTOP_APP",
        "__WRL_NO_DEFAULT_LIB__",
    ]

    if is_dll:
        defines.extend([
            "_WINRT_DLL",
            "WIN32_LEAN_AND_MEAN",
            "WINRT_LEAN_AND_MEAN",
            "_WINDLL",
        ])
    else:
        defines.extend([
            "MICROSOFT_WINDOWSAPPSDK_SELFCONTAINED=1",
            "MICROSOFT_WINDOWSAPPSDK_UNDOCKEDREGFREEWINRT_AUTO_INITIALIZE_LOADLIBRARY",
        ])

    return {
        "directory": str(project_dir).replace("\\", "/"),
        "pch": str(project_dir / "pch.h").replace("\\", "/"),
        "project_includes": project_includes,
        "defines": defines,
        "sources": sources,
        "headers": headers,
    }


def build_command_entry(file_path, config, is_pch_create=False):
    """Build a single compile_commands.json entry"""
    # Build include paths
    includes = []
    for inc in config["project_includes"] + COMMON_INCLUDES + NUGET_INCLUDES:
        includes.extend(["/I", inc])

    # Build defines
    defines = []
    for define in config["defines"]:
        defines.extend(["/D", define])

    # Build arguments
    arguments = (
        ["C:/Program Files/LLVM/bin/clang-cl.exe"]
        + COMMON_FLAGS
        + includes
        + defines
    )

    # Add precompiled header flags
    if is_pch_create:
        arguments.extend(["/FI", config["pch"]])
    else:
        arguments.extend(["/FI", config["pch"]])

    # Add the source file
    arguments.append(file_path)

    # Build command string (for compatibility)
    command = " ".join(f'"{arg}"' if " " in arg else arg for arg in arguments)

    return {
        "directory": config["directory"],
        "command": command,
        "arguments": arguments,
        "file": file_path,
    }


def generate_compile_commands():
    """Generate the complete compile_commands.json"""
    entries = []

    # Get all project directories (those with .cpp files)
    all_directories = discover_all_src_directories()
    project_directories = []

    for directory in all_directories:
        sources, _ = discover_sources(directory)
        if sources:  # Has .cpp files, it's a project
            project_directories.append(directory)

    # Generate entries for each project
    for project_dir in project_directories:
        config = get_project_config(project_dir)

        # Add source files
        for source in config["sources"]:
            file_path = str(source).replace("\\", "/")
            is_pch = source.name == "pch.cpp"
            entries.append(build_command_entry(file_path, config, is_pch))

        # Add headers as virtual entries (helps clangd understand header-only code)
        for header in config["headers"]:
            file_path = str(header).replace("\\", "/")
            if header.exists():
                entries.append(build_command_entry(file_path, config))

    # Generate entries for header-only directories
    # Use the first project's config as context (if any projects exist)
    if project_directories:
        reference_config = get_project_config(project_directories[0])

        for header_only_dir in discover_all_header_only_directories():
            _, headers = discover_sources(header_only_dir)
            for header in headers:
                file_path = str(header).replace("\\", "/")
                if header.exists():
                    entries.append(build_command_entry(file_path, reference_config))

    # Write the compilation database
    output_file = ROOT_DIR / "compile_commands.json"
    with open(output_file, "w", encoding="utf-8") as f:
        json.dump(entries, f, indent=2)

    print(f"Generated {len(entries)} compilation database entries")
    print(f"  Projects: {', '.join(d.name for d in project_directories)}")
    print(f"  Header-only: {', '.join(d.name for d in discover_all_header_only_directories())}")
    print(f"Written to: {output_file}")


if __name__ == "__main__":
    generate_compile_commands()
