#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

#include "common_defs.h"

int		ft_isblank(int c);
int		ft_ismeta(int c);
int		update_state(int state, int c);
void	free_double_ptr(char **ptr);

#endif
