#ifndef VECTOR2D_H_INCLUDED
#define VECTOR2D_H_INCLUDED

#include <math.h>
#include <iostream>

using namespace std;

class Vector2d {
public:
  Vector2d(double x, double y) {
    coord_[0] = x;
    coord_[1] = y;
  }
  Vector2d () {
    coord_[0] = 0.;
    coord_[1] = 0.;
  }
  void set (double x, double y) {
    coord_[0] = x;
    coord_[1] = y;
  }
  void set (int x, int y) {
    coord_[0] = static_cast<double>(x);
    coord_[1] = static_cast<double>(y);
  }
  double get_x () const {
    return coord_[0];
  }
  double get_y () const {
    return coord_[1];
  }
  void mul (double d) {
    coord_[0] *= d;
    coord_[1] *= d;
  }
  double operator[] (const size_t n) {
    return coord_[n];
  }
  bool operator== (const Vector2d& other) {
    return ((get_x() == other.get_x()) && (get_y() == other.get_y()));
  }
  Vector2d& operator= (const Vector2d& other) {
    coord_[0] = other.coord_[0];
    coord_[1] = other.coord_[1];
    return *this;
  }
  Vector2d& operator+= (const Vector2d& other) {
    coord_[0] += other.coord_[0];
    coord_[1] += other.coord_[1];
    return *this;
  }
  friend Vector2d operator+ (const Vector2d& v1, const Vector2d& v2) {
    Vector2d result (v1.get_x() + v2.get_x(), v1.get_y() + v2.get_y());
    return result;
  }
  Vector2d operator- () const {
    Vector2d result (-coord_[0], -coord_[1]);
    return result;
  }
  Vector2d operator* (double d) const {
    Vector2d result (coord_[0] * d, coord_[1] * d);
    return result;
  }
  void get_normalized (Vector2d& v) const {
    double norm2 = coord_[0] * coord_[0] + coord_[1] * coord_[1];
    double norm = sqrt(norm2);
    // The Null vector cannot be normalized
    if (norm < 1E-3) {
      cout << "*** WARNING: norm is dangerously tiny: " << norm << endl;
      v.coord_[0] = 0.;
      v.coord_[1] = 0.;
      return;
    }
    v.coord_[0] = coord_[0] / norm;
    v.coord_[1] = coord_[1] / norm;
  }
  double get_arg () const {
    if (coord_[0] > 0) {
      return atan(coord_[1] / coord_[0]);
    }
    else if (coord_[0] < 0) {
      return M_PI - atan(coord_[1] / -coord_[0]);
    }
    else {
      return (coord_[1] >= 0) ? (+M_PI) : (-M_PI);
    }
  }
  Vector2d& round_int () {
    coord_[0] = static_cast<int>(round(coord_[0]));
    coord_[1] = static_cast<int>(round(coord_[1]));
    return *this;
  }
  bool is_null () const {
   return (get_x() == 0.) && (get_y() == 0.);//<= 1E-3) && (get_y() <= 1E-3);
  }
  void print () const {
    cout << "(" << coord_[0] << ", " << coord_[1] << ")";
  }
private:
  double coord_[2];
};

#endif // VECTOR2D_H_INCLUDED
