#include <iostream>
#include <vector>
#include <cmath>
#include <array>
#include <fstream>
#include <bits/stdc++.h>
#include "geometric_functions.h"

using namespace std;


int main() {
  const string data = "data.txt";
  vector<Point> coordinate_placeholder;
  vector<Point> points;

  ofstream outfile("output.txt");
  if (!outfile) {
    cerr << "Error opening file for output" << endl;
    return 1;
  }

  loadPoints("data.txt", points);

  const Point A = points[0];
  const Point B = points[1];
  const Point C = points[2];
  const Point D = points[3];
  const Point E = points[4];
  const Point F = points[5];

  coordinate_placeholder.push_back(A);
  coordinate_placeholder.push_back(B);
  coordinate_placeholder.push_back(C);
  coordinate_placeholder.push_back(D);
  coordinate_placeholder.push_back(E);
  coordinate_placeholder.push_back(F);


  const Point avg = closest_point_to_center(coordinate_placeholder);

  cout << "Midpoint A and C: " << midpoint_func(A, C) << endl;
  cout << "Gradient A and C: " << gradient_func(A, C) << endl;

  cout << "Average Centre Point: " << avg << endl;

  cout << "\n" << endl;
  cout << "Initial S: " << endl;

  for (int i = 0; i < coordinate_placeholder.size(); i++) {
    cout << coordinate_placeholder[i] << endl;
    outfile << coordinate_placeholder[i] << endl;
  }

  vector<Point> sorted_coordinate_placeholder = point_sorter(coordinate_placeholder, avg);

  vector<Point> three_points; // can write as our T
  // float max_distance = sorted_coordinate_placeholder[0].segment(); //circle radius
  // Point point_two, point_three;

  int i_three = 0;
  while (three_points.size() < 3) {
    Point p = sorted_coordinate_placeholder[i_three];
    //cout << "checking " << p << endl;
    bool is_similar = false;
    for (int j = 0; j < three_points.size(); j++) {
      //cout << "check similarity " << p << "and " << three_points[j] << endl;
      if (similarity_check(three_points[j], p)) {
        //cout << "result: similar, dropping point " << p << endl;
        is_similar = true;
        break;
      }
    }
    if (!is_similar) {
      three_points.push_back(p);
    }
    if (three_points.size() == 3) {
      if (affine_dependent_check(three_points)) {
        cout << "result: affine dependent" << endl;
        three_points.pop_back();
      }
    }
    i_three++;
  }

  cout << "Three Points: " << endl;
  for (int i = 0; i < three_points.size(); i++) {
    Point three = three_points[i];
    cout << three << endl;
  }


  const Line AC = perpendicular_bisector_func(three_points[0], three_points[1]);
  const Line FC = perpendicular_bisector_func(three_points[0], three_points[2]);


  const Point new_center = new_coordinate_func(AC, FC);
  cout << "New coordinates are: " << new_coordinate_func(AC, FC) << endl;
  outfile << "New coordinates are: " << new_coordinate_func(AC, FC) << endl;

  //set ref to new coordinate
  Point::ref = new_center;
  cout << "final radius check from T" << endl;
  for (int i = 0; i < three_points.size(); i++) {
    Point p = three_points[i];
    cout << "radius from " << p << ": " << p.segment() << endl;
  }


  Point p = three_points[0];
  outfile << "radius is " << p.segment() << endl;


  return 0;
}