#include <unordered_map>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

std::unordered_map<double, double> factorials;
double success = 0.0;

double factorial(double input){
  if(input == 0){
    return 1;
  }
  if(factorials.find(input) == factorials.end()){
    double current = input;
    for(double i = input - 1; i > 0; i--){
      if(factorials.find(input) != factorials.end()){
        factorials[input] = current * factorials[i];
        return factorials[input];
      }
      current *= i;
    }
    factorials[input] = current;
    return factorials[input];
  }
  return factorials[input];
}

double power(double base, double exp){
  double result = 1.0;
  for(int i = 0; i < exp; i++){
    result *= base;
  }
  return result;
}
// n -> sub-set size , k -> set size
double combination(double n, double k){
  if(n > k){
    std::cout << "Invalid combination!" << std::endl;
  }
  return factorial(k) / (factorial(n) * factorial(k - n));
}
// n -> sucessful chances , k -> total chances
double binomial(double n, double k){
  return combination(n, k) * power(success, n) * power(1 - success, k - n);
}

void binomial_parsed(std::string filename){
  std::string filePath = "data/" + filename, line, ch;
  std::ifstream file(filePath);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filePath << std::endl;
    return;
  }
  double S = 0, F = 0;
  while(getline(file, line)){
    std::istringstream iss(line);
    while(getline(iss, ch, ',')){
      if(ch[0] == 'S' && ch[1] == '\0'){
        S++;
      }
      else if(ch[0] == 'F' && ch[1] == '\0'){
        F++;
      }
      else{
        std::cout << "Invalid file format!" << std::endl;
        return;
      }
    }
    success = S / (S + F);
  }
}
double binomial_interval(double n1, double n2, double k){
  if(n1 > n2){
    std::cout << "Invalid interval.\n";
  }
  double p = 0.0;
  for(; n1 <= n2; n1++){
    p += binomial(n1, k);
  }
  return p;
}
int main(){
  uint c;
  std::cout << "If you don't understand how to use this tool or what it is for go to the README.\n";
  while(c != 0){
    std::cout << "========== BinomialDistribuTool ==========\n";
    std::cout << "What do you want to do?\n";
    std::cout << "1. Outsource file with data for me to calculate the odds?\n";
    std::cout << "2. Provide me with the odds of success?\n";
    std::cout << "3. Give you a probability of a use-case (n out of k) using uintegers and the current state?\n";
    std::cout << "4. Same as 3 but with an interval of k?\n";
    std::cout << "0. Leave.\n";
    std::cout << "Enter option: ";
    std::cin >> c;
    if(c == 1){
      std::string path;
      std::cout << "The file needs to be inside data folder and in the format of a success/failure ('S'/'F') character, followed by a separator (','), followed by another character and so on.\n";
      std::cout << "Path File : ";
      std::cin >> path;
      binomial_parsed(path);
      std::cout << "The updated success rate is: " << success << '\n';
      continue;
    }
    if(c == 2){
      std::cout << "New odds: ";
      std::cin >> success;
      continue;
    }
    if(c == 3){
      double n, k;
      std::cout << "What is n? ";
      std::cin >> n;
      std::cout << "What is k? ";
      std::cin >> k;
      std::cout << "The probability of said n of k using the current odds is: " << binomial(n, k) << std::endl;
      continue;
    }
    if(c == 4){
      double n1, n2, k;
      std::cout << "What is lower bound of n? ";
      std::cin >> n1;
      std::cout << "What is upper bound of n? ";
      std::cin >> n2;
      std::cout << "What is k? ";
      std::cin >> k;
      std::cout << "The probability of said n interval of k using the current odds is: " << binomial_interval(n1, n2, k) << std::endl;
      continue;
    }
    if(c == 5){
      std::cout << "Current success chance is: " << success << std::endl;
    }
  }
  return 0;
}