#include "headers/camera.h"

camera_t *Camera(double horizontal_size, double lenght, double aspect_ration)
{
	camera_t *camera;

	camera = malloc(sizeof(camera_t));
	camera->position = NULL;
	camera->loockat = NULL;
	camera->up = NULL;
	camera->horizontal_size = horizontal_size;
	camera->lenght = lenght;
	camera->aspect_ration = aspect_ration;
	return (camera);
}

void SetPosition(camera_t *this, vector_t *position)
{
	this->position = position;
}

void SetUp(camera_t *this, vector_t *Up)
{
	this->up = Up;
}

void Setloockat(camera_t *this, vector_t *loockat)
{
	this->loockat = loockat;
}

void printf_with_name(char *name, vector_t *v)
{
	printf("%s\n\t", name);
	print_vector(*v);
}

void calculat_geometry(camera_t *this)
{
	vector_t *aligment;

	aligment = minus(this->loockat, this->position);
	normalize(aligment);
	this->screen_u = cross(*aligment, *this->up);
	normalize(this->screen_u);
	this->screen_v = cross(*this->screen_u, *aligment);
	normalize(this->screen_v);
	this->screen_center = pluse(this->position, num_muliplication(aligment,
																  this->lenght));
	this->screen_u = num_muliplication(this->screen_u,
									   this->horizontal_size);
	this->screen_v = num_muliplication(this->screen_v,
									   this->horizontal_size / this->aspect_ration);
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

ray_t *generate_ray(camera_t *this, double screenX, double screenY)
{
	vector_t *w_part1;
	vector_t *dst_cords;
	vector_t *scalled_u;
	vector_t *scalled_v;

	scalled_u = num_muliplication(this->screen_u,
								  screenX);
	scalled_v = num_muliplication(this->screen_v, screenY);
	w_part1 = pluse(this->screen_center, scalled_u);
	dst_cords = pluse(w_part1, scalled_v);
	free(w_part1);
	free(scalled_v);
	free(scalled_u);
	return (ray(copy_vector(*this->position), dst_cords));
}
