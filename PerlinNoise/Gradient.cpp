#include "Gradient.hpp"

double abs(unsigned char a) {
    return (double) ( (a < 0) ? -1*a : a );
}

ppm Gradient(const ppm * image, double threshold) {
    ppm result(image->width, image->height);
    {
        unsigned int i = 0;
        for (unsigned int j = 0; j < image->height; ++j) {
            result.r[j * image->width + i] = 255;
            result.g[j * image->width + i] = 255;
            result.b[j * image->width + i] = 255;
        }
    };
    {
        unsigned int i = image->width - 1;
        for (unsigned int j = 0; j < image->height; ++j) {
            result.r[j * image->width + i] = 255;
            result.g[j * image->width + i] = 255;
            result.b[j * image->width + i] = 255;
        }
    };
    {
        unsigned int j = 0;
        for (unsigned int i = 0; i < image->width; ++i) {
            result.r[j * image->width + i] = 255;
            result.g[j * image->width + i] = 255;
            result.b[j * image->width + i] = 255;
        }
    };
    {
        unsigned int j = image->height - 1;
        for (unsigned int i = 0; i < image->width; ++i) {
            result.r[j * image->width + i] = 255;
            result.g[j * image->width + i] = 255;
            result.b[j * image->width + i] = 255;
        }
    };
    for (unsigned int i = 1; i < image->width - 1; ++i) {
        for (unsigned int j = 1; j < image->height - 1; ++j) {
            result.r[j * image->width + i] = (abs(image->r[j * image->width + i - 1] - image->r[j * image->width + i + 1]) / 2.f <= threshold) ? 0 : 255;
            result.g[j * image->width + i] = (abs(image->g[j * image->width + i - 1] - image->g[j * image->width + i + 1]) / 2.f <= threshold) ? 0 : 255;
            result.b[j * image->width + i] = (abs(image->b[j * image->width + i - 1] - image->b[j * image->width + i + 1]) / 2.f <= threshold) ? 0 : 255;

            result.g[j * image->width + i] |= (abs(image->g[(j-1) * image->width + i] - image->g[(j+1) * image->width + i]) / 2.f <= threshold) ? 0 : 255;
            result.r[j * image->width + i] |= (abs(image->r[(j-1) * image->width + i] - image->r[(j+1) * image->width + i]) / 2.f <= threshold) ? 0 : 255;
            result.b[j * image->width + i] |= (abs(image->b[(j-1) * image->width + i] - image->b[(j+1) * image->width + i]) / 2.f <= threshold) ? 0 : 255;
        }
    }
    return result;
}
