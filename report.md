# midterm project
# Implement and optimize a fixed-size algorithm with ESL platform

## Introduction
### Emboss filter
An emboss filter gives a 3D shadow effect to the image, the result is very useful for a bumpmap of the image. It can be achieved by taking a pixel on one side of the center, and subtracting one of the other side from it. Pixels can get either a positive or a negative result. To use the negative pixels as shadow and positive ones as light, for a bumpmap, a bias of 128 is added to the image. Now, most parts of the image will be gray, and the sides will be either dark gray/black or bright gray/white.


## Implementation details 

### - Gaussian Kernel Generation
The approximation to 3x3 Gaussian kernel used in designing gaussian filter is:\\
```sh
#define filterWidth 3
#define filterHeight 3

double filter[filterHeight][filterWidth] =
{
  -1, -1,  0,
  -1,  0,  1,
   0,  1,  1
};

double factor = 1.0;
double bias = 128.0;
```
After designing the kernel we need to implement it to bitmap image for blurring. The center value of this filter will be the largest. 


