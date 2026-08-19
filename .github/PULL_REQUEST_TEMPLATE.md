## Summary

<!-- What pattern does this change demonstrate or fix? -->

## Checklist

- [ ] No credentials, private keys, or operator APNs are included
- [ ] Layering is respected (app → services → HAL → hardware)
- [ ] Native tests added or updated when logic is hardware-independent
- [ ] Docs / CHANGELOG updated when behavior or public APIs change
- [ ] Original code only (no pasted vendor samples)

## Test plan

- [ ] `cd firmware && pio test -e native`
- [ ] `cd firmware && pio run -e <affected_env>`
