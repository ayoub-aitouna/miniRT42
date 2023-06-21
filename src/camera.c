#include "headers/camera.h"

camera_t *Camera(void)
{
    camera_t *camera;

    camera = malloc(sizeof(camera_t));
    camera->position = vector(3.0, -5.0, -2.0);
    camera->loockat = vector(0.0, 0.0, 0.0);
    camera->up = vector(0.0, 0.0, 0.1);
    camera->horizontal_size = 0.75;
    camera->lenght = 1.0;
    camera->aspect_ration = 16.0 / 9.0;
    calculat_geometry(camera);
    return (camera);
}
void printf_with_name(char *name, vector_t *v)
{
    printf("%s\n\t", name);
    print_vector(*v);
}

void calculat_geometry(camera_t *camera)
{
    vector_t *aligment;
    aligment = minus(camera->loockat, camera->position);
    normalize(aligment);
    camera->screen_u = cross(*aligment, *camera->up);
    normalize(camera->screen_u);
    camera->screen_v = cross(*camera->screen_u, *aligment);
    normalize(camera->screen_v);
    camera->screen_center = pluse(camera->position, num_muliplication(aligment,
                                                                      camera->lenght));
    camera->screen_u = num_muliplication(camera->screen_u,
                                         camera->horizontal_size);

    camera->screen_v = num_muliplication(camera->screen_v,
                                         camera->horizontal_size / camera->aspect_ration);
}

void PrintRay(ray_t *ray)
{
    for (int i = 0; i < 10; i++)
        printf("-");
    printf("\n");
    printf("point1 : \n\t");
    print_vector(*ray->point1);
    printf("point2 : \n\t");
    print_vector(*ray->point2);
    printf("m_lab : \n\t");
    print_vector(*ray->m_lab);
    for (int i = 0; i < 10; i++)
        printf("-");
    printf("\n\n");
}

ray_t *generate_ray(camera_t *camera, double screenX, double screenY)
{
    vector_t *w_part1;
    vector_t *dst_cords;
    ray_t *new_ray;

    w_part1 = pluse(camera->screen_center, num_muliplication(camera->screen_u,
                                                        screenX));
    dst_cords = pluse(w_part1, num_muliplication(camera->screen_v, screenY));
    new_ray = malloc(sizeof(ray_t));
    new_ray->point1 = copy_vector(*camera->position);
    new_ray->point2 = dst_cords;
    new_ray->m_lab = minus(dst_cords, camera->position);
    // printf("-------------------------------------- \n");
    // printf_with_name("new_ray->point1", new_ray->point1);
    // printf_with_name("new_ray->point2", new_ray->point2);
    // printf_with_name("new_ray->m_lab", new_ray->m_lab);
	// printf("-------------------------------------- \n");
    return (new_ray);
}
