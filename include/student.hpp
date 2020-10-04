//
// Created by Кирилл Броцкий on 08.09.2020.
//

#ifndef INCLUDE_STUDENT_HPP_
#define INCLUDE_STUDENT_HPP_

#include <any>
#include <exception>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;
class Student {

 public:
  explicit Student(const json &obj);
  Student();
  const std::string &getName() const;
  void setName(const json &name);
  const std::any &getGroup() const;
  void setGroup(const json &group);
  double getAvg() const;
  void setAvg(const json &avg);
  const std::any &getDebt() const;
  void setDebt(const json &debt);
  void from_json(const json &j);

 private:
  double Avg = 0;
  std::string Name;
  std::any Group;
  std::any Debt;
};

void from_json(const json &j, Student &s);

#endif  // INCLUDE_STUDENT_HPP_