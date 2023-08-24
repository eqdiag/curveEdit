# curveEdit

Application for editing and visualizing common curve representations.

Uses my custom math library: [gMath](https://github.com/eqdiag/gMath)

All dependencies are self-contained in this project using git's submodule system.

## Installation

```
git clone https://github.com/eqdiag/curveEdit
mkdir -p out/build
cd out/build
cmake ../..
make
```

## Color Key
  *  `Blue` = Control Curve/Polygon
  *  `Red` = Bezier Curve
  *  `Green` = BSpline
  *  `Magenta` = Subdivision Curve

## Keyboard Controls

  * `LEFT_CTRL` Clamps mouse cursor position to closest grid point (Hold)
  * `LEFT_ALT` Modifies position of closest control point (Hold)
  * `r` Reset camera position to the origin
  * `z` Decrease the number of curve samples (For Bezier and BSpline)
  * `x` Increase the number of curve samples (For Bezier and BSpline)
  *`[` Reset the subdivision depth to the control curve level (For Subdivision Curves)
  *`]` Increase the subdivision depth (For Subdivision Curves)
  *`1` Toggle display of Control Curve
  *`2` Toggle display of Bezier Curve
  *`3` Toggle display of BSpline Curve
  *`4` Toggle display of Subdivision Curve
  *`WASD` Movement around grid
  * `ESC` Exit program


## Mouse Controls
  * `leftClick` Adds points to control curve
  * `rightClick` Removes points from control curve
  * `mouseScroll` Zoom camera in/out

## Potential Future Additions
* Saving/Loading Curves
* [Surfaces of revolution](https://en.wikipedia.org/wiki/Surface_of_revolution#:~:text=A%20surface%20of%20revolution%20is,is%20the%20solid%20of%20revolution.)
* Better line drawing (currently using OpenGL's default GL_LINES primitive which is ugly)
                       
## Copyright and Attribution
Copyright (c) 2023 eqdiag. Released under the [MIT License](https://github.com/eqdiag/curveEdit/blob/main/LICENSE.md).
