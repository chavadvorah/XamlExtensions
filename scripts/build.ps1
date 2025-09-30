nuget restore -PackagesDir .\packages
msbuild /t:Clean,Build /p:Configuration=Debug /p:Platform=x64
