#include <bits/stdc++.h>
#include "ValueAndSolveTask.h"

int main()
{
  std::string line;
  std::cout << "enter line"<<std::endl;
  std::getline(std::cin,line);
  std::string result=trySwapAtoBorBtoA(line);
  std::cout << "Результат работы программы: " << result << std::endl;
  return 0;
}