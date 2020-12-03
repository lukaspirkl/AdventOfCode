Boost directory with headers was create by the following commands.

```
cd C:\Temp
git clone --recursive https://github.com/boostorg/boost.git
cd boost
bootstrap.bat
b2
b2 tools/bcp
dist\bin\bcp.exe boost/multiprecision/cpp_int.hpp C:\Temp\headers
```

Resulting C:\Temp\headers contains files which are here.