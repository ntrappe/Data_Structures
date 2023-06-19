#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <iostream>
#include <cmath>
#include <utility>
#include <tuple>

using namespace std;

double DELTA = 0.1;

/*------------------------------------------------------
 % Routine Name: getAreaTriangle
 % 
 % Description: Calculates area of triangle given base
 %   and height.
 % Result: Calculates height.
 % Return: Return area as double
 % Parameters:
 %
 % NAME               DESCRIPTION
 % -----------------------------------------------------
 % base               Base of triangle
 % height             Height of triangle
 -------------------------------------------------------*/
double getAreaTriangle(double base, double height) {
  if (base <= 0 || height <= 0) {
    return EXIT_FAILURE;
  }

  return (height * base) / 2;
}

/*------------------------------------------------------
 % Routine Name: getAreaTriangle
 % 
 % Description: Calculates area of an EQUILATERAL 
 %   triangle given one side.
 % Result: Calculates area.
 % Return: Return area as double
 % Parameters:
 %
 % NAME               DESCRIPTION
 % -----------------------------------------------------
 % side               One side of equilateral triangle
 -------------------------------------------------------*/
double getAreaTriangle(double side) {
  if (side <= 0) {
    return EXIT_FAILURE;
  }

  return ((sqrt (3)) / 4) * (side * side * side);
}

double getAreaTrapezoid(double top, double bottom, double height) {
  if (top <= 0 || bottom <= 0 || height <= 0) {
    return EXIT_FAILURE;
  }

  return ((top + bottom) / 2) * height;
}

/*------------------------------------------------------
 % Routine Name: getTrapTop
 % 
 % Description: Helper function to get the top length of a
 %   trapezoid to be used in calculating its area later
 % Result: Uses Tan to calculate size of adjacent side
 % Return: Length of trap top or FAILURE if invalid param
 % Parameters:
 %
 % NAME               DESCRIPTION
 % -----------------------------------------------------
 % triHeight          Height of entire equilateral triangle
 % traHeight          Height of trapezoid
 -------------------------------------------------------*/
double getTrapTop(double triHeight, double traHeight) {
  if (triHeight <= 0 || traHeight <= 0 || triHeight < traHeight) {
    return EXIT_FAILURE;
  }

  double heightMiniTri = triHeight - traHeight;
  double baseMiniTri = (heightMiniTri / (sqrt (3))) * 2;

  // cout << "mini triangle height (" << heightMiniTri << ") and base (" << baseMiniTri << ")\n";
  return baseMiniTri;
}

/*------------------------------------------------------
 % Routine Name: trapezoidAreaReverse
 % 
 % Description: Given an area for a trapezoid, find the
 %   dimensions it should be. By just adjusting the height
 %   we can calculate the equiv top length and then see if
 %   its area is close enough to our goal area.
 % Result: Finds closest height and base for trapezoid. Uses
 %   passing by reference to update those values.
 % Return: SUCCESS or FAILURE.
 % Parameters:
 %
 % NAME               DESCRIPTION
 % -----------------------------------------------------
 % bottom             Bottom/base of trapezoid (we know)
 % triHeight          Height of entire equilateral triangle
 % area               Goal area for trapezoid
 % height             Ref to height of trapezoid (calc)
 % top                Ref to top of trapezoid (calc)
 -------------------------------------------------------*/
int trapezoidAreaReverse(double bottom, double triHeight, double area,
                         double &height, double &top) {
  if (triHeight <= 0 || area <= 0 || bottom <= 0 || bottom > area) {
    return EXIT_FAILURE;
  }

  height = 0;
  top = 0;

  double tempArea = 0;	// calc approx areas for diff traps

  while (tempArea < area) {
    height += DELTA; 
    top = getTrapTop(triHeight, height);
    tempArea = getAreaTrapezoid(top, bottom, height);
    //printf("Trying height %.2f, got top %.2f, area is %.2f and goal is %.2f\n", height, top, tempArea, area); 
  }

  return EXIT_SUCCESS;
}

/*------------------------------------------------------
 % Routine Name: divideTrapezoid
 % 
 % Description: Given a trapezoid, we want to know where to
 %   draw a vertical partition [   W  | M] but we need to 
 %   get the width from left to that partition. We use the
 %   area of the big trapezoid and find the percent the little
 %   trap should take up til the partition.
 % Result: Width to the parition in the big trapezoid.
 % Return: partition width or FAILURE.
 % Parameters:
 %
 % NAME               DESCRIPTION
 % -----------------------------------------------------
 % bottom             Bottom/base of trapezoid (we know)
 % height             Height of trapezoid (we know)
 % portion            What percent [0-100%] to take up
 -------------------------------------------------------*/
double divideTrapezoid(double bottom, double height, double portion) {
  if (bottom <= 0 || height <= 0 || portion > 1 || portion < 0) {
    return EXIT_FAILURE;
  }
 
  if (portion < .01)
    return 0;

  double bigTrapArea = bottom * height;
  double smallTrapArea = bigTrapArea * portion;
  double smallTrapWidth = smallTrapArea / height;

  return smallTrapWidth;

}


int main() {
  cout << "Test 2 x 3 triangle should be 3: " << getAreaTriangle(3.0, 2.0) << endl;
  cout << "Test 2 x 3 x 4 trap should be 10: " << getAreaTrapezoid(2.0, 3.0, 4.0) << endl;
  cout << "Get trap new top w/ height 2.15 and base 5: " << getTrapTop(4.33013, 2.15) << endl;
  double height = 0;
  double top = 0;
  trapezoidAreaReverse(5, 4.33013, 8.1, height, top);
  printf("Height should be %.2f, top %.2f, for area %.2f\n", height, top, 8.1); 
  printf("%.2f of trapezoid, width is %.2f\n", 0.0, divideTrapezoid(5, 2.15, 0)); 
  printf("%.2f of trapezoid, width is %.2f\n", .30, divideTrapezoid(5, 2.15, .30)); 

  return EXIT_SUCCESS;
}
