/* Copyright (c) David Cunningham and the Grit Game Engine project 2012
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


/* The purpose of this program is to generate high frequency noise textures
 * for PCF shadow map purposes.
 */

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstdio>

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

float random_uniform ()
{
        return 2*double(random()) / RAND_MAX - 1;
}

float random_gauss ()
{
        float total = 0;
        int counter = 0;
        for (int i=0 ; i<10 ; ++i) {
                total += random_uniform();
                counter++;
        }
        // 2 is a fudge factor
        return 2 * total / counter;
}

int main(void)
{
        bool ring = getenv("RING")!=NULL;
        bool gauss = getenv("GAUSS")!=NULL;
        bool white = getenv("WHITE")!=NULL;
        bool raw = getenv("RAW")!=NULL;
        int WIDTH = getenv("WIDTH")!=NULL ? atoi(getenv("WIDTH")) : 64;
        int HEIGHT = getenv("HEIGHT")!=NULL ? atoi(getenv("HEIGHT")) : 64;
        fRGB *fdata = new fRGB[WIDTH*HEIGHT];
        for (int y=0 ; y<HEIGHT ; ++y) {
                for (int x=0 ; x<WIDTH ; ++x) {
                        fRGB &d = fdata[y*WIDTH + x];
                        int attempts = 0;
                        do {
                                if (gauss) {
                                        d.r = random_gauss();
                                        d.g = random_gauss();
                                } else {
                                        d.r = random_uniform();
                                        d.g = random_uniform();
                                }
                                float rad = sqrtf(d.r*d.r + d.g*d.g);
                                if (rad > 1) continue;
                                if (ring) {
                                        d.r /= rad;
                                        d.g /= rad;
                                }
                                if (white) break;
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
                }
        }

        RGB *data = new RGB[WIDTH*HEIGHT];
        for (int y=0 ; y<HEIGHT ; ++y) {
                for (int x=0 ; x<WIDTH ; ++x) {
                        RGB &d = data[y*WIDTH + x];
                        fRGB &fd = fdata[y*WIDTH + x];
                        d.r = (unsigned char)(fd.r*128 + 128);
                        d.g = (unsigned char)(fd.g*128 + 128);
                        d.b = (unsigned char)(fd.b*128 + 128);
                }
        }

        if (raw) {
                FILE *f = fopen("HiFreqNoise.raw","w");
                if (f==NULL) perror("Opening file.");
                fwrite(data, sizeof(RGB), WIDTH*HEIGHT, f);
                fclose(f);
        } else {
                FILE *f = fopen("HiFreqNoise.pnm","w");
                if (f==NULL) perror("Opening file.");
                fprintf(f, "P6\n");
                fprintf(f, "%d %d\n", WIDTH, HEIGHT);
                fprintf(f, "%d\n", 255);

                for (int p = 0; p < WIDTH * HEIGHT; ++p) {
                    fputc(data[p].r, f);
                    fputc(data[p].g, f);
                    fputc(data[p].b, f);
                }
                fclose(f);
        }

        return EXIT_SUCCESS;
}

// vim: shiftwidth=8:tabstop=8:expandtab

