// Synopsis: Example program illustrating how to use the Seb library
//
// Authors: Martin Kutz <kutz@math.fu-berlin.de>,
//          Kaspar Fischer <kf@iaeth.ch>

#include <iostream>
#include <cstdio>

#include "Seb.h"
#include "Seb_debug.h"
#include "Seb_debug.C" // ... only needed because we use Seb::Timer below

inline void loadPoints2d(const std::string& filename, std::vector<Seb::Point<double>>& points) {
    typedef double FT;
    typedef Seb::Point<FT> Point;
    typedef std::vector<Point> PointVector;

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Could not open the file!" << std::endl;
        return;
    }
    int d = 2;
    std::string line;
    while (std::getline(file, line)) {

        line.erase(std::remove(line.begin(), line.end(), '{'), line.end());
        line.erase(std::remove(line.begin(), line.end(), '}'), line.end());
        line.erase(std::remove(line.begin(), line.end(), ','), line.end());

        std::istringstream iss(line);
        double x, y;
        std::vector<double> coords(d);
        if (iss >> x >> y) {
            coords[0] = x;
            coords[1] = y;
            //points.push_back(Point(x,y)) 
            points.push_back(Point(d,coords.begin()));
        } else {
            std::cerr << "Error parsing line: " << line << std::endl;
        }
    }
}

int main(int argn,char **argv) {
  typedef double FT;
  typedef Seb::Point<FT> Point;
  typedef std::vector<Point> PointVector;
  typedef Seb::Smallest_enclosing_ball<FT> Miniball;

  using std::cout;
  using std::endl;
  using std::vector;

  cout << "====================================================" << endl
       << "Seb example" << endl;

  /* original code, commented as we don't use it  
  // Check for right number of arguments ...
  if (argn < 3) {
    cout << "Usage: " << argv[0] << " number-of-points dimension [boundary]" << endl
         << "If 'boundary' is given, all points will be on the boundary of a sphere." << endl
	 << "====================================================" << endl;
    return 1;
  }
  cout << "====================================================" << endl;
  // ... and parse command line arguments
  const int n = std::atoi(argv[1]), d = std::atoi(argv[2]);
  const bool on_boundary = argn > 3 && std::string(argv[3]) == "boundary";
  */
  int d = 2;

  // Construct n random points in dimension d
  PointVector S;
  vector<double> coords(d);
  srand(clock());
  /* original code to generate points, commented as we don't use it
  for (int i=0; i<n; ++i) {

    // Generate coordindates in [-1,1]
    double len = 0;
    for (int j=0; j<d; ++j) {
      coords[j] = static_cast<FT>(2.0*rand()/RAND_MAX - 1.0);
      len += coords[j]*coords[j];
    }

    // Normalize length to "almost" 1 (makes it harder for the algorithm)
    if (on_boundary) {
      const double Wiggle = 1e-2;
      len = 1/(std::sqrt(len)+Wiggle*rand()/RAND_MAX);
      for (int j=0; j<d; ++j)
        coords[j] *= len;
    }
    S.push_back(Point(d,coords.begin()));
  }
  */
  loadPoints2d("data.txt", S);

  cout << "Starting computation..." << endl
       << "====================================================" << endl;
  Seb::Timer::instance().start("all");

  // Compute the miniball by inserting each value
  Miniball mb(d, S);

  // Output
  FT rad = mb.radius();
  FT rad_squared = mb.squared_radius();
  cout << "Running time: " << Seb::Timer::instance().lapse("all") << "s" << endl
       << "Radius = " << rad << " (squared: " << rad_squared << ")" << endl
       << "Center:" << endl;
  Miniball::Coordinate_iterator center_it = mb.center_begin();
  for (int j=0; j<d; ++j)
    cout << "  " << center_it[j] << endl;
  cout << "=====================================================" << endl;

  mb.verify();
  cout << "=====================================================" << endl;
}
