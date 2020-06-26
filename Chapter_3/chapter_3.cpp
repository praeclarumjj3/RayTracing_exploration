#include <stdio.h>
#include "ray.h"

vec3 color(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main(){
  int image_width = 200; //image width
  int image_height = 100; //image height

  FILE* ppmimg;
  ppmimg = fopen("chapter_3.ppm","wb");

  fprintf(ppmimg, "P3\n");
  fprintf(ppmimg, "%d %d\n",image_width,image_height);
  fprintf(ppmimg,"255\n");

  vec3 lower_left_corner(-2.0, -1.0, -1.0);
  vec3 horizontal(4.0, 0.0, 0.0);
  vec3 vertical(0.0, 2.0, 0.0);
  vec3 origin(0.0, 0.0, 0.0);

  for(int j = image_width-1; j>=0; j--){
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for(int i = 0; i<image_height; i++){
      float u = float(i) / (image_width);
      float v = float(j) / (image_height);
      ray r(origin, lower_left_corner + u*horizontal + v*vertical);
      vec3 col = color(r);
      int ir = int(255.99*col[0]);
      int ig = int(255.99*col[1]);
      int ib = int(255.99*col[2]);
      fprintf(ppmimg, "%d %d %d\n",ir,ig,ib);
    }
    fprintf(ppmimg, "\n");
  }
  fclose(ppmimg);
}
