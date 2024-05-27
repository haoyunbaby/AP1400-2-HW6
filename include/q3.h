#ifndef Q3_H
#define Q3_H
#include <fstream>
#include <queue>
#include <regex>
#include <string>
namespace q3 {
struct Flight {
  std::string flight_number;
  size_t duration;
  size_t connections;
  size_t connection_times;
  size_t price;
};
auto cmp = [](auto a, auto b) {
  int i = a.duration + a.connection_times + 3 * a.price;
  int j = b.duration + b.connection_times + 3 * b.price;
  return i > j;
};
std::priority_queue<Flight, std::vector<Flight>, decltype(cmp)> gather_flights(
    std::string filename) {
  std::priority_queue<Flight, std::vector<Flight>, decltype(cmp)> pq(cmp);
  std::ifstream file(filename);
  std::string line;
  std::regex line_regex(
      "\\d+- flight_number:(\\w+) - duration:(\\d+h\\d*m?) - "
      "connections:(\\d+) - "
      "connection_times:((\\d+h\\d*m?(,\\d+h\\d*m?)*)?) - "
      "price:(\\d+)");
  std::regex duration_regex("(\\d+)h(\\d+)?m?");
  while (getline(file, line)) {
    Flight flight;

    std::smatch match;

    if (std::regex_search(line, match, line_regex)) {
      flight.flight_number = match[1];
      std::string duration_str = match[2];
      std::smatch d_match;
      if (std::regex_search(duration_str, d_match, duration_regex)) {
        size_t hours = stoi(d_match[1]);
        size_t minutes = d_match[2].matched ? stoi(d_match[2]) : 0;
        flight.duration = 60 * hours + minutes;
      }
      flight.connections = stoi(match[3]);
      std::string connection_times_str = match[4];
      flight.connection_times = 0;
      std::string token;
      std::istringstream token_stream(connection_times_str);
      while (getline(token_stream, token, ',')) {
        std::smatch d_match;
        if (std::regex_search(duration_str, d_match, duration_regex)) {
          size_t hours = stoi(d_match[1]);
          size_t minutes = d_match[2].matched ? stoi(d_match[2]) : 0;
          flight.connection_times += 60 * hours + minutes;
        }
      }
      flight.price = stoi(match[5]);
      pq.push(flight);
    }
  }
  file.close();
  return pq;
}
}  // namespace q3
#endif  // Q3_H
