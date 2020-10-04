//
// Created by Кирилл Броцкий on 08.09.2020.
//

#include "parser.hpp"

int main(){
  Parser parser("../tests/students.json");
  parser.printTable();
  return 0;
}