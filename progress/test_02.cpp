#include <iostream>
#include <vector>
#include <cmath>
#include <array>
#include "geometric_functions.h"

using namespace std;



// class Line {       
//   public:             
//     float gradient;        
//     float c_value; 
//     Line (float g, float c){
//       gradient = g;
//       c_value = c;
//     }
// };

//TODO:
    /*
    1. pick random center [DONE-ish]
    2. calculate distance from all points with the centre
    3. sort points based on distance (descending)
    4. remove 1st data and parse thru to remove duplicates
    5. place 
    
    
    */

vector <vector <float>> point_sorter (vector <vector <float>> a){

    vector <float> random_point = a[3]; // for the D point which is [1,2]
    // vector <>;

    for (int i = 0; i < a[i].size(); i++){

        segment_func(a[i],random_point);

    }


}
   


int main() {

    // vector <float> midpoint_placeholder;
    // vector <float> new_coordinate_placeholder;
    vector <vector <float>> coordinate_placeholder;
    // [[-3,10]]

    vector <float> A = {-3,10};
    vector <float> B = {3,4};
    vector <float> C = {8,2};
    vector <float> D = {1,2};
    vector <float> E = {-1,1};
    vector <float> F = {2,-3};

    coordinate_placeholder.push_back(A);
    coordinate_placeholder.push_back(B);
    coordinate_placeholder.push_back(C);
    coordinate_placeholder.push_back(D);
    coordinate_placeholder.push_back(E);
    coordinate_placeholder.push_back(F);


    for (int i = 0; i < coordinate_placeholder.size(); i++){

        for (int j = 0; j < coordinate_placeholder[i].size(); j++){

            if (j == 0){
                cout << " [" << coordinate_placeholder[i][j];         
            }
            else{
                cout << "," << coordinate_placeholder[i][j] << "]" << endl;               
            }       
        }
    }

    






  return 0;
}

