#pragma once

#if defined(__has_include)
#  if __has_include("config.local.h")
#    include "config.local.h"
#  else
#    include "config.example.h"
#  endif
#else
#  include "config.example.h"
#endif
