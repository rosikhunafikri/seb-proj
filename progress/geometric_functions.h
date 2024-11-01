using std::vector;

class Line {       
  public:             
    float gradient;        
    float c_value; 
    Line (float g, float c){
      gradient = g;
      c_value = c;
    }
};

vector <float> midpoint_func (vector<float> A, vector<float> B){

  vector <float> mid;

  float x_mid = (A[0] + B[0]) / 2;
  float y_mid = (A[1] + B[1]) / 2;

  mid.push_back(x_mid);
  mid.push_back(y_mid);

  return mid;

}

float gradient_func (vector<float> A, vector<float> B){

  float m = (B[1] - A[1]) / (B[0] - A[0]);

  return m;
}

float perpendicular_gradient_func(float m){

  float m_perp = -1 / m;

  return m_perp;

}

// calculates distance between 2 points
float segment_func (vector<float> A, vector<float> B){

  float segment = sqrt(pow((B[1] - A[1]),2) + pow((B[0] - A[0]),2));

  return segment;

}

float eol_g_p (vector <float> A, float gradient){

  float c_gp = A[1] - (gradient * A[0]);

  return c_gp;

}

float eol_pp (vector <float> A, vector <float> B){

  float m_pp = gradient_func(A,B);

  float c_pp = (-m_pp * A[0]) + A[1]; //MUST USE FIRST POINT AS REFERENCE!

  return c_pp;

}

vector <float> new_coordinate_func (Line A, Line B){

  vector <float> new_coordinate;
  float x = (B.c_value - A.c_value) / (A.gradient - B.gradient);
  float y = (B.gradient) * x + B.c_value;
  new_coordinate.push_back(x);
  new_coordinate.push_back(y);

  return new_coordinate;
}
