#include <iostream>
#include <vector>
#include <cmath>
#include <array>
#include <bits/stdc++.h>
// #include "geometric_functions.h"

using namespace std;

class Line {       
  public:             
    float gradient;        
    float c_value; 
    Line (float g, float c){
      gradient = g;
      c_value = c;
    }
    Line(){
        gradient = 0.0;
        c_value = 0.0;
    }
};


class Point {       
  public:
    static Point ref;     
    float x;        
    float y;
    Point (float x_, float y_){
      x = x_;
      y = y_;
    }
    Point (){
      x = ref.x;
      y = ref.y;
    }

    float segment(){
        float segment = sqrt(pow((x - ref.x),2) + pow((y - ref.y),2));
        return segment;
    }

    Point refers_to(){
        return Point(x - ref.x, y - ref.y);
    }

    //for cout, leave as it is
    friend ostream& operator<<(ostream& os, const Point& obj) {
        os << "(" << obj.x << "," << obj.y << ")";
        return os;
    }
};


bool point_comparator(Point a, Point b){
    bool a_is_bigger; //for descending
    a_is_bigger = a.segment() > b.segment();
    return a_is_bigger;
}

vector <Point> point_sorter (vector <Point> points, Point avg){
    Point random_point = avg; // for the D point which is [1,2]
    Point::ref = random_point;

    vector<Point> sorted;
    cout << "inside point sorter" << endl;
    /*
    for (int i = 0 ; i < points.size() ; i++){
        sorted[i] = points[i];
        cout << i << ": " << sorted[i] << endl;
    }
    */
    sorted = points;
    cout << "begin sorting..." << endl;
    sort(sorted.begin(), sorted.end(), point_comparator);
    cout << "sorted:" << endl;
    for (int i = 0 ; i < sorted.size() ; i++){
        cout << i << ": " << sorted[i] << endl;
    }


    return sorted;

}

Point midpoint_func (Point A, Point B){

  Point mid;

  float x_mid = (A.x + B.x) / 2;
  float y_mid = (A.y + B.y) / 2;

  mid.x = x_mid;
  mid.y = y_mid;

  return mid;

}

//modified: finds the average point instead
Point closest_point_to_center(vector<Point> points) {

    Point avg_point;
    Point accumulator;
    size_t num_points = points.size();

    for (int i = 0; i < points.size(); i++){
        accumulator.x += points[i].x;
        accumulator.y += points[i].y;
    }

    avg_point.x = accumulator.x / num_points;
    avg_point.y = accumulator.y / num_points;
    

    return avg_point; 
}

float gradient_func (Point A, Point B){

  float m = (B.y - A.y) / (B.x - A.x);

  return m;
}

float perpendicular_gradient_func(float m){

  float m_perp = -1.0 / m;

  return m_perp;

}

Line eol_g_p (Point A, float gradient){
  Line output;
  float new_gradient = perpendicular_gradient_func(gradient);
  float c_gp = A.y - (new_gradient * A.x);

  output.gradient = new_gradient;
  output.c_value = c_gp;

  return output;

}

Line eol_pp (Point A, Point B){
    Line output;
  float m_pp = gradient_func(A,B);

  float c_pp = (-m_pp * A.x) + A.y; //MUST USE FIRST POINT AS REFERENCE!

  output.gradient = m_pp;
  output.c_value = c_pp;

  return output;

}

bool similarity_check(Point A, Point B){
  bool x_similar = abs(A.x - B.x) < 0.0001;
  bool y_similar = abs(A.y - B.y) < 0.0001;
  return x_similar && y_similar;
}

bool affine_dependent_check (vector <Point> A){
    cout << "checking if affine dependent" << endl;
    // 0 is false. !0 is true
    
    Line affine_checker;
    
    affine_checker = eol_pp(A[0], A[1]);

    cout << "gradient: " << affine_checker.gradient << ". c = " <<  affine_checker.c_value << endl;
    cout << "y = " << A[2].y << endl;
    cout << "mx+c = " << affine_checker.gradient * A[2].x + affine_checker.c_value << endl; 
    //
    bool result = abs (affine_checker.gradient * A[2].x + affine_checker.c_value - A[2].y) < 0.0001;
    cout << "affine check result: " << result << endl;
    return result;   
}

Point new_coordinate_func (Line A, Line B){

  Point new_coordinate;
  float x = (B.c_value - A.c_value) / (A.gradient - B.gradient);
  float y = (B.gradient) * x + B.c_value;
  new_coordinate.x = x;
  new_coordinate.y = y;

  return new_coordinate;
}


Point Point::ref = Point(0,0);

int main() {

    // vector <float> midpoint_placeholder;
    // vector <float> new_coordinate_placeholder;
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
    Point mp_A;
    Point mp_B;
    float grad_A;
    float grad_B;
    grad_A = gradient_func(three_points[0], three_points[1]);
    grad_B = gradient_func(three_points[0], three_points[2]);
    mp_A = midpoint_func(three_points[0], three_points[1]);
    mp_B = midpoint_func(three_points[0], three_points[2]);

    AC = eol_g_p(mp_A,grad_A);
    FC = eol_g_p(mp_B,grad_B);

    cout << "New coordinates are: " << new_coordinate_func(AC,FC) << endl;



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