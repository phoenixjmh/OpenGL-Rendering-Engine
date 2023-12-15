#pragma once
#include <math.h>
//need this FOR NOW, to access the Vertex struct
#include "VertexBuffer.h"
#include <vector>
struct ShapeFactory {
    static std::vector<float> create_circle(float size);
    static std::vector<unsigned int> index_circle(int num_segments);

    static std::vector<float> create_cube();
    static std::vector<Vertex> create_cube_no_index();
    static std::vector<unsigned int> index_cube();

    static std::vector<float> create_sphere(float size);
    static std::vector<unsigned int> index_sphere(int num_segments);

    static std::vector<float> create_plane();
    static std::vector<unsigned int> index_plane(int num_segments);
};
