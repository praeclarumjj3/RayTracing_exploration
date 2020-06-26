#include <stdio.h>
#include "vec3.h"

int main(){
  int image_width = 200; //image width
  int image_height = 100; //image height

  FILE* ppmimg;
  ppmimg = fopen("chapter_2.ppm","wb");

  fprintf(ppmimg, "P3\n");
  fprintf(ppmimg, "%d %d\n",image_width,image_height);
  fprintf(ppmimg,"255\n");
  for(int j = image_width-1; j>=0; j--){
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for(int i = 0; i<image_height; i++){
      vec3 col(float(i)/float(image_width), float(j)/float(image_height), 0.2);
      int ir = int(255.99*col[0]);
      int ig = int(255.99*col[1]);
      int ib = int(255.99*col[2]);
      fprintf(ppmimg, "%d %d %d\n",ir,ig,ib);
    }
    fprintf(ppmimg, "\n");
  }
  fclose(ppmimg);
}
