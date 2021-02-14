//
// Created by Michael on 13.02.2021.
//

#pragma once

#define MILLISECOND 1
#define SECOND (1000 * MILLISECOND)
#define MINUTE (60 * SECOND)
#define HOUR (60 * MINUTE)

#define SECOND_TO_MILLI(sec) ((sec) * 1000)
#define MILLI_TO_SECOND(milli) ((milli) / 1000)