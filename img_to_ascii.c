#include "utils.h"


int main(int ac, char **av)
{
    // Ensure proper usage
    if (ac != 2)
    {
        fprintf(stderr, "Usage: ./\"Program name\" \"Your image\"\n");
        return 1;
    }
    return (img_to_ascii(av[1]));
}

int img_to_ascii(char *img_path)
{
    // ... channels = # 8-bit components per pixel ...
    // ... replace the last argement with '0'..'4' to force that many components per pixel
    // ... but 'n' will always be the number that it would have been if you said
    int width;
    int height;
    int channels;
    char *out_path;


    // Get the out text file name and path
    out_path = get_out_path(img_path);

    // Load the image
    unsigned char *image = stbi_load(img_path, &width, &height, &channels, 0);

    // Check if image loading fails
    if (image == NULL)
    {
        fprintf(stderr, "Error: image loading fails\n");
        return 1;
    }

    // open the out_pathput text file
    FILE *text_file = fopen(out_path, "w");

    //Calculate image size
    size_t img_size = (width * height * channels) - channels;

    // After Load the image, convert each pixel to gray 
	// then put an ascii char that match the gray grtade in the txt file
    int pexel = 0;
    for (unsigned char *p = image; p < image + img_size; p += channels)
    {
        pexel++;
        // Convert the input image pexel to gray
        int grayPexel = round((float)((p[0] + p[1] + p[2]) / 3));

        // If it's the end of the image width add new line
        if (pexel % width == 0)
            fputc('\n', text_file);
        
        fputc(ASCII_CHARS[grayPexel / 25], text_file);
    }
    // Free the input image
    stbi_image_free(image);

    //Close the out_path put text file
    fclose(text_file);

    // Free the out path string
    free(out_path);
	fprintf(stderr, "Your Image has been successfully converted to ASCII\nPath: \"%s\"\n",out_path);
    return (0);
}


char    *get_out_path(char *img_path)
{
    int i;
    int j;
    int l;
    char    name[256];
    char    *sufix;
    char    *prefix;
    char    *out_path;

    i = 0;
    j = 0;
    l = 9;
    sufix = ".txt";
    prefix = "outs";


    create_folder("outs");
    // Extact the image name from the given path
    // get image img_path length
    while (img_path[i])
        i++;
    //set i to the first character of the image name (after last '/')
    while (img_path[i] != '/')
        i--;
    // Copy image name to [name]
    while (img_path[i] != '.')
    {
        name[j++] = img_path[i];
        l++;
        i++;
    }
    //Allocate the memory for our path
    out_path = malloc(sizeof(char) * (l + 1));
    if(!out_path)
        return 0;

    i = 0;
    l = 0;
    // Add the folder name to the path
    while (prefix[i])
        out_path[l++] = prefix[i++];
        
    // Add image name to the path    
    i = 0;
    while (i < j)
        out_path[l++] = name[i++];
    
    // Add the .txt extention to the file name
    i = 0;
    while (sufix[i])
        out_path[l++] = sufix[i++];

    // Add NULL terminator to the string
    out_path[l] = 0;
    return out_path;
}

void create_folder(char *dirname) {
    int check;
    struct stat sb;

    // Create the folder if not exsit
    if (stat(dirname, &sb))
        check = mkdir(dirname, 0777);
}
 