<h1 align="center">
  <br>
  <a href="http://www.amitmerchant.com/electron-markdownify"><img src="https://github.com/byaliego/42-project-badges/blob/main/badges/minirtm.png?raw=true" alt="MiniRT42" width="200"></a>
  <br>
  MiniRT 42
  <br>
</h1>

<p align="center">
When it comes to rendering 3-dimensional computer-generated images there are 2 possible approaches: “Rasterization”, which is used by almost all graphic engines because
of its efficiency and “Ray Tracing.”</br>
The “Ray Tracing” method, developed for the first time in 1968 (but improved upon
since) is even today more expensive in computation than the “Rasterization” method.
As a result, it is not yet fully adapted to real time use-cases but it produce a much higher
degree of visual realism.
</p>

##

# ![](https://i.pinimg.com/originals/4c/db/2f/4cdb2f06617f18e398b3ed23a5705739.jpg)

## How It works ?

### An Overview of the Ray-Tracing Rendering Technique
Ray tracing is a sophisticated computer graphics technique that replicates the behavior of light in a virtual environment 
to produce highly realistic and detailed images. It operates by initiating rays from a virtual camera through each pixel on 
an image plane. These rays are then traced through the scene, testing for intersections with objects. Upon intersection,
the properties of the surface are evaluated, including its interaction with light sources and environmental factors.
Secondary rays are often cast to simulate effects like reflections, refractions, shadows, and global illumination. 
This recursive process captures intricate light interactions. The resulting color and intensity information carried 
by the rays is accumulated and blended to compute the final pixel colors. This culminates in the rendering of the scene, 
showcasing how light interacts with virtual objects and surfaces. While immensely capable of generating stunning visuals, 
ray tracing is computationally demanding, necessitating powerful hardware and often involving optimization methods to manage its complexity.


![](https://www.scratchapixel.com/images/ray-tracing-refresher/rt-setup2.png)

## Light Transport
Light transport is a fundamental principle in ray tracing, enabling the simulation of realistic lighting interactions within a virtual environment. Ray tracing starts by casting rays from a virtual camera through each pixel on the image plane, simulating the paths that light rays would take. These rays are traced as they travel through the scene, checking for intersections with objects. When an intersection is found, the properties of the surface are assessed, taking into account its interaction with various light sources and environmental conditions. To capture intricate lighting effects, secondary rays are often cast, representing reflections, refractions, shadows, and global illumination. These secondary rays can themselves generate more rays in a recursive process, simulating complex light behaviors. As rays traverse the scene, they accumulate color and intensity information, which is then blended to compute the final colors for each pixel. This comprehensive process ultimately yields a rendered image that portrays how light interacts with virtual objects and surfaces, delivering a high degree of visual realism. However, due to its computational complexity, achieving accurate light transport often requires advanced optimization techniques and robust hardware resources.

# Diffuse lighting & Shadows
<div style="display: flex; flex-wrap: wrap;">
  <div style="flex: 50%">
    <figure style="height: 500px">
      <img src="https://www.scratchapixel.com/images/introduction-to-ray-tracing/lightingnoshadow.gif" alt="Image 1" style="width: 100%; object-fit: fill;">
    </figure>
  </div>
  <div style="flex: 50%;">
    <figure style="height: 500px">
      <img src="https://www.scratchapixel.com/images/introduction-to-ray-tracing/lightingshadow.gif" alt="Image 2" style="width: 100%; object-fit: fill;">
    </figure>
  </div>
</div>

# Reflection & Refraction

| Reflection | Refraction |
|---------|---------|
| ![Image 1](https://www.scratchapixel.com/images/ray-tracing-refresher/rt-reflection2.gif?) | ![Image 2](https://www.scratchapixel.com/images/ray-tracing-refresher/rt-refraction2.gif?) |

| Example|
|---------|
| ![Image 3](https://github.com/jrayoub/miniRT42/blob/main/rendred_scenes/reflection.png?raw=true)


## Demo

|         |        |
|---------|---------|
| ![Image 1](https://github.com/jrayoub/miniRT42/blob/main/rendred_scenes/bm.png?raw=true) | ![Image 2](https://github.com/jrayoub/miniRT42/blob/main/rendred_scenes/bmpmap.png?raw=true) |


|         |        |
|---------|---------|
| ![Image 1](https://github.com/jrayoub/miniRT42/blob/main/rendred_scenes/checker.png?raw=true) | ![Image 2](https://github.com/jrayoub/miniRT42/blob/main/rendred_scenes/cone.png?raw=true) |



|         |        |
|---------|---------|
| ![Image 1](https://github.com/jrayoub/miniRT42/blob/main/rendred_scenes/mt_light.png?raw=true) | ![Image 2](https://github.com/jrayoub/miniRT42/blob/main/rendred_scenes/sp.png?raw=true) |

| |
|---------|
| ![Image 3](https://github.com/jrayoub/miniRT42/blob/main/rendred_scenes/reflection.png?raw=true)



## How To Use

To clone and run this application, you'll need [Git](https://git-scm.com) and [Minilibx](https://github.com/harm-smits/42docs) installed on your computer.

From your command line:

```bash
# Clone this repository
$ git clone https://github.com/jrayoub/miniRT42.git

# Go into the repository
$ cd miniRT42

# Build the Project
$ Make bonus

# Run the app
$ ./miniRTBONUS ./scene/Bonus/<scene_name.rt>
## replace <scene_name.rt> with the name of scene you want to render 
```

## Built with 
- [Minilibx 42](http://www.w3schools.com/jquery/jquery_ref_ajax.asp) -MiniLibX is a tiny graphics library which allows you to do the most basic things for rendering
  </br>something in screens without any knowledge of X-Window and Cocoa. It provides so-called simple window creation,</br>
   a questionable drawing tool, half-ass image functions and a weird event management system.


## Resources
[Ray tracing from scratch \[C++ & SDL2\]](https://www.youtube.com/watch?v=JN5yUrJPThI)<br>
[Ray-Tracing Rendering Technique](https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-overview/light-transport-ray-tracing-whitted.html)<br>

## Authors
- [@jrayoub](https://www.github.com/jrayoub)


## You may also like...

- [raytracing](https://github.com/jrayoub/raytracing) - a ray tracer created from scratch in C++ using the SDL2 library

## License

MIT

---

> [jrayoub.github.io](https://jrayoub.github.io/AyoubAitouna/) &nbsp;&middot;&nbsp;
> GitHub [@jrayoub](https://github.com/jrayoub) &nbsp;&middot;&nbsp;
> Twitter [@Ayoub_Aitouna](https://twitter.com/Ayoub_Aitouna)