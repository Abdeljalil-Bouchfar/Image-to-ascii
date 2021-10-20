#ifndef UTILS
#define UTILS

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const char ASCII_CHARS[11] = {'.', ',', ':', ';', '+', '*', '?', '%', 'S', '#', '@'};

char    *get_out_path(char *img_path);
void    create_folder(char *dirname);
int     img_to_ascii(char *img_path);

#endif
