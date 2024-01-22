#pragma once
#include "utils.h"
#include<iostream>
#include "color.h"
#include "hittable.h"

using namespace std;
class camera {
  public:
    double aspectRatio = 16.0/9.0;
    int imgw = 400;
    int samplesPerPixel = 10;
    int maxDepth = 10;
    /* Public Camera Parameters Here */
    ray getRay(int i, int j)const{
        vec3 point = pixel00Loc + i*pdU + j*pdV;
        point += pixelSampleSquare();
        auto direction  = point-cameraCenter;
        return ray(cameraCenter,direction);
    }
    vec3 pixelSampleSquare()const {
        auto px = -0.5+random_double();
        auto py = -0.5+random_double();
        return (px*pdU) + (py*pdV);
    }
    void render(const hittable& world) {
        initialize();
        cout<<"P3\n"<<imgw<<' '<<imgh<<"\n255\n";
        for(int j=0;j<imgh;j++){
            clog<<"\rScanlines remaining: "<<(imgh-j)<<" "<<flush;
            for(int i=0;i<imgw;i++){
                auto pixelCenter = pixel00Loc + i*pdU + j*pdV;
                color pixelColor(0,0,0);
                for(size_t sample=0;sample<samplesPerPixel;sample++){
                    ray r = getRay(i,j);
                    pixelColor += rayColor(r,maxDepth,world);
                }
                write_color(cout,pixelColor,samplesPerPixel);
            }
        }
        clog<<"\rDone                   \n";
    }

  private:
    /* Private Camera Variables Here */
    int imgh;
    point3 cameraCenter, pixel00Loc;
    vec3 pdU,pdV;
    void initialize() {
        imgh = static_cast<int>(imgw/aspectRatio);
        imgh = imgh<1 ? 1: imgh;
        auto focalLength = 1.0;    
        auto viewportHeight = 2.0;
        auto viewportWidth = viewportHeight*(static_cast<double>(imgw)/imgh);
        cameraCenter = point3(0,0,0);

        vec3 vpU(viewportWidth,0,0);
        vec3 vpV(0,-viewportHeight,0);

        pdU = vpU/imgw;
        pdV = vpV/imgh;

        auto vpTL = cameraCenter - vec3(0,0,focalLength) - (vpU/2) - vpV/2;
        pixel00Loc = vpTL + 0.5*(pdU+pdV);
    }

    color rayColor(const ray& r, int depth,const hittable& world) const {
        if(depth<=0){
            return color(0,0,0);
        }
        hitRecord rec;
        if(world.isHit(r,interval(0.001,infinity),rec)){
            vec3 direction = rec.normal + random_unit_vector();
            return 0.5*rayColor(ray(rec.p,direction),depth-1,world);
        }
        
        vec3 unitDir = unit_vector(r.direction());
        // -1,1 -> 0,1
        auto a = 0.5*(unitDir.y()+1.0);
        color c = (1.0-a)*color(1,1,1) + a*color(0.5,0.7,1.0);
        return c;
    }
};
