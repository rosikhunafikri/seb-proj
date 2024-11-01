#include <iostream>
#include <vector>
#include <cmath>
#include <array>
#include <bits/stdc++.h>
#include "geometric_functions.h"

using namespace std;

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

vector <Point> point_sorter (vector <Point> points){
    Point random_point = points[3]; // for the D point which is [1,2]
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
    

    coordinate_placeholder.push_back(A);
    coordinate_placeholder.push_back(B);
    coordinate_placeholder.push_back(C);
    coordinate_placeholder.push_back(D);
    coordinate_placeholder.push_back(E);
    coordinate_placeholder.push_back(F);

    //to remove the first element
    //coordinate_placeholder.erase(coordinate_placeholder.begin());


    for (int i = 0; i < coordinate_placeholder.size(); i++){
        cout << coordinate_placeholder[i] << endl;
    }

    sorted_coordinate_placeholder = point_sorter(coordinate_placeholder);

    vector<Point> T;
    float max_distance = sorted_coordinate_placeholder[0].segment(); //circle radius
    Point next_max_point;
    
    for (int i = 0; i < sorted_coordinate_placeholder.size(); i++){
        Point p = sorted_coordinate_placeholder[i];
        if (p.segment() == max_distance){
            T.push_back(p);
            //sorted_coordinate_placeholder.erase(next(sorted_coordinate_placeholder, i));
        } else {
            next_max_point = p;
            break;
        }
    }
    cout << "Sorted: " << endl;
    for (int i = 0; i < sorted_coordinate_placeholder.size(); i++){
        Point shown_point = sorted_coordinate_placeholder[i];
        //cout
        cout << shown_point << endl;
    }
    cout << "T: " << endl;
    for (int i = 0; i < T.size(); i++){
        Point t_point = T[i];
        //cout
        cout << t_point << endl;
    }
    cout << "next max point: " << next_max_point << endl;

  return 0;
}