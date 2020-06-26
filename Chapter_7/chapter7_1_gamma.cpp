#include "rtweekend.h"

#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

#include <iostream>

color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0,0,0);


    if (world.hit(r, 0, infinity, rec)) {
        point3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth-1);
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
  const int max_depth = 50;

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
                 col += ray_color(r, world, max_depth);
             }
         auto scale = 1.0 / samples_per_pixel;
         col[0] = sqrt(col[0]*scale);
         col[1] = sqrt(col[1]*scale);
         col[2] = sqrt(col[2]*scale);
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
