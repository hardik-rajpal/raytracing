#pragma once
#include "vec3.h"
#include"interval.h"
#include<iostream>
using color=vec3;
void write_color(std::ostream &out, color pixel_color,int samplesPerPixel){
    static const interval intensity(0.000,0.999);
    pixel_color *= 1.0/samplesPerPixel;
    
    out <<static_cast<int>(255.999*intensity.clamp(pixel_color.x()))<<' '
        <<static_cast<int>(255.999*intensity.clamp(pixel_color.y()))<<' '
        <<static_cast<int>(255.999*intensity.clamp(pixel_color.z()))<<'\n';
}