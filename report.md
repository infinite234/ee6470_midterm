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
## Algorithms of Emboss Filter
The optimized Emboss filter accelerator has used
 Data unrolling with latency constraint

```sh
HLS_CONSTRAIN_LATENCY(0,6,"lat01");
HLS_UNROLL_LOOP (ALL,"SHIFT");

```

 Pipelining
 ```sh
HLS_PIPELINE_LOOP(HARD_STALL,2,"LOOP");

```
 Data Reuse
 The following design is for the Cache gaussian filter

![source image](https://github.com/infinite234/ee6470-hw2/blob/main/hw2/cache.png)<br/>

Here, as the window of 3*3 kernel slides we can see that only thr last column is new so we can send the first 3*3 kernel and then just update the last column. This will help in reducing the pixel transfer and just update the last column for computing the new R,G,B pixels.

## Algorithm and Design
Following is the design of emboss filter in stratus HLS.
for the splitted inputs           |  for non splitted inputs
:-------------------------:|:-------------------------:
![](https://github.com/infinite234/ee6470_hw5-hw6-hw7-hw1/blob/main/hw7/Screenshot%20from%202021-06-29%2011-22-01.png)  |  ![](https://github.com/infinite234/ee6470_hw5-hw6-hw7-hw1/blob/main/hw7/Screenshot%20from%202021-06-29%2011-22-04.png)

Following is the design of emboss filter in SCML Platform
![source image](https://github.com/infinite234/ee6470-hw2/blob/main/hw2/cache.png)<br/>

## Simulation Results
Following is the simulated cycles in ns for the different types of optimization
![source image](https://github.com/infinite234/ee6470-hw2/blob/main/hw2/cache.png)<br/>

Following is the simulated cycles in ns for the different types of optimization
![source image](https://github.com/infinite234/ee6470-hw2/blob/main/hw2/cache.png)<br/>

## Conclusion
Thus the area and the simulated cycles are less than that to non reuse data.
Also, the simulated cycles of DPA is more than BASIC but the area of DPA is less than BASIC.

 
