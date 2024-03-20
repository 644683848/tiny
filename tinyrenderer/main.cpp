#include <iostream>
#include <vector>
#include "geometry.h"
#include "model.h"
#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green  = TGAColor(0, 255,   0,   255);
const TGAColor blue  = TGAColor(0, 0,   255,   255);

Model *model = NULL;
const int width  = 800;
const int height = 800;
void bresenham_line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
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
        }
        else{
            image.set(x_next, y_next, color);
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

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    bresenham_line(x0, y0, x1, y1, image, color);
}

void line(Vec2i v1, Vec2i v2, TGAImage &image, TGAColor color) {
    bresenham_line(v1.u, v1.v, v2.u, v2.v, image, color);
}

//void triangle(Vec2i* t, TGAImage &image, TGAColor color) {
//    line(t[0], t[1], image, color);
//    line(t[1], t[2], image, color);
//    line(t[2], t[0], image, color);
//}


float crossProduct2D(Vec2i a, Vec2i b) {
    return a.x * b.y - a.y * b.x;
}


Vec3f barycentric(Vec2i *pts, Vec2i P) {
    // 设pts[0], pts[1], pts[2]分别为A, B, C点
    Vec2i A = pts[0];
    Vec2i B = pts[1];
    Vec2i C = pts[2];
    Vec2i AB = Vec2i(B.x - A.x, B.y - A.y);
    Vec2i BC = Vec2i(C.x - B.x, C.y - B.y);
    Vec2i PB = Vec2i(B.x - P.x, B.y - P.y);
    Vec2i PC = Vec2i(C.x - P.x, C.y - P.y);
    Vec2i CA = Vec2i(A.x - C.x, A.y - C.y);
    // 总面积为AB X BC
    float S_ABC = crossProduct2D(AB, BC);
    // 所有三角形都是逆时针，否则会出错
    float i = crossProduct2D(PB, BC) / S_ABC;
    float j = crossProduct2D(PC, CA) / S_ABC;
    float k = 1 - i - j;
    return {i , j, k};
}



void triangle(Vec2i *pts, TGAImage &image, TGAColor color) {
    Vec2i bboxmin(image.get_width()-1,  image.get_height()-1);
    Vec2i bboxmax(0, 0);
    Vec2i clamp(image.get_width()-1, image.get_height()-1);
    for (int i=0; i<3; i++) {
        bboxmin.x = std::max(0, std::min(bboxmin.x, pts[i].x));
        bboxmin.y = std::max(0, std::min(bboxmin.y, pts[i].y));

        bboxmax.x = std::min(clamp.x, std::max(bboxmax.x, pts[i].x));
        bboxmax.y = std::min(clamp.y, std::max(bboxmax.y, pts[i].y));
    }
    Vec2i P;
    for (P.x=bboxmin.x; P.x<=bboxmax.x; P.x++) {
        for (P.y=bboxmin.y; P.y<=bboxmax.y; P.y++) {
            Vec3f bc_screen  = barycentric(pts, P);
            if (bc_screen.x<0 || bc_screen.y<0 || bc_screen.z<0) continue;
            image.set(P.x, P.y, color);
        }
    }
}


int main(int argc, char** argv) {
    TGAImage image(width, height, TGAImage::RGB);
    model = new Model(R"(C:\Users\64468\Documents\workspace\CG\cpp\tiny\tinyrenderer\obj\african_head.obj)");
    for (int i=0; i<model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        Vec2i screen_coords[3];
        for (int j=0; j<3; j++) {
            Vec3f world_coords = model->vert(face[j]);
            screen_coords[j] = Vec2i((world_coords.x+1.)*width/2., (world_coords.y+1.)*height/2.);
        }
        triangle(screen_coords, image, TGAColor(rand()%255, rand()%255, rand()%255, 255));
    }
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    delete model;
}
