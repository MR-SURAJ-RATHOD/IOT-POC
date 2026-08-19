#pragma once

/*
 * Include this header from firmware (not config.example.h directly).
 *
 * Priority:
 *   1. firmware/include/config.local.h  — your private values (gitignored)
 *   2. firmware/include/config.example.h — public placeholders
 *
 * How to use:
 *   copy firmware/include/config.example.h
 *     to firmware/include/config.local.h
 *   then replace YOUR_* strings and example pin numbers.
 */

#if defined(__has_include)
#  if __has_include("config.local.h")
#    include "config.local.h"
#  else
#    include "config.example.h"
#  endif
#else
#  include "config.example.h"
#endif
