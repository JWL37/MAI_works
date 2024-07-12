#include <iostream>
#include <vector>
#include <string>

std::vector<int> calculateZFunction(std::string &s) {
     int n = s.length();
    std::vector<int> Z(n);
    int left = 0, right = 0;

    for (int i = 1; i < n; ++i) {
        if (i<=right){
            Z[i]=std::min(right-i,Z[i-left]);
        }
        while (i+Z[i]<n && s[Z[i]]==s[i+Z[i]]){
            ++Z[i];
        }
        if (i+Z[i]>right){
            right=i+Z[i];
            left=i;
        }
    }
    return Z;
}


int main() {
    std::string text;
    std::string pattern;

    std::cin >> text>>pattern;

    std::string combined = pattern + '$' + text;
    std::vector<int> Z = calculateZFunction(combined);
    std::vector<int> result;
    int pattern_length = pattern.length();

    for (int i = 0; i < Z.size(); ++i) {
        if (Z[i] == pattern_length) {
            result.push_back(i - pattern_length - 1);
        }
    }

    for (int pos : result) {
        std::cout << pos << std::endl;
    }

    return 0;
}