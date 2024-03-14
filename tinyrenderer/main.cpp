#include "tgaimage.h"
#include <iostream>
#include <type_traits>
#include <vector>
#include "geometry.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green  = TGAColor(0, 255,   0,   255);
const TGAColor blue  = TGAColor(0, 0,   255,   255);
void bresenham_line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    x0 += 80;
    y0 += 80;
    x1 += 80;
    y1 += 80;
    bool steep = false; 
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    } 
    if (x0 > x1) {
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    }
    int delta_x = abs(x1 - x0);
    int delta_y = abs(y1 - y0);
    int x_next = x0;
    int y_next = y0;
    int p_next = 2 * delta_y - delta_x;

    for (; x_next <= x1; x_next++) {
        if (steep) {
            image.set(y_next, x_next, color);
            std::cout << y_next << "," << x_next << std::endl;
        }
        else{
            image.set(x_next, y_next, color);
            std::cout << x_next << "," << y_next << std::endl;
        }

        if (p_next < 0) {
            p_next += 2 * delta_y;
        }
        else {
            if (y1 - y0 > 0) y_next += 1;
            else y_next -= 1;
            p_next = p_next + 2 * delta_y - 2 * delta_x;
        }
        
    }
}

void line(Vec2i v1, Vec2i v2, TGAImage &image, TGAColor color) {
    bresenham_line(v1.u, v1.v, v2.u, v2.v, image, color);
}

void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color) { 
    line(t0, t1, image, color); 
    line(t1, t2, image, color); 
    line(t2, t0, image, color); 
}


int main(int argc, char** argv) {
    TGAImage image(800, 800, TGAImage::RGB);
    // Vec2i t0[3] = {Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80)}; 
    // Vec2i t1[3] = {Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180)}; 
    // Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)}; 
    // triangle(t0[0], t0[1], t0[2], image, red); 
    // triangle(t1[0], t1[1], t1[2], image, white); 
    // triangle(t2[0], t2[1], t2[2], image, green);
    // bresenham_line(10, 70, 50, 160, image, TGAColor(255, 0,   0,   255));
    // bresenham_line(50, 160, 70, 80, image, white);
    // bresenham_line(0, 80, 20, 160, image, white);
    // bresenham_line(50, 160, 200, 100, image, white);
    // bresenham_line(50, 160, 100, 50, image, white);
    // bresenham_line(70, 80, 10, 70, image, blue);
    // bresenham_line(50, 160, 70, 80, image, red);
    bresenham_line(0, 0, 80 , 0  , image, white);
    bresenham_line(0, 0, 74 , 31 , image, white);
    bresenham_line(0, 0, 57 , 57 , image, white);
    bresenham_line(0, 0, 31 , 74 , image, white);
    bresenham_line(0, 0, 0, 80   , image, white);
    bresenham_line(0, 0, -31, 74 , image, white);
    bresenham_line(0, 0, -57, 57 , image, white);
    bresenham_line(0, 0, -74, 31 , image, white);
    bresenham_line(0, 0, -80, 0  , image, white);
    bresenham_line(0, 0, -74, -31, image, white);
    bresenham_line(0, 0, -57, -57, image, white);
    bresenham_line(0, 0, -31, -74, image, white);
    bresenham_line(0, 0, 0, -80  , image, white);
    bresenham_line(0, 0, 31, -74 , image, white);
    bresenham_line(0, 0, 57, -57 , image, white);
    bresenham_line(0, 0, 74, -31 , image, white);
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}
