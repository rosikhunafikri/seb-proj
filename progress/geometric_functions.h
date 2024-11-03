#include <iostream>
#include <cmath>
#include <array>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

//makes line objects - contains gradient and c-value
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

//makes point objects - contains x and y coordinates
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

//used later to sort
bool point_comparator(Point a, Point b){
    bool a_is_bigger; //for descending
    a_is_bigger = a.segment() > b.segment();
    return a_is_bigger;
}

//used to sort the points in descending order
vector <Point> point_sorter (vector <Point> points, Point avg){
    Point random_point = avg; // for the D point which is [1,2]
    Point::ref = random_point;

    vector<Point> sorted;
    sorted = points;
    // cout << "begin sorting..." << endl;
    sort(sorted.begin(), sorted.end(), point_comparator);
    // cout << "sorted:" << endl;
    // for (int i = 0 ; i < sorted.size() ; i++){
    //     cout << i << ": " << sorted[i] << endl;
    // }


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


//used to find equation of bisector
Line eol_g_p (Point A, float gradient){
  Line output;
  float new_gradient = perpendicular_gradient_func(gradient);
  float c_gp = A.y - (new_gradient * A.x);

  output.gradient = new_gradient;
  output.c_value = c_gp;

  return output;

}

//used to find equation of line
Line eol_pp (Point A, Point B){
    Line output;
  float m_pp = gradient_func(A,B);

  float c_pp = (-m_pp * A.x) + A.y; //MUST USE FIRST POINT AS REFERENCE!

  output.gradient = m_pp;
  output.c_value = c_pp;

  return output;

}

//used to check for similar points
bool similarity_check(Point A, Point B){
  bool x_similar = abs(A.x - B.x) < 0.0001;
  bool y_similar = abs(A.y - B.y) < 0.0001;
  return x_similar && y_similar;
}

//used to check for affine dependence
bool affine_dependent_check (vector <Point> A){
    // cout << "checking if affine dependent" << endl;
    // 0 is false. !0 is true
    
    Line affine_checker;
    
    affine_checker = eol_pp(A[0], A[1]);

    // cout << "gradient: " << affine_checker.gradient << ". c = " <<  affine_checker.c_value << endl;
    // cout << "y = " << A[2].y << endl;
    // cout << "mx+c = " << affine_checker.gradient * A[2].x + affine_checker.c_value << endl; 
    //
    bool result = abs (affine_checker.gradient * A[2].x + affine_checker.c_value - A[2].y) < 0.0001;
    // cout << "affine check result: " << result << endl;
    return result;   
}

//used to find new coordinate
Point new_coordinate_func (Line A, Line B){

  Point new_coordinate;
  float x = (B.c_value - A.c_value) / (A.gradient - B.gradient);
  float y = (B.gradient) * x + B.c_value;
  new_coordinate.x = x;
  new_coordinate.y = y;

  return new_coordinate;
}

// use to immediately find perpendicular bisector!
Line perpendicular_bisector_func(Point A, Point B){
  Point mp = midpoint_func(A, B);
  float gradient = gradient_func(A, B);
  //already done eol_g_p
  //float new_gradient = -1 / gradient ;
  Line p_bisector = eol_g_p(mp, gradient);
  return p_bisector;
}



Point Point::ref = Point(0,0);