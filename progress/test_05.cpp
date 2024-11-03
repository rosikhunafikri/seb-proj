#include <iostream>
#include <vector>
#include <cmath>
#include <array>
#include <bits/stdc++.h>
#include "geometric_functions.h"

using namespace std;



int main() {

    
    vector<Point> coordinate_placeholder;
    vector<Point> sorted_coordinate_placeholder;
    // [[-3,10]]

    Point A = Point(-3,10);
    Point B = Point(3,4);
    Point C = Point(8,2);
    Point D = Point(1,2); // intitial centre point
    Point E = Point(-1,1);
    Point F = Point(2,-3);
    Point F_affine = Point(2.05, -3.13);
    Point avg;

    coordinate_placeholder.push_back(A);
    coordinate_placeholder.push_back(B);
    coordinate_placeholder.push_back(C);
    coordinate_placeholder.push_back(D);
    coordinate_placeholder.push_back(E);
    coordinate_placeholder.push_back(F);
    // coordinate_placeholder.push_back(C);
    // coordinate_placeholder.push_back(C);
    // coordinate_placeholder.push_back(F);
    // coordinate_placeholder.push_back(F_affine);
    // coordinate_placeholder.push_back(E);
    // coordinate_placeholder.push_back(A);
    // coordinate_placeholder.push_back(F);
    // coordinate_placeholder.push_back(C);

    avg = closest_point_to_center(coordinate_placeholder);

    // cout << "Midpoint A and C: " << midpoint_func(A,C) << endl;
    // cout << "Gradient A and C: " << gradient_func(A,C) << endl;

    // cout << "Average Centre Point: " << avg << endl;
    
    // cout << "\n" << endl;
    // cout << "Initial S: " << endl;

    // for (int i = 0; i < coordinate_placeholder.size(); i++){
    //     cout << coordinate_placeholder[i] << endl;
    // }
    
    sorted_coordinate_placeholder = point_sorter(coordinate_placeholder, avg);
    
    vector <Point> three_points; // can write as our T
    float max_distance = sorted_coordinate_placeholder[0].segment(); //circle radius
    // Point point_two, point_three;

    int i_three = 0;
    while( three_points.size() < 3 ){
        Point p = sorted_coordinate_placeholder[i_three];
        cout << "checking " << p << endl;
        bool is_similar = false;
        for(int j=0; j<three_points.size(); j++){
          cout << "check similarity " << p << "and " << three_points[j] << endl;
          if (similarity_check(three_points[j], p)){
          cout << "result: similar, dropping point "<< p << endl;
            is_similar = true;
            break;
          }
        }
        if(!is_similar){
          three_points.push_back(p);
        }
        if (three_points.size() == 3){
          if(affine_dependent_check(three_points)){
            cout << "result: affine dependent" << endl;
            three_points.pop_back();
          }
        }
        i_three++;
    }

    cout << "Three Points: " << endl;
    for (int i = 0; i < three_points.size(); i++){
        Point three = three_points[i];
        //cout
        cout << three << endl;
    }

    // cout << "Point dependent? " << affine_dependent_check(three_points) << endl;

    Line AC, FC;
    // Point mp_A;
    // Point mp_B;
    // float grad_A;
    // float grad_B;
    // grad_A = gradient_func(three_points[0], three_points[1]);
    // grad_B = gradient_func(three_points[0], three_points[2]);
    // mp_A = midpoint_func(three_points[0], three_points[1]);
    // mp_B = midpoint_func(three_points[0], three_points[2]);

    // AC = eol_g_p(mp_A,grad_A);
    // FC = eol_g_p(mp_B,grad_B);

    

    AC = perpendicular_bisector_func(three_points[0], three_points[1]);
    FC = perpendicular_bisector_func(three_points[0], three_points[2]);


    Point new_center = new_coordinate_func(AC,FC);
    cout << "New coordinates are: " << new_coordinate_func(AC,FC) << endl;

    //set ref to new coordinate
    Point::ref = new_center;
    cout << "final radius check from T" << endl;
    for(int i = 0 ; i<three_points.size(); i++){
      Point p = three_points[i];
      cout <<"radius from " << p << ": " << p.segment() << endl;
    }

  return 0;
}




    // //to remove the first element
    // //coordinate_placeholder.erase(coordinate_placeholder.begin());


    

    

    // vector<Point> T;
    // float max_distance = sorted_coordinate_placeholder[0].segment(); //circle radius
    // Point next_max_point;
    
    // for (int i = 0; i < sorted_coordinate_placeholder.size(); i++){
    //     Point p = sorted_coordinate_placeholder[i];
    //     if (p.segment() == max_distance){
    //         T.push_back(p);
    //         //sorted_coordinate_placeholder.erase(next(sorted_coordinate_placeholder, i));
    //     } else {
    //         next_max_point = p;
    //         break;
    //     }
    // }
    // cout << "Sorted: " << endl;
    // for (int i = 0; i < sorted_coordinate_placeholder.size(); i++){
    //     Point shown_point = sorted_coordinate_placeholder[i];
    //     //cout
    //     cout << shown_point << endl;
    // }
    // cout << "T: " << endl;
    // for (int i = 0; i < T.size(); i++){
    //     Point t_point = T[i];
    //     //cout
    //     cout << t_point << endl;
    // }
    // cout << "next max point: " << next_max_point << endl;