#ifndef Q1_H
#define Q1_H
#include <cmath>
#include <functional>
namespace q1 {
double gradient_descent(double init, double step,
                        std::function<double(double)> func);
const double delta = 1e-3;
const double epsilon = 1e-10;
double derivative(double x, const std::function<double(double)> &func) {
  return (func(x + delta) - func(x - delta)) / (2 * delta);
}
template <typename T, typename F>
T gradient_descent(T init, T step) {
  return gradient_descent(init, step, F());
}
double gradient_descent(double init, double step,
                        std::function<double(double)> func) {
  double cur = init;
  double d = derivative(cur, func);
  while (std::abs(d) > epsilon) {
    cur = cur - step * d;
    d = derivative(cur, func);
  }
  return cur;
}

}  // namespace q1
#endif  // Q1_H
