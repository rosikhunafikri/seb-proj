#include <iostream>
#include <vector>
#include <cmath>
#include "geometric_functions.h"

using namespace std;



class Line {       
  public:             
    float gradient;        
    float c_value; 
    Line (float g, float c){
      gradient = g;
      c_value = c;
    }
};




int main() {

  vector <float> midpoint_placeholder;
  vector <float> new_coordinate_placeholder;
  vector <float> p1 = {-3,10};
  vector <float> p2 = {8,2};
  vector <float> p3 = {1,2};



  // 11/8 is called integer division - if 11.0/8 then float division!

  Line l_1(11.0/8,41.0/16);
  // Line l_1(1.375,2.5625);
  Line l_2(-2,4);

  
  
 


  midpoint_placeholder = midpoint_func (p1,p2);

  float perp_grad = perpendicular_gradient_func(gradient_func(p1,p2));

  new_coordinate_placeholder = new_coordinate_func(l_1, l_2);

  


  cout << "Midpoint is: (" << midpoint_placeholder[0] << "," << midpoint_placeholder[1] << ")" << endl;


  cout << "Gradient is: " << gradient_func(p1,p2) << endl;

  cout << "Distance between is: " << segment_func(p1,p2) << endl;

  cout << "Gradient perpendicular is: " << perp_grad << endl;

  cout << "C-value for PB is: " << eol_g_p(midpoint_placeholder, perp_grad) << endl;

  cout << "C-value for 2-points is: " << eol_pp(p1,p3) << endl;

  cout << "New coordinate is: (" << new_coordinate_placeholder[0] << "," << new_coordinate_placeholder[1] << ")" << endl;

  return 0;
}

