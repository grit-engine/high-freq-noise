#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstdio>

#define WIDTH 64
#define HEIGHT 64

struct RGB {
        unsigned char r, g, b;
};
struct fRGB {
        float r, g, b;
};

float dist (const fRGB &a, const fRGB &b)
{
        float r = a.r - b.r;
        float g = a.g - b.g;
        return sqrtf(r*r + g*g) / 2;
}

float gaussian[3][3] = {
        { 41/273.0, 26/273.0, 7/273.0 },
        { 26/273.0, 16/273.0, 4/273.0 },
        { 7/273.0, 4/273.0, 1/273.0 },
};

int main(void)
{
        fRGB fdata[WIDTH*HEIGHT];
        int counter = 0;
        for (int y=0 ; y<HEIGHT ; ++y) {
                for (int x=0 ; x<WIDTH ; ++x) {
                        fRGB &d = fdata[y*WIDTH + x];
                        int attempts = 0;
                        do {
                                d.r = 2*double(random()) / RAND_MAX - 1;
                                d.g = 2*double(random()) / RAND_MAX - 1;
                                float rad = sqrtf(d.r*d.r + d.g*d.g);
                                if (rad > 1) continue;
                                d.r /= rad;
                                d.g /= rad;
                                if (attempts <= 1000) {
                                        for (int y_=2 ; y_>=0 ; --y_) {
                                                for (int x_=2 ; x_>=0 ; --x_) { 
                                                        if (x_==0 && y_==0) continue;
                                                        fRGB &othertl = fdata[(y-y_)*WIDTH + x - x_];
                                                        if (x >= x_ && y >= y_ && dist(d, othertl) <= 6*gaussian[y_][x_]) goto try_again;
                                                }
                                        }
                                }
                                d.b = 0; //sqrtf(1 - d.r*d.r - d.g*d.g);
                                break;
                                try_again: {}
                                attempts++;
                        } while (true);
                        std::cout << counter << std::endl;
                        counter++;
                }
        }

        RGB data[WIDTH*HEIGHT];
        for (int y=0 ; y<HEIGHT ; ++y) {
                for (int x=0 ; x<WIDTH ; ++x) {
                        RGB &d = data[y*WIDTH + x];
                        fRGB &fd = fdata[y*WIDTH + x];
                        d.r = (unsigned char)(fd.r*128 + 128);
                        d.g = (unsigned char)(fd.g*128 + 128);
                        d.b = (unsigned char)(fd.b*128 + 128);
                }
        }

        FILE *f = fopen("HiFreqNoise.raw","w");
        if (f==NULL) perror("Opening file.");
        fwrite(data, sizeof(RGB), WIDTH*HEIGHT, f);
        fclose(f);
        return EXIT_SUCCESS;
}

// vim: shiftwidth=8:tabstop=8:expandtab

