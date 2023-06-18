#include "headers/types.h"
#include "lib/lib.h"
#include "Objects/headers/spher.h"
#include "math_lib/headers/vectormath.h"
#include "math_lib/headers/matrex.h"
#include "headers/camera.h"
#include "headers/image.h"

scene_t *Scene()
{
	scene_t *scene = malloc(sizeof(scene_t));
	// objects
	scene->m_object_list = NULL;
	double values[] = 
	{	1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1};
	object_t *sphere = create_sphere(matrix(4,4, values), matrix(4,4, values), matrix(4,4, values), vector(1, 1, 1));

	push_back(&scene->m_object_list, ft_lstnew(sphere));

	scene->m_camera = Camera();
	calculat_geometry(scene->m_camera);

	return (scene);
}


t_image *Render(scene_t *scene)
{


}

