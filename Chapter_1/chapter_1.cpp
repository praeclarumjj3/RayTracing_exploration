#include <iostream>
#include <fstream>

int main(){
  int nx = 200; //image width
  int ny = 100; //image height

  FILE* ppmimg;
  ppmimg = fopen("chapter_1.ppm","wb");

  fprintf(ppmimg, "P3\n");
  fprintf(ppmimg, "%d %d\n",nx,ny);
  fprintf(ppmimg,"255\n");
  for(int j = ny-1; j>=0; j--){
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for(int i = 0; i<nx; i++){
      float r = float(i)/float(nx);
      float g = float(j)/float(ny);
      float b = 0.2;
      int ir = int(255.99*r);
      int ig = int(255.99*g);
      int ib = int(255.99*b);
      fprintf(ppmimg, "%d %d %d\n",ir,ig,ib);
    }
    fprintf(ppmimg, "\n");
  }
  fclose(ppmimg);
}

