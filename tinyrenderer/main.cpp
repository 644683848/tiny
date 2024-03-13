#include "tgaimage.h"
#include "geometry.h"
#include <vector>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green  = TGAColor(0, 255,   0,   255);
const TGAColor blue  = TGAColor(0, 0,   255,   255);
void bresenham_line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    bool steep = false; 
    if (std::abs(x0-x1)<std::abs(y0-y1)) { // if the line is steep, we transpose the image 
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    } 
    if (x0>x1) { // make it left−to−right 
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    } 
    int delta_x = x1 - x0;
    int delta_y = y1 - y0;
    int p_next = 2 * delta_y - delta_x;
    int x_next = x0;
    int y_next = y0;
    for (; x_next <= x1; x_next++) {
        std::cout << x_next << "," << y_next << std::endl;
        if (steep) {
            image.set(y_next, x_next, color);
        }
        else {
            image.set(x_next, y_next, color);
        }
        if (p_next < 0) {
            p_next += 2 * delta_y;
        }
        else {
            y_next += 1;
            p_next = p_next + 2 * delta_y - 2 * delta_x;
        }
        
    }
}

void line(Vec2i v1, Vec2i v2, TGAImage &image, TGAColor color) {
    bresenham_line(v1.u, v1.v, v2.u, v2.v, image, color);
}

int main(int argc, char** argv) {
    TGAImage image(800, 800, TGAImage::RGB);
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}
