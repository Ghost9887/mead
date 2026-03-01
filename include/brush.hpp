#ifndef BRUSH_HPP
#define BRUSH_HPP

#include "shape.hpp"

typedef enum {
    Default,
}BrushType;

class Brush {
public:
    Brush(BrushType type, Shape shape, int size);
    BrushType type;
    Shape shape;
    int size;
};

#endif
