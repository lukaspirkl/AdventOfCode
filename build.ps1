param([string]$type="Debug")
Push-Location
Write-Host "Build type: ${type}"

New-Item -ItemType Directory -Force -Path "out\build-$($type.ToLower())" | Out-Null
Set-Location "out\build-$($type.ToLower())"

Write-Host "`n### CONAN INSTALL ###" -ForegroundColor black -BackgroundColor white
conan install ../.. -s build_type=${type} --build missing

Write-Host "`n### CMAKE GENERATE ###" -ForegroundColor black -BackgroundColor white
cmake "-DCMAKE_BUILD_TYPE=${type}" ../..

Write-Host "`n### CMAKE BUILD ###" -ForegroundColor black -BackgroundColor white
cmake --build . -- "/p:Configuration=${type}"

Pop-Location
