#include <iostream>
#include <vector>
#include <cmath>
#include <array>
#include <bits/stdc++.h>
// #include "geometric_functions.h"

using namespace std;

// to compare if point distance distance is larger or not
bool point_comparator(vector<float> a, vector<float> b){
    vector <float> ref = {0,0};
    bool a_is_bigger; //for descending
    a_is_bigger = segment_func(a,ref) > segment_func(b,ref);
    return a_is_bigger;
}






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

    vector<float> segment_vector;

    vector <vector <float>> sorted;

    for (int i = 0; i < a.size(); i++){
        cout << "entering function point sorter" << i << endl;

        vector<float> p;
        p[0] = a[i][0] - random_point[0];
        p[1] = a[i][1] - random_point[1];
        sorted.push_back(p);
        cout <<"p0 " << p[0] << endl;
        cout <<"p1 " << p[1] << endl;
    }
    
    cout << "sorted: " << endl;
    for (int i = 0; i < sorted.size(); i++){
        cout <<"x: " << sorted[i][0] << ", y: " << sorted[i][1] << endl;
    }


    sort(sorted.begin(), sorted.end(), point_comparator);

    return sorted;

}
   


int main() {

    // vector <float> midpoint_placeholder;
    // vector <float> new_coordinate_placeholder;
    vector <vector <float>> coordinate_placeholder;
    vector <vector <float>> sorted_coordinate_placeholder;
    // [[-3,10]]

    vector <float> A = {-3,10};
    vector <float> B = {3,4};
    vector <float> C = {8,2};
    vector <float> D = {1,2}; // intitial centre point
    vector <float> E = {-1,1};
    vector <float> F = {2,-3};

    coordinate_placeholder.push_back(A);
    coordinate_placeholder.push_back(B);
    coordinate_placeholder.push_back(C);
    coordinate_placeholder.push_back(D);
    coordinate_placeholder.push_back(E);
    coordinate_placeholder.push_back(F);

    //to remove the first element
    //coordinate_placeholder.erase(coordinate_placeholder.begin());


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

    sorted_coordinate_placeholder = point_sorter(coordinate_placeholder);

    cout << "Sorted: " << endl;

    cout << "sort level 1: " << coordinate_placeholder[0][0] << endl;
    cout << "sort level 1: " << coordinate_placeholder[0][1] << endl;
    cout << "sort level 2: " << coordinate_placeholder[1][0] << endl;
    cout << "sort level 2: " << coordinate_placeholder[1][1] << endl;

    

    for (int i = 0; i < sorted_coordinate_placeholder.size(); i++){

        for (int j = 0; j < sorted_coordinate_placeholder[i].size(); j++){

            if (j == 0){
                cout << " [" << sorted_coordinate_placeholder[i][j];         
            }
            else{
                cout << "," << sorted_coordinate_placeholder[i][j] << "]" << endl;               
            }       
        }
    }

    






  return 0;
}

