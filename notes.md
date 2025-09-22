# Introduction to 3D Graphics Workshop [Slide 1]
- Welcome
- Who has done graphics programming before, visualisations etc...

## Why? [Slide 2]
- Graphics programming is an incredibly rewarding area in computer science.
- Deepen your understanding of mathematics, physics, algorithms, computer hardware, optimisations, visual art, game development, tooling, and more.
- You can learn hard things, you just have to start small!

## What Are We Doing Today? [Slide 3]
- We will learn from the ground up how can we draw basic shapes and move them (1D), how we can move from screen space (pixel based space) to some world space (scaled space that is easier for us to work with).
- Learn about foundational mathematics used throughout 3D grpahics, vectors and matricies. Learn about transformations and learn how to draw more complex shapes (2D).
- And finally we will learn a few more concepts with matricies to make 3D possible.

## Black Box [Slide 4]
- In software, a black box is a metaphorical representation of some component or system.
- We pass in some input, the black box does its thing and produces some output. 
- To truely understand a black box we need to dig deep into the system.

## Black Box [Slide 5]
- The high-level black box in 3D graphics looks something like this.
- Our input is data representing shapes, the transformations applied to the shapes (like rotations, scale, position, etc...).
- This input passes through some black box.
- Resulting in our output, pixels being rendered to a canvas in a way the we expect.

## From Black Box -> White Box [Slide 6]
- Understanding how systems work requires us to dig deep, figure out the steps/implementation required to have a clear view of what actually happens inside the black box.
- My goal for this workshop is to demistify the black box of 3D graphics.
- But first lets think about the problem we are trying to solve.


## The Problem [Slide 7]
- Screens are 2D -> flat
- We want 3D -> objects have depth
- The Challenge (The Black Box) -> how is the perception of depth (3D) achieved on a 2D screens.

## Don't be afraid of the C [Slide 8]
- You may have heard of the C programming language before; some may hate it because of CAB202; however, it's actually quite a simple language, also it's super portable and has been battle tested for over 50 years!
- You don't need a deep understanding of C to read the code shown during this workshop.
- If you have experience with any other language you should be able to follow.
- I will explain any C specific techniques used, so rest assured.
- To ensure that this workshop isn't a multi-day exercise, I will be using a 3rd party library to make creating a window, and drawing pixels.
- If you haven't heard of Raylib before, its a simple library used to do video game programming.
- Although raylib already has the ability to do 3D, I won't be using any of that functionality as we want to see for ourselfs how 3D works.

# Setting up the environment [Slide 9]
- I will now demonstrate the setup required to run the code used in this workshop.

# Topic 1: 1D [Slide 10]
- 