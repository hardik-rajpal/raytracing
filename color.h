#pragma once
#include "vec3.h"
#include"interval.h"
#include<iostream>
using color=vec3;
double linearToGamma(double linearComponent){
    return sqrt(linearComponent);
}
void write_color(std::ostream &out, color pixel_color,int samplesPerPixel){
    static const interval intensity(0.000,0.999);
    pixel_color *= 1.0/samplesPerPixel;
    double r,g,b;
    r=pixel_color.x();
    g=pixel_color.y();
    b=pixel_color.z();
    r=linearToGamma(r);
    g=linearToGamma(g);
    b=linearToGamma(b);
    out <<static_cast<int>(255.999*intensity.clamp(r))<<' '
        <<static_cast<int>(255.999*intensity.clamp(g))<<' '
        <<static_cast<int>(255.999*intensity.clamp(b))<<'\n';
}