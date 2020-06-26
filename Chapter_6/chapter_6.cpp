#include "rtweekend.h"

#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

#include <iostream>

color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main(){
  const auto aspect_ratio = 16.0 / 9.0;
  const int image_width = 384;
  const int image_height = static_cast<int>(image_width / aspect_ratio);
  const int samples_per_pixel = 100;

  FILE* ppmimg;
  ppmimg = fopen("chapter_7.ppm","wb");

  fprintf(ppmimg, "P3\n");
  fprintf(ppmimg, "%d %d\n",image_width, image_height);
  fprintf(ppmimg,"255\n");

  auto viewport_height = 2.0;
  auto viewport_width = aspect_ratio * viewport_height;
  auto focal_length = 1.0;
  auto origin = point3(0, 0, 0);
  auto horizontal = vec3(viewport_width, 0, 0);
  auto vertical = vec3(0, viewport_height, 0);
  auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

   hittable_list world;
   world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
   world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

   camera cam;

   for (int j = image_height-1; j >= 0; --j) {
     std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
     for (int i = 0; i < image_width; ++i) {
             color col(0, 0, 0);
             for (int s = 0; s < samples_per_pixel; ++s) {
                 auto u = (i + random_double()) / (image_width-1);
                 auto v = (j + random_double()) / (image_height-1);
                 ray r = cam.get_ray(u, v);
                 col += ray_color(r, world);
             }
         auto scale = 1.0 / samples_per_pixel;
         col[0] *= scale;
         col[1] *= scale;
         col[2] *= scale;
         int ir = int(256 * clamp(col[0], 0.0, 0.999));
         int ig = int(256 * clamp(col[1], 0.0, 0.999));
         int ib = int(256 * clamp(col[2], 0.0, 0.999));
         fprintf(ppmimg, "%d %d %d\n",ir,ig,ib);
     }
     fprintf(ppmimg, "\n");
  }
  fclose(ppmimg);
  std::cerr << "\nDone.\n";
}
