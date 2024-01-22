#include"utils.h"
#include"color.h"
#include"hittable.h"
#include"hittablelist.h"
#include"sphere.h"
#include "camera.h"
#include<iostream>
using namespace std;
point3 sphereCenter = point3(0,0,-1), earthCenter=point3(0,-100.5,-1);
double sphereRadius = 0.5, earthRadius = 100.0;
sphere s = sphere(sphereCenter,sphereRadius);

int main(){
    //World
    hittable_list world;
    world.add(make_shared<sphere>(sphereCenter,sphereRadius));
    world.add(make_shared<sphere>(earthCenter,earthRadius));
    
    //camera
    camera cam;
    cam.aspectRatio = 16.0/9.0;
    cam.imgw = 400;
    cam.samplesPerPixel = 100;
    cam.render(world);
    //render:
    
}
