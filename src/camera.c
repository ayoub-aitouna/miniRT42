#include "headers/camera.h"
#include "headers/types.h"

camera_t *Camera()
{
    camera_t *camera = malloc(sizeof(camera_t));
    camera->position = vector(0.0, -10.0, 0.0);
    camera->loockat = vector(0.0, 0.0, 0.0);
    camera->up = vector(0.0, 0.0, 0.1);
    camera->aspect_ration = 1.0;
    camera->horizontal_size = 1.0;
    camera->lenght = 1.0;
    camera->aspect_ration = 1.0;
    return (camera);
}

void calculat_geometry(camera_t *camera)
{
    vector_t *aligment = minus(camera->loockat, camera->position);
    normalize(aligment);

    camera->screen_u = cross(*aligment, *camera->up);
    normalize(camera->screen_u);

    camera->screen_v = cross(*camera->screen_u, *aligment);
    normalize(camera->screen_v);

    camera->screen_center = pluse(camera->position, num_muliplication(aligment, camera->lenght));

    camera->screen_u = num_muliplication(camera->screen_u, camera->horizontal_size);
    camera->screen_v = num_muliplication(camera->screen_v, camera->horizontal_size / camera->aspect_ration);
}

ray_t *generate_ray(camera_t *camera, int screenX, int screenY)
{
    vector_t *w_part1 = pluse(camera->position, num_muliplication(camera->screen_u, screenX));
    vector_t *dst_cords = pluse(w_part1, num_muliplication(camera->screen_v, screenY));

    ray_t *new_ray = malloc(sizeof(ray_t));
    new_ray->point1 = copy_vector(*camera->position);
    new_ray->point2 = copy_vector(*dst_cords);
    new_ray->m_lab = minus(new_ray->point1, new_ray->point2);
    return (new_ray);
}