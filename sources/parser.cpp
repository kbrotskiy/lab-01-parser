//
// Created by Кирилл Броцкий on 08.09.2020.
//

#include "parser.hpp"
#include <algorithm>

Parser::Parser() = default;
Parser::Parser(const std::string &path) {
  parser(path);
}

const std::vector<Student> &Parser::getStudents() const {
  return students;
}

const Lengths_of_fields &Parser::getL() const {
  return l;
}

void Parser::printLine(std::ostream &out, const Student &student) const {
  out << std::left << "|" << std::setw(l.length_1) << student.getName() << "|";
  if (std::any_cast<json>(student.getGroup()).is_number()) {
    out << std::setw(l.length_2) << std::any_cast<json>(student.getGroup()).get<int>();
  } else
      if (std::any_cast<json>(student.getGroup()).is_string()) {
    out << std::setw(l.length_2) << std::any_cast<json>(student.getGroup()).get<std::string>();
  } else {
    throw std::invalid_argument(
        "!The type of the Group variable is undefined!");
  }
  out << "|" << std::setprecision(3) << std::setw(l.length_3) << student.getAvg() << "|";
  if (std::any_cast<json>(student.getDebt()).is_null()) {
    out << std::setw(l.length_4) << "null";
  } else
      if (std::any_cast<json>(student.getDebt()).is_array()) {
    std::string it = std::to_string(std::any_cast<json>(student.getDebt()).get<std::vector<std::string>>().size()) +" items";
    out << std::setw(l.length_4) << it;
  } else
      if (std::any_cast<json>(student.getDebt()).is_string()) {
    out << std::setw(l.length_4) << std::any_cast<json>(student.getDebt()).get<std::string>();
  } else {
    throw std::invalid_argument(
        "!The type of the Debt variable is undefined!");
  }
  out << "|";
}

std::string Parser::getSeparator() const {
  std::string sep = "|";
  for (size_t i = 0; i < l.length_1; ++i) {
    sep += "-";
  }
  sep += "|";
  for (size_t i = 0; i < l.length_2; ++i) {
    sep += "-";
  }
  sep += "|";
  for (size_t i = 0; i < l.length_3; ++i) {
    sep += "-";
  }
  sep += "|";
  for (size_t i = 0; i < l.length_4; ++i) {
    sep += "-";
  }
  sep += "|";
  return sep;
}

void Parser::parser(const std::string &path) {
  if (path.empty()) {
    throw std::invalid_argument("!The file path cannot be empty!");
  }
  std::ifstream json_file(path);
  if (!json_file.is_open()) {
    throw std::out_of_range("!The file with the specified name: " + path + " does not exist!");
  }
  json data;
  json_file >> data;
  if (!data.at("items").is_array()) {
    throw std::invalid_argument("!Items is not array!");
  }
  if (data.at("items").size() != data.at("_meta").at("count").get<size_t>()) {
    throw std::out_of_range("!Items length don't equal _meta.count!");
  }
  for (auto const &student : data.at("items")) {
    students.emplace_back(student);
  }
  setLengths();
}

void Parser::printTable() {
  std::cout << *this;
}

bool Parser::emptyJSONobject() const {
  return students.empty();
}

void Parser::setJSONString(const std::string &JSON) {
  json data = json::parse(JSON);
  if (!data.at("items").is_array()) {
    throw std::invalid_argument("!Items is not array!");
  }
  if (data.at("items").size() != data.at("_meta").at("count").get<size_t>()) {
    throw std::invalid_argument("!Items length don't equal _meta.count!");
  }
  for (auto const &student : data.at("items")) {
    students.emplace_back(student);
  }
  setLengths();
}

void Parser::setLengths() {
  for (const auto &student : students) {
    if (student.getName().size() > l.length_1) {
      l.length_1 = student.getName().size() + 1;
    }
    if (std::any_cast<json>(student.getGroup()).is_number()) {
      if (std::to_string(std::any_cast<json>(student.getGroup()).get<int>()).size() > l.length_2) {
        l.length_2 = std::to_string(std::any_cast<json>(student.getGroup()).get<int>()).size() + 1;
      }
    } else {
      if (std::any_cast<json>(student.getGroup()).get<std::string>().size() > l.length_2) {
        l.length_2 = std::any_cast<json>(student.getGroup()).get<std::string>().size() + 1;
      }
    }
    if (std::any_cast<json>(student.getDebt()).is_string() &&
        std::any_cast<json>(student.getDebt()).get<std::string>().size() > l.length_4) {
      l.length_4 =std::any_cast<json>(student.getDebt()).get<std::string>().size() + 1;
    }
  }
}

std::ostream &operator<<(std::ostream &out, Parser &p) {
  out << std::left << "|" << std::setw(p.l.length_1) << "      Name"
      << "|" << std::setw(p.l.length_2) << " Group"
      << "|" << std::setw(p.l.length_3) << "  Avg"
      << "|" << std::setw(p.l.length_4) << "      Debt"
      << "|" << std::endl;
  std::string separator = p.getSeparator();
  out << separator << std::endl;
  for (const auto &student : p.students) {
    p.printLine(out, student);
    out << std::endl;
    out << separator << std::endl;
  }
  return out;
}

Parser::~Parser() = default;