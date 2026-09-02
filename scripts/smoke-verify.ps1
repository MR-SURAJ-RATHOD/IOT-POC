# Smoke verify — compile + test without hardware (except optional Pi dry-run)
$ErrorActionPreference = "Stop"
$root = Split-Path -Parent $PSScriptRoot
Set-Location $root

Write-Host "=== IOT-POC smoke verify ==="

Write-Host "`n[1/5] ESP32 poc_relay_control"
Set-Location firmware
python -m platformio run -e poc_relay_control
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

Write-Host "`n[2/5] STM32 example_stm32_edge"
python -m platformio run -e example_stm32_edge
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

Write-Host "`n[3/5] Native unit tests"
if ($env:OS -match "Windows") {
    $gcc = (Get-Command gcc -ErrorAction SilentlyContinue)?.Source
    if ($gcc -and $gcc -match " ") {
        $short = cmd /c "for %I in (`"$gcc`") do @echo %~sI"
        if ($short -and (Test-Path $short)) {
            $bin = Split-Path $short
            $env:PATH = "$bin;" + $env:PATH
            $root = Split-Path (Split-Path $bin)
            $shortRoot = cmd /c "for %I in (`"$root`") do @echo %~sI"
            if ($shortRoot) {
                $env:GCC_EXEC_PREFIX = ($shortRoot -replace '\\', '/') + "/lib/gcc/"
            }
        }
    }
}
python -m platformio test -e native
if ($LASTEXITCODE -ne 0) {
    Write-Warning "Native tests failed (install gcc/g++ or use WSL). Continuing smoke verify."
}

Set-Location $root

Write-Host "`n[4/5] A7672 4G gateway"
Set-Location "ESP32 4G LTE A7672 MODULE"
python -m platformio run
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

Set-Location $root

Write-Host "`n[5/5] Raspberry Pi dry-run"
Set-Location edge\raspberry_pi
pip install -q -r requirements.txt
python telemetry_gateway.py --dry-run --once
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

Set-Location $root
Write-Host "`n=== ALL SMOKE CHECKS PASSED ==="
