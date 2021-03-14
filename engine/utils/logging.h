//
// Created by Michael on 12.03.2021.
//

#pragma once

#include <cstdio>

#define LOGDEBUG(str, args...) std::printf("DEBUG: " str "\n", args)
#define LOGERROR(str, args...) std::printf("ERROR: " str "\n", args)