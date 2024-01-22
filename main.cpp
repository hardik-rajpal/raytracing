#include"color.h"
#include"ray.h"
#include"vec3.h"
#include<iostream>

using namespace std;
bool hitSphere(const point3& center, double radius, const ray&r){
    point3 oc = r.origin()-center;
    auto a = dot(r.direction(),r.direction());
    auto  b = 2.0*dot(oc,r.direction());
    auto c = dot(oc,oc) - radius*radius;
    auto discr = b*b - 4*a*c;
    return discr>0;
}
point3 sphereCenter = point3(3,4,10);
double sphereRadius = 2.0;
color rayColor(const ray& r){
    if(hitSphere(sphereCenter,sphereRadius,r)){
        return color(1,0,0);
    }
    
    vec3 unitDir = unit_vector(r.direction());
    // -1,1 -> 0,1
    auto a = 0.5*(unitDir.y()+1.0);
    color c = (1.0-a)*color(1,1,1) + a*color(0.5,0.7,1.0);
    return c;
}
int main(){
    int imgw,imgh;

    auto aspectRatio = 16.0/9.0;
    imgw = 400;
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
    //render:
    cout<<"P3\n"<<imgw<<' '<<imgh<<"\n255\n";
    for(int j=0;j<imgh;j++){
        clog<<"\rScanlines remaining: "<<(imgh-j)<<" "<<flush;
        for(int i=0;i<imgw;i++){
            auto pixelCenter = pixel00Loc + i*pdU + j*pdV;
            auto rayDirection = pixelCenter-cameraCenter;
            ray r(cameraCenter,rayDirection);
            color pixelColor = rayColor(r);
            write_color(cout,pixelColor);
        }
    }
    clog<<"\rDone                   \n";
    
}
