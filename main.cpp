#include"color.h"
#include"vec3.h"
#include<iostream>

using namespace std;
int main(){
    int imgw,imgh;
    imgw = 256;
    imgh = 256;
    cout<<"P3\n"<<imgw<<' '<<imgh<<"\n255\n";
    for(int j=0;j<imgh;j++){
        clog<<"\rScanlines remaining: "<<(imgh-j)<<" "<<flush;
        for(int i=0;i<imgw;i++){
            double r,g,b;
            r = double(i)/(imgw-1);
            g = double(j)/(imgh-1);
            b = 0.0;
            auto pixel_color = color(r,g,b);
            write_color(cout,pixel_color);
        }
    }
    clog<<"\rDone                   \n";
}