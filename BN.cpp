#include <iostream>
#include <vector>
#include <math.h>



using namespace std;


class Big_Number {
private:
    vector<int> array;
public:
    enum { BASE = 2147483647};
    Big_Number(const string S = "");
    Big_Number(int n = 0);
    Big_Number(const Big_Number&);  
    Big_Number& operator+=(const Big_Number&);
    Big_Number operator*(const Big_Number&);
    Big_Number operator/(const Big_Number&);  // сделать 
    Big_Number& operator-=(const Big_Number&);
    friend ostream& operator<<(ostream&, const Big_Number&); //  сделать такой для 10 и 16 - ричного вывода 
    friend istream& operator>>(istream&,  Big_Number&); // сделать для 16 - ричного ввода
    bool operator==(const Big_Number&);
};


bool Big_Number:: operator==(const Big_Number& num) 
{
    if (array.empty()) {
        if (num.array.empty() || (num.array.size() == 0 && num.array[0] == 0)) return true;
        return false;
    }

    if (num.array.empty()) {
        if (array.empty() || (array.size() == 0 && array[0] == 0)) return true;
        return false;
    }

    if (num.array.size() != array.size()) return false;
    else 
    {
        for (int i = 0; i < array.size(); i++) 
        {
            if (array[i] != num.array[i]) return false;
        }
    }

    return true;

}


Big_Number& Big_Number:: operator+=(const Big_Number& num) {
    Big_Number result(0);

    int current = 0;

    for (int i = 0; i < max(array.size(), num.array.size()) || current != 0; i++)
    {
        if (i == array.size()) array.push_back(0);
        array[i] = array[i] + current + (i < num.array.size() ? num.array[i] : 0);
        current = (array[i] + num.array[i] + current) / BASE;
    }

    return (*this);

}

Big_Number::Big_Number(int n)
{
    for (int i = 0; i < n; i++)
    {
        array.push_back(0);
    }

}


Big_Number Big_Number:: operator*(const Big_Number& num)
{
    Big_Number result(array.size() + num.array.size() - 1);
    int current = 0;

    for (int i = 0; i < num.array.size() || current != 0; i++)
    {

        for (int j = 0; j < array.size() || current != 0; j++)
        {
            if (i != array.size())
            {
                long long cur = result.array[i + j] + (array[j] * 1LL * (i < num.array.size() ? num.array[i] : 0)) + current;
                result.array[i + j] = static_cast<int>(cur % BASE);
                current = static_cast<int>(cur / BASE);
            }
        }
    }
    return result;
}


Big_Number::Big_Number(const Big_Number& num)
{
    array.resize(num.array.size());
    for (int i = 0; i < array.size(); i++) array[i] = num.array[i];
}

istream& operator>>(istream& in, Big_Number& num) {
    string S;
    in >> S;
    Big_Number k(S);
    num = S;
    return in;

}

Big_Number& Big_Number:: operator-=(const Big_Number& num) {

    int current = 0;

    for (int i = 0; i < max(array.size(), num.array.size()) || current != 0; i++) {

        if (i == array.size()) array.push_back(0);
        array[i] = array[i] - (current + (i < num.array.size() ? num.array[i] : 0));

        current = array[i] < 0;
        if (current != 0) array[i] += BASE;
    }
    return (*this);
}



Big_Number::Big_Number(const string S) {
    if (S.size() != 0) {
        for (int i = S.size() - 1; i >= 0; i -= 9) {
            int k = 1;
            int result = 0;
            for (int j = i; j >= i - 8 && j >= 0; j--) {
                result += (S[j] - '0') * k;
                k *= 10;
            }
            array.push_back(result);
        }
    }
}


ostream& operator<<(ostream& out, const Big_Number& N) {
    for (int i = N.array.size() - 1; i >= 0; i--) {
        out << N.array[i];
    }
    return out;
}


int main()
{
    Big_Number n("1000");
    Big_Number k("10");
    Big_Number num("10000");
    cout << (num  == k * n ? "da" : "net");
    return 0;
}
