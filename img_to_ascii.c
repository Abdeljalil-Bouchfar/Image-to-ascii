#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

const char ASCII_CHARS[11] = {' ',',',':',';','+','*','?','%','S','#','@'};

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./img_to_ascii infile\n");
        return 1;
    }

    // ... channels = # 8-bit components per pixel ...
    // ... replace the last argement with '0'..'4' to force that many components per pixel
    // ... but 'n' will always be the number that it would have been if you said
    int width, height, channels;

    // Load the image
    unsigned char *image = stbi_load(argv[1], &width, &height, &channels, 0);

    // Check if image loading fails
    if (image == NULL)
    {
        fprintf(stderr, "Error: image loading fails\n");
        return 2;
    }

    // open the output text file
    FILE *outText = fopen("out.txt", "w");

    //Calculate image size
    size_t img_size = (width * height * channels) - channels;

    // After Load the image, convert it to gray
    int pexel = 0;
    for (unsigned char *p = image; p < image + img_size; p += channels)
    {
        pexel++;
        // printf("========> pexel: %i\n", pexel);
        // printf("========> image heigth: %i\n",  pexel / width);
        // Convert the input image pexel to gray
        int grayPexel = round((float)((p[0] + p[1] + p[2]) / 3));

        // If it's the end of the image width add new line
        if (pexel % width == 0)
            fputc(10, outText);
        char x = ASCII_CHARS[grayPexel / 25];
        fputc(x, outText);
    }
    // Free the input image
    stbi_image_free(image);

    //Close the out put text file
    fclose(outText);

    return 0;
}