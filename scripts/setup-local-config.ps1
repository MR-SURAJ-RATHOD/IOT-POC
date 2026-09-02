$ErrorActionPreference = "Stop"
$root = Split-Path -Parent $PSScriptRoot

Write-Host "IOT-POC local config setup (repo: $root)"

$pairs = @(
    @("firmware\include\config.example.h", "firmware\include\config.local.h"),
    @("edge\raspberry_pi\config.example.env", "edge\raspberry_pi\config.local.env"),
    @("ESP32 4G LTE A7672 MODULE\data\config.local.env.example", "ESP32 4G LTE A7672 MODULE\data\config.local.env")
)

foreach ($pair in $pairs) {
    $src = Join-Path $root $pair[0]
    $dst = Join-Path $root $pair[1]
    if (-not (Test-Path $src)) {
        Write-Warning "Skip (missing): $($pair[0])"
        continue
    }
    if (Test-Path $dst) {
        Write-Host "Exists: $($pair[1])"
    } else {
        New-Item -ItemType File -Path $dst -Force | Out-Null
        Copy-Item $src $dst -Force
        Write-Host "Created: $($pair[1])"
    }
}

Write-Host ""
Write-Host "Next — verify (no hardware required for compile/tests):"
Write-Host "  cd firmware"
Write-Host "  python -m platformio run -e poc_relay_control"
Write-Host "  python -m platformio run -e example_stm32_edge"
Write-Host "  python -m platformio test -e native"
Write-Host "  cd ..\edge\raspberry_pi"
Write-Host "  pip install -r requirements.txt"
Write-Host "  python telemetry_gateway.py --dry-run --once"
