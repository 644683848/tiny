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
const int depth  = 255;
float *z_buffer = NULL;
Vec3f light_dir(0,0,-1); // 光照方向，用来跟三角形法线计算亮度

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
    bresenham_line(v1.x, v1.y, v2.x, v2.y, image, color);
}

//void triangle(Vec2i* t, TGAImage &image, TGAColor color) {
//    line(t[0], t[1], image, color);
//    line(t[1], t[2], image, color);
//    line(t[2], t[0], image, color);
//}


float crossProduct2D(Vec2i a, Vec2i b) {
    return a.x * b.y - a.y * b.x;
}

Vec3f crossProduct3D(Vec3f v1, Vec3f v2) {
    float x = v1.y * v2.z - v1.z * v2.y;
    float y = v1.z * v2.x - v1.x * v2.z;
    float z = v1.x * v2.y - v1.y * v2.x;
    return {x, y ,z};
}


Vec3f barycentric(Vec3f *pts, Vec2i P) {
    // 设pts[0], pts[1], pts[2]分别为A, B, C点
    Vec2i A = Vec2i(pts[0].x, pts[0].y);
    Vec2i B = Vec2i(pts[1].x, pts[1].y);
    Vec2i C = Vec2i(pts[2].x, pts[2].y);
    Vec2i AB = Vec2i(B.x - A.x, B.y - A.y);
    Vec2i BC = Vec2i(C.x - B.x, C.y - B.y);
    Vec2i PB = Vec2i(B.x - P.x, B.y - P.y);
    Vec2i PC = Vec2i(C.x - P.x, C.y - P.y);
    Vec2i CA = Vec2i(A.x - C.x, A.y - C.y);
    // 总面积为AB X BC
    float S_ABC = crossProduct2D(AB, BC);
    // 计算面积时，以逆时针为准
    float i = crossProduct2D(PB, BC) / S_ABC;
    float j = crossProduct2D(PC, CA) / S_ABC;
    float k = 1 - i - j;
    return {i , j, k};
}



void triangle(Vec3f *pts, Vec2i uv0, Vec2i uv1, Vec2i uv2, TGAImage &image, float intensity, float *z_buffer) {
    Vec2i bboxmin(image.get_width()-1,  image.get_height()-1);
    Vec2i bboxmax(0, 0);
    Vec2i clamp(image.get_width()-1, image.get_height()-1);
    for (int i=0; i<3; i++) {
        bboxmin.x = std::max(0, std::min(bboxmin.x, int(pts[i].x)));
        bboxmin.y = std::max(0, std::min(bboxmin.y, int(pts[i].y)));

        bboxmax.x = std::min(clamp.x, std::max(bboxmax.x, int(pts[i].x)));
        bboxmax.y = std::min(clamp.y, std::max(bboxmax.y, int(pts[i].y)));
    }
    Vec2i P;
    Vec2i uvP;
    for (P.x=bboxmin.x; P.x<=bboxmax.x; P.x++) {
        for (P.y=bboxmin.y; P.y<=bboxmax.y; P.y++) {
            Vec3f bc_screen  = barycentric(pts, P);
            if (bc_screen.x<0 || bc_screen.y<0 || bc_screen.z<0) continue;
            float tmp = 0;
            for (int i = 0; i < 3; i++) {
                if (i == 0) tmp += pts[i].z * bc_screen.x;
                else if (i == 1) tmp += pts[i].z * bc_screen.y;
                else tmp += pts[i].z * bc_screen.z;
            }
            uvP.x = uv0.x * bc_screen.x + uv1.x * bc_screen.y + uv2.x * bc_screen.z;
            uvP.y = uv0.y * bc_screen.x + uv1.y * bc_screen.y + uv2.y * bc_screen.z;
            if (z_buffer[int(P.x+P.y*width)] < tmp) {
                z_buffer[int(P.x+P.y*width)] = tmp;
                TGAColor texture_color = model->diffuse(uvP);
                intensity = 1;
                TGAColor color = TGAColor(intensity * texture_color.r, intensity * texture_color.g, intensity * texture_color.b);
                image.set(P.x, P.y, color);
            }
        }
    }
}


int main(int argc, char** argv) {
    TGAImage image(width, height, TGAImage::RGB);
    model = new Model(R"(..\obj\african_head.obj)");
    z_buffer = new float [width*height];
    for (int i=0; i<width*height; i++) {
        z_buffer[i] = std::numeric_limits<int>::min();
    }

    for (int i=0; i<model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        Vec3f screen_coords[3];
        Vec3f world_coords[3];
        for (int j=0; j<3; j++) {
            world_coords[j] = model->vert(face[j]);
            screen_coords[j] = Vec3f(int((world_coords[j].x+1.)*width/2.+.5), int((world_coords[j].y+1.)*height/2.+.5), world_coords[j].z);
        }
        Vec3f normal_to_the_triangle = crossProduct3D(world_coords[1] - world_coords[2], world_coords[0] - world_coords[1]);
        normal_to_the_triangle.normalize();
        // 计算与法线的点积，同向时光照最亮
        float intensity = normal_to_the_triangle * light_dir;
        if (intensity > 0) { // 夹角超过九十度表示光照不到，舍弃即可
            Vec2i uv[3];
            for (int k=0; k<3; k++) {
                uv[k] = model->uv(i, k);
            }
            triangle(screen_coords, uv[0], uv[1], uv[2],image, intensity, z_buffer);
        }

    }
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    delete model;
}
