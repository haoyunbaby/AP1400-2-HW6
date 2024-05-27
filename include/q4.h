#ifndef Q4_H
#define Q4_H
#include <algorithm>
#include <numeric>
#include <vector>
namespace q4 {

struct Vector2D {
  double x{};
  double y{};
};
struct Sensor {
  Vector2D pos;
  double accuracy;
};
Vector2D kalman_filter(const std::vector<Sensor>& sensors) {
  if (sensors.empty()) {
    return {0.0, 0.0};
  }
  Vector2D ans = {0, 0};
  double sum = std::accumulate(
      sensors.begin(), sensors.end(), 0.0,
      [](double sum, const Sensor& s) { return sum += s.accuracy; });
  std::for_each(sensors.begin(), sensors.end(), [&ans, sum](const Sensor& s) {
    ans.x += s.pos.x * s.accuracy / sum;
    ans.y += s.pos.y * s.accuracy / sum;
  });
  return ans;
}
}  // namespace q4
#endif  // Q4_H
