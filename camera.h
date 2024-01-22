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
    /* Public Camera Parameters Here */

    void render(const hittable& world) {
        initialize();
        cout<<"P3\n"<<imgw<<' '<<imgh<<"\n255\n";
        for(int j=0;j<imgh;j++){
            clog<<"\rScanlines remaining: "<<(imgh-j)<<" "<<flush;
            for(int i=0;i<imgw;i++){
                auto pixelCenter = pixel00Loc + i*pdU + j*pdV;
                auto rayDirection = pixelCenter-cameraCenter;
                ray r(cameraCenter,rayDirection);
                color pixelColor = rayColor(r,world);
                write_color(cout,pixelColor);
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
        point3 cameraCenter(0,0,0);

        vec3 vpU(viewportWidth,0,0);
        vec3 vpV(0,-viewportHeight,0);

        auto pdU = vpU/imgw;
        auto pdV = vpV/imgh;

        auto vpTL = cameraCenter - vec3(0,0,focalLength) - (vpU/2) - vpV/2;
        auto pixel00Loc = vpTL + 0.5*(pdU+pdV);
    }

    color rayColor(const ray& r, const hittable& world) const {
        hitRecord rec;
        if(world.isHit(r,interval(0,infinity),rec)){
            vec3 N = rec.normal;
            color c = 0.5*color(N.x()+1,N.y()+1,N.z()+1);
            return c;
        }
        
        vec3 unitDir = unit_vector(r.direction());
        // -1,1 -> 0,1
        auto a = 0.5*(unitDir.y()+1.0);
        color c = (1.0-a)*color(1,1,1) + a*color(0.5,0.7,1.0);
        return c;
    }
};
