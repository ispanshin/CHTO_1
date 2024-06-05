#include <iostream>
#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <ctime>
#include <cassert>
#include <random>
#include <unordered_map>
#include <chrono>
#include <utility>
#include <numeric>
#include <bitset>
#include <unordered_set>
#include <queue>

using namespace std;

class BigInt {
private:
    vector<int> value_;
    size_t len() const {
        return value_.size();
    }

    void normalize(vector<int> &v) {
        int carry = 0;
        for (int i = 0; i < v.size(); ++i) {
            carry += v[i];
            v[i] = carry % 10;
            carry /= 10;
        }
        while (carry > 0) {
            v.push_back(carry % 10);
            carry /= 10;
        }
        while (v.size() > 1 && v.back() == 0) {
            v.pop_back();
        }
    }
public:
    BigInt(const vector<int> &value) : value_(std::move(value)) {}
    BigInt(const BigInt& other) {
        value_ = other.value_;
    }
    BigInt(string s) {
        reverse(s.begin(), s.end());
        size_t n = s.size();
        value_.resize(n);
        for (size_t i = 0; i < n; ++i) {
            value_[i] = s[i] - '0';
        }
    }
    BigInt operator*(const BigInt& other) {
        size_t n = other.len() + len();
        vector<int> res(n);
        for (size_t i = 0; i < other.len(); ++i) {
            for (size_t j = 0; j < len(); ++j) {
                res[i + j] += other.value_[i] * value_[j];
            }
        }

        normalize(res);
        return res;
    }
    BigInt& operator=(BigInt&& other)  noexcept {
        value_ = std::move(other.value_);
        return *this;
    }
    void Print()  {
        reverse(value_.begin(), value_.end());
        for (auto i : value_) {
            cout << i;
        }
        reverse(value_.begin(), value_.end());

        cout << '\n';
    }
};



int main(int argc, char *argv[]) {
    if (argc != 2) {
        throw std::invalid_argument("Too much arguments" + to_string(argc));
    }

    char *ptr;
    long long n = strtoll(argv[1], &ptr, 10);
    if (*ptr || n < 0) {
        throw std::invalid_argument("Wrong number format");
    }
    BigInt answer("1");
    for (int i = 2; i <= n; ++i) {
        answer = answer * BigInt(to_string(i));
    }
    answer.Print();
}
