#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <iostream>
#include <cmath>
#include <utility>
#include <tuple>

using namespace std;

double DELTA = 0.1;
double TRI_SIDE = 5.0;
double TRI_HEIGHT = 4.330127019;

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
  if (triHeight <= 0 || area <= 0 || bottom <= 0) {
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
  double Eng1 = 0.185567;
  double Eng2 = 0.309278;
  double Senior = 0.2680412;
  double Principal = 0.1958762;
  double Partner = 0.03092783;

  double womenEng1 = 0.7777778;
  double womenEng2 = 0.3333333;
  double womenSenior = 0.1538461;
  double womenPrincipal = 0.05263157;
  double womenPartner = 0.0;

  double womenEng1Part = 0;
  double womenEng2Part = 0;
  double womenSeniorPart = 0;

  double triangleArea = 0;
  double triangleHeight = TRI_HEIGHT;
  double segmentTop = 0;
  double segmentBase = TRI_SIDE;
  double segmentHeight = 0;
  double valid;

  printf("In an org, there are 5 possible roles: Eng1, Eng2, Senior, "
         "Principal, and Partner\n");
  printf("Split a triangle into segments that represent how many people "
         "work in each of those 5 roles\n");
  printf("\tEng1 %% of Org:\t\t %.2f\n\tEng2 %% of Org:\t\t %.2f\n"
         "\tSenior %% of Org:\t %.2f\n\tPrincipal %% of Org:\t %.2f\n"
         "\tPartner %% of Org:\t %.2f\n\n", Eng1, Eng2, Senior, Principal, Partner);

  printf("Given an equilateral triangle with sides of %.2f\n", TRI_SIDE);
  triangleArea = getAreaTriangle(TRI_SIDE, TRI_HEIGHT);
  cout << "Triangle area: " << triangleArea << endl;

  if (triangleArea == EXIT_FAILURE) {
    cerr << "Invalid triangle area calculation" << endl;
    return EXIT_FAILURE;
  }
 
  // Eng 1 Calculations
  printf("--- SEGMENT 1: Eng1 ---\n");
  valid = trapezoidAreaReverse(segmentBase, triangleHeight, triangleArea * Eng1,
                               segmentHeight, segmentTop);
  if (valid == EXIT_FAILURE) {
    cerr << "Invalid area to trapezoid calculation" << endl;
    return EXIT_FAILURE;
  }
  printf("Eng1:\t\t Area (%.2f), Base (%.2f), Top (%.2f), Height (%.2f)\n", 
          triangleArea * Eng1, segmentBase, segmentTop, segmentHeight); 
  womenEng1Part = divideTrapezoid(segmentBase, segmentHeight, womenEng1);
  segmentBase = segmentTop;
  triangleHeight -= segmentHeight;

  // Eng 2 Calculations
  printf("--- SEGMENT 2: Eng2 ---\n");
  valid = trapezoidAreaReverse(segmentBase, triangleHeight, triangleArea * Eng2,
                               segmentHeight, segmentTop);
  if (valid == EXIT_FAILURE) {
    cerr << "Invalid area to trapezoid calculation" << endl;
    return EXIT_FAILURE;
  }
  printf("Eng2:\t\t Area (%.2f), Base (%.2f), Top (%.2f), Height (%.2f)\n", 
          triangleArea * Eng2, segmentBase, segmentTop, segmentHeight); 
  womenEng2Part = divideTrapezoid(segmentBase, segmentHeight, womenEng2);
  segmentBase = segmentTop;
  triangleHeight -= segmentHeight;

  // Senior Calculations
  printf("--- SEGMENT 3: Senior ---\n");
  valid = trapezoidAreaReverse(segmentBase, triangleHeight, triangleArea * Senior,
                               segmentHeight, segmentTop);
  if (valid == EXIT_FAILURE) {
    cerr << "Invalid area to trapezoid calculation" << endl;
    return EXIT_FAILURE;
  }
  printf("Senior:\t\t Area (%.2f), Base (%.2f), Top (%.2f), Height (%.2f)\n", 
          triangleArea * Senior, segmentBase, segmentTop, segmentHeight); 
  womenSeniorPart = divideTrapezoid(segmentBase, segmentHeight, womenSenior);
  segmentBase = segmentTop;
  triangleHeight -= segmentHeight;

  // Principal Calculations
  printf("--- SEGMENT 4: Principal ---\n");
  valid = trapezoidAreaReverse(segmentBase, triangleHeight, triangleArea * Principal,
                               segmentHeight, segmentTop);
  if (valid == EXIT_FAILURE) {
    cerr << "Invalid area to trapezoid calculation" << endl;
    return EXIT_FAILURE;
  }
  printf("Senior:\t\t Area (%.2f), Base (%.2f), Top (%.2f), Height (%.2f)\n\n", 
          triangleArea * Principal, segmentBase, segmentTop, segmentHeight); 
  segmentBase = segmentTop;
  triangleHeight -= segmentHeight;


  printf("Parition each of those 5 segments to show the proportion of "
         "women vs men\n");
  printf("\tWomen %% of Eng1:\t %.2f\tWidth: %.2f\n\tWomen %% of Eng2:\t %.2f\t"
         "Width: %.2f\n\tWomen %% of Senior:\t %.2f\tWidth: %.2f\n\tWomen %% of "
         "Principal:\t %.2f\n\tWomen %% of Partner:\t %.2f\n\n", 
         womenEng1, womenEng1Part, womenEng2, womenEng2Part, womenSenior, 
         womenSeniorPart, womenPrincipal, womenPartner);
  

  return EXIT_SUCCESS;
}
