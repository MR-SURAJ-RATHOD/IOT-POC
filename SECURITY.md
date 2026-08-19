# Security Policy

This repository is a **public** proof-of-concept reference. It is not a hosted service and it does not ship production credentials.

## Supported versions

Security fixes are accepted against the default branch (`main`) and the latest tagged release when tags exist.

| Version | Supported |
| ------- | --------- |
| `main`  | Yes       |
| older untagged snapshots | Best effort |

## What to report

Please report:

- Credential or key material accidentally committed to the tree
- Unsafe TLS/MQTT defaults that would encourage production misuse
- Buffer overflows, command injection via serial/MQTT payloads, or watchdog bypasses in example firmware
- Documentation that instructs users to hard-code real secrets

Do **not** report:

- Missing features in a POC example
- Hardware that does not match the example pin tables
- Issues in third-party brokers, cellular networks, or vendor modules

## How to report

Use [GitHub Security Advisories](https://github.com/suraj-iot-engineer/IOT-POC/security/advisories/new) so the report stays private until a fix is ready.

Include:

- Affected files and PlatformIO environment names
- Reproduction on ESP32 (or native test) without real customer credentials
- Impact (device takeover, secret leakage, denial of service)

Do not attach private certificates, live APNs, or operator credentials. Redact IMSI/ICCID.

## Maintainer response

Maintainers will acknowledge reports when possible and publish a fix or advisory through the normal GitHub release process. There is no dedicated bug-bounty program.

## Secret handling in this project

- Copy `firmware/include/config.example.h` to `firmware/include/config.local.h` (gitignored).
- Never commit passwords, API keys, private keys, or operator APN credentials.
- Example certificates, if added later, must be **public test** material only, stored as placeholders.
