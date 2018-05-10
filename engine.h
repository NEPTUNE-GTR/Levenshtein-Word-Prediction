#ifndef _ENGINE_H
#define _ENGINE_H

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "table.h"
#include "levenshtein.h"


void start(char const * const q);
void userInput();
void pager();

#endif