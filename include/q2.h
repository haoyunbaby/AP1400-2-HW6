#ifndef Q2_H
#define Q2_H
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
namespace q2 {
struct Patient {
  std::string name;
  size_t age;
  size_t smokes;
  size_t area_q;
  size_t alkhol;
};
std::vector<Patient> read_file(std::string filename) {
  std::vector<Patient> ans;
  std::ifstream file(filename);
  std::string line;
  std::getline(file, line);
  std::getline(file, line);
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    Patient pat;
    std::string name, surname, field;
    std::getline(ss, name, ',');
    std::getline(ss, surname, ',');
    size_t pos = name.find_last_not_of(" \t\n\r\f\v");
    name = name.substr(0, pos + 1);
    pat.name = name + " " + surname;
    std::getline(ss, field, ',');
    pat.age = std::stoi(field);
    std::getline(ss, field, ',');
    pat.smokes = std::stoi(field);
    std::getline(ss, field, ',');
    pat.area_q = std::stoi(field);
    std::getline(ss, field, ',');
    pat.alkhol = std::stoi(field);
    ans.push_back(pat);
  }
  file.close();
  return ans;
}
void sort(std::vector<Patient> &patients) {
  std::sort(patients.begin(), patients.end(), [&](auto a, auto b) {
    int i = 3 * a.age + 5 * a.smokes + 2 * a.area_q + 4 * a.alkhol;
    int j = 3 * b.age + 5 * b.smokes + 2 * b.area_q + 4 * b.alkhol;
    return i > j;
  });
}
}  // namespace q2
#endif  // Q2_H
