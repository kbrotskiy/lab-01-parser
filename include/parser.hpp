//
// Created by Кирилл Броцкий on 08.09.2020.
//

#ifndef INCLUDE_PARSER_HPP_
#define INCLUDE_PARSER_HPP_

#include "student.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

struct Lengths_of_fields {
  size_t length_1;
  size_t length_2;
  size_t length_3;
  size_t length_4;
};

class Parser {

 public:
  Parser();
  explicit Parser(const std::string &path);
  ~Parser();
  const std::vector<Student> &getStudents() const;
  const Lengths_of_fields &getL() const;
  void printLine(std::ostream& out, const Student &student) const;
  std::string getSeparator() const;
  void parser(const std::string &path);
  void printTable();
  bool emptyJSONobject() const;
  void setJSONString(const std::string &JSON);
  friend std::ostream& operator <<(std::ostream& out, Parser& p);

 private:
  std::vector<Student> students;
  Lengths_of_fields l{15, 8, 6, 15};
  void setLengths();
};

#endif  // INCLUDE_PARSER_HPP_