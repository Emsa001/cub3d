#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <X11/X.h>
#include <X11/keysym.h>

# define ESC 65307
# define MINUS 45
# define PLUS 61

#define WIDTH 1920 * 1
#define HEIGHT 1080 * 1
#define M_PI 3.14159265358979323846

#define RES_DOWNGRADE 3 //Do not change

int	kd(int kc);
int	ku(int kc);
void view_center();
void put_pixel(int x, int y, int color);

extern float scale;