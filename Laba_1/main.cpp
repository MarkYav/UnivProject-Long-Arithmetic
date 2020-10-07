#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>
#include <stdlib.h>

using namespace std;

struct LongNumber
{
    int lengTop;
    int dot = 0;
    int sing = 1;
    int presice = 3;
    int base = 10;
    vector < int > arrayOfTopNumbers;

    // functions of LongNumber class
    void SetPartOfNumber(int leng, vector < int > &arrayOfNumbers, string str){
        int k = str.size() - leng;
        for (int i = str.size() - 1; i >= k; i--){
            if (str[i] != '.')
                arrayOfNumbers.push_back(str[i] - 48);
            else {
                lengTop--;
                dot = str.size() - 1 - i;
            }
        }
    }

    void SetNumber(string str){
        lengTop = str.size();
        switch (str[0]) {
            case '-':
                lengTop--;
                sing = -1;
                break;
            case '+':
                lengTop--;
                sing = 1;
                break;
        }
        SetPartOfNumber(lengTop, arrayOfTopNumbers, str);
        ZipNumber(arrayOfTopNumbers, lengTop);
    }

    bool IsHasNumbers(){
        for (int i = lengTop - 1; i >= 0; i--){
            if (arrayOfTopNumbers[i] != 0)
                return true;
        }
        return false;
    }

    void GetNumber(){
        if (!IsHasNumbers()) {
            cout << "0";
            return;
        }
        if (sing < 0)
            cout << "-";
        for (int i = lengTop - 1; i >= 0; i--){
            if (lengTop == dot && i == lengTop - 1)
                cout << "0.";
            if (arrayOfTopNumbers[i] < 10)
                cout << arrayOfTopNumbers[i];
            else
                switch (arrayOfTopNumbers[i]) {
                    case 10: cout << "A"; break;
                    case 11: cout << "B"; break;
                    case 12: cout << "C"; break;
                    case 13: cout << "D"; break;
                    case 14: cout << "E"; break;
                    case 15: cout << "F"; break;
                }
            if (i == dot && dot > 0)
                cout << '.';
        }
    }

    string GetStringNumber() {
        if (!IsHasNumbers()) {
            return "0";
        }
        string str;
        if (sing < 0)
            str = str + '-';
        for (int i = lengTop - 1; i >= 0; i--){
            if (lengTop == dot && i == lengTop - 1)
                str = str + '0' + '.';
            cout << arrayOfTopNumbers[i];
            if (i == dot && dot > 0)
                str = str + '.';
        }
        return str;
    }

    int FindMaxLeng(int leng1, int leng2){
        return (leng1 > leng2) ? leng1 : leng2;
    }

    void ChangeSing(){
        sing *= -1;
    }

    bool CompareNumber(const LongNumber &N1, const LongNumber &N2){ //return 1 if N1 >= N2, return 0 if N1 < N2
        if (N1.lengTop - N1.dot > N2.lengTop - N2.dot)
            return true;
        else if (N1.lengTop - N1.dot < N2.lengTop - N2.dot)
            return false;
        else {
            for (int i = N1.lengTop - 1; i >= 0; i--){
                if (N1.arrayOfTopNumbers[i] > N2.arrayOfTopNumbers[i])
                    return true;
                else if (N1.arrayOfTopNumbers[i] < N2.arrayOfTopNumbers[i])
                    return false;
            }
        }
        return true;
    }

    bool FindBiggerNumber(const LongNumber &other){     //return 1 if this >= other, return 0 if this < other
        /*if (sing > other.sing)
            return true;
        else if (sing < other.sing)
            return false;
        else {
            if (sing > 0){
                return CompareNumber(*this, other);
            } else {
                return CompareNumber(other, *this);
            }
        }*/

        if (sing > 0){
            return CompareNumber(*this, other);
        } else {
            return CompareNumber(other, *this);
        }
    }

    void MatchDots(LongNumber &B, LongNumber &S){
        if (B.dot < S.dot) {
            int num = S.dot - B.dot;
            for (int i = 0; i < num; i++) {
                B.arrayOfTopNumbers.emplace(B.arrayOfTopNumbers.begin(), 0);
                B.lengTop++;
                B.dot++;
            }
        }
        else if (B.dot > S.dot)
            MatchDots(S, B);
    }

    void ZipForvardPartOfNumber(vector < int > &arrayOfNumbers, int &leng) {
        if (arrayOfNumbers[leng - 1] == 0 && leng - 1 - dot > 0) {
            arrayOfNumbers.erase(arrayOfNumbers.end() - 1);
            leng--;
            ZipForvardPartOfNumber(arrayOfNumbers, leng);
        }

        /*if (arrayOfTopNumbers[0] == 0) {
            arrayOfTopNumbers.erase(arrayOfTopNumbers.begin());
            lengTop--;
            ZipForvardPartOfNumber();
        }*/
    }

    void ZipLastPartOfNumber(vector < int > &arrayOfNumbers, int &leng) {
        if (arrayOfNumbers[0] == 0 && dot > 0) {
            arrayOfNumbers.erase(arrayOfNumbers.begin());
            leng--;
            dot--;
            ZipLastPartOfNumber(arrayOfNumbers, leng);
        }

        /*if (dot > 0 && arrayOfTopNumbers[lengTop - 1] == 0) {
            arrayOfTopNumbers.erase(arrayOfTopNumbers.end() - 1);
            lengTop--;
            ZipLastPartOfNumber();
        }*/
    }

    void ZipNumber(vector < int > &arrayOfNumbers, int &leng) {
        ZipForvardPartOfNumber(arrayOfNumbers, leng);
        ZipLastPartOfNumber(arrayOfNumbers, leng);
    }

    LongNumber ConvertToOtherBase(int newBase) {
        LongNumber result;
        LongNumber numberBase(to_string(newBase));

        result.lengTop= 0;
        result.sing = sing;
        result.base = newBase;
        while (CompareNumber(*this, numberBase)) {
            LongNumber newThis;
            newThis = *this;
            newThis = newThis % numberBase;
            //TODO ко-ко-костылЪ
            //string str = newThis.GetStringNumber();
            //stringstream geek(str);
            //int i = stoi(newThis.GetStringNumber());
            int sum = 0;
            for (int i = 0; i < newThis.lengTop; i++){
                sum += newThis.arrayOfTopNumbers[i] * pow(10, i);
            }
            //geek >> i;
            result.arrayOfTopNumbers.push_back(sum);

            *this = *this ^ numberBase;
        }
        /*stringstream geek(this->GetStringNumber());
        int i = 0;
        geek >> i;
        result.arrayOfTopNumbers.push_back(i);*/
        int sum = 0;
        for (int i = 0; i < lengTop; i++){
            sum += arrayOfTopNumbers[i] * pow(10, i);
        }
        //geek >> i;
        result.arrayOfTopNumbers.push_back(sum);
        result.lengTop = result.arrayOfTopNumbers.size();

        //TODO костыль: не работает присвоение; сделал через return
        //*this = result;
        return result;
    }

    LongNumber ConvertFromBinarToDecimal() {
        LongNumber result;

        result.arrayOfTopNumbers.push_back(0);
        result.lengTop = 1;
        result.sing = sing;
        result.base = 10;

        for (double i = 0; i < this->lengTop; i++){
            double x = this->arrayOfTopNumbers[i] * pow(2, i);
            LongNumber midNumber(to_string(x));
            result = result + midNumber;
        }

        result.ZipNumber(result.arrayOfTopNumbers, result.lengTop);
        //*this = result;
        return result;
    }

    LongNumber SumOfTwo(const LongNumber &B, const LongNumber &S){
        LongNumber Bigger = B;
        LongNumber Smaller = S;
        MatchDots(Bigger, Smaller);
        int maxSize = FindMaxLeng(Bigger.lengTop, Smaller.lengTop);
        for (int i = 0; i < maxSize; i++){
            if ( i < Bigger.lengTop && i < Smaller.lengTop){
                if (Bigger.sing == Smaller.sing) {
                    Bigger.arrayOfTopNumbers[i] += Smaller.arrayOfTopNumbers[i];
                    if (Bigger.arrayOfTopNumbers[i] > 9) {
                        Bigger.arrayOfTopNumbers[i] -= 10;
                        if (i < Bigger.lengTop - 1)
                            Bigger.arrayOfTopNumbers[i + 1]++;
                        else {
                            Bigger.arrayOfTopNumbers.push_back(1);
                            Bigger.lengTop++;
                            maxSize = FindMaxLeng(Bigger.lengTop, Smaller.lengTop);
                        }
                    }
                } else {
                    Bigger.arrayOfTopNumbers[i] -= Smaller.arrayOfTopNumbers[i];
                    if (Bigger.arrayOfTopNumbers[i] < 0) {
                        Bigger.arrayOfTopNumbers[i] += 10;
                        if (i < Bigger.lengTop - 1)
                            Bigger.arrayOfTopNumbers[i + 1]--;
                        else {
                            Bigger.arrayOfTopNumbers.push_back(1);
                            Bigger.lengTop++;
                            ChangeSing();
                            maxSize = FindMaxLeng(Bigger.lengTop, Smaller.lengTop);
                        }
                    }
                }
            }
            else if (i >= Bigger.lengTop){
                Bigger.arrayOfTopNumbers.push_back(1);
                Bigger.lengTop++; //надо снова задать leng
            } else if (i >= Smaller.lengTop){
                if (Bigger.arrayOfTopNumbers[i] >= 10){
                    Bigger.arrayOfTopNumbers[i] -= 10;
                    if (i + 1 < Bigger.lengTop){
                        Bigger.arrayOfTopNumbers[i+1]++;
                    }
                    else {
                        Bigger.arrayOfTopNumbers.push_back(1);
                        Bigger.lengTop++;
                    }
                }
            }
        }
        lengTop = Bigger.arrayOfTopNumbers.size();

        Bigger.ZipNumber(Bigger.arrayOfTopNumbers, Bigger.lengTop);
        return Bigger;
    }

    LongNumber operator+ (const LongNumber &other) {
        if (FindBiggerNumber(other)){
            return SumOfTwo(*this, other);
        } else {
            return SumOfTwo(other, *this);
        }
    }

    //TODO почему-то не работает; сделал костыль через следующюю ф-ю
    /*LongNumber operator* (const int &other) {
        for (int i = 0; i < other; i++){
            arrayOfTopNumbers.emplace(arrayOfTopNumbers.begin(), 0);
            lengTop++;
        }

        /*for (int i = lengTop - 1; i >= 0; i--)
            arrayOfTopNumbers[i] *= other;
        return*/
    /*}*/

    void MunliplyOnNumber(LongNumber &longN, const int &number){
        for (int i = 0; i < number; i++){
            longN.arrayOfTopNumbers.emplace(longN.arrayOfTopNumbers.begin(), 0);
            longN.lengTop++;
        }
    }

    LongNumber operator* (const LongNumber &other) {
        LongNumber subArray[other.lengTop];
        LongNumber result;

        int n = dot + other.dot;

        result.lengTop = 1;
        result.arrayOfTopNumbers.push_back(0);
        for (int i = 0; i < other.lengTop; i++){
            subArray[i].lengTop = 0;
            for (int p = 0; p < i; p++) {
                subArray[i].arrayOfTopNumbers.push_back(0);
                subArray[i].lengTop++;
            }
            int inherter = 0;
            for (int k = 0; k < lengTop; k++){
                if (arrayOfTopNumbers[k]*other.arrayOfTopNumbers[i] + inherter < 10) {
                    if (inherter > 0){
                        subArray[i].arrayOfTopNumbers.push_back(arrayOfTopNumbers[k] * other.arrayOfTopNumbers[i] + inherter);
                        inherter = 0;
                        }
                    else
                        subArray[i].arrayOfTopNumbers.push_back(arrayOfTopNumbers[k] * other.arrayOfTopNumbers[i]);
                    subArray[i].lengTop++;
                } else {
                    int m = (arrayOfTopNumbers[k] * other.arrayOfTopNumbers[i] + inherter) % 10;
                    subArray[i].arrayOfTopNumbers.push_back(m);
                    //inherter = 0;
                    inherter = (arrayOfTopNumbers[k] * other.arrayOfTopNumbers[i] + inherter) / 10;
                    subArray[i].lengTop ++;
                }
            }
            if (inherter > 0) {
                subArray[i].arrayOfTopNumbers.push_back(inherter);
                subArray[i].lengTop += 1;
                inherter = 0;
            }
            result = result + subArray[i];
        }
        result.lengTop = result.arrayOfTopNumbers.size();

        result.dot = n;
        result.sing = sing * other.sing;
        result.ZipNumber(result.arrayOfTopNumbers, result.lengTop);
        return result;
    }

    LongNumber operator- (const LongNumber &other) {
        LongNumber copyOfOther = other;
        copyOfOther.ChangeSing();
        if (FindBiggerNumber(other)){
            return SumOfTwo(*this, copyOfOther);
        } else {
            return SumOfTwo(copyOfOther, *this);
        }
    }

    LongNumber operator/ (const LongNumber &o) {
        int s = sing * o.sing;
        this->sing = 1;

        if (o.lengTop == 1 && o.arrayOfTopNumbers[0] == 0){
            cout << "wrong input" << endl;
            exit(0);
        }
        if (this->lengTop == 1 && this->arrayOfTopNumbers[0] == 0){
            cout << '0' << endl;
            exit(0);
        }
        LongNumber result;
        LongNumber other = o;
        result.lengTop = 0;

        result.sing = 1;
        other.sing = 1;

        result.dot = 3;

        MatchDots(*this, other);
        dot = 0;
        other.dot = 0;
        /*for (int i = 0; i < presice; i++){
            arrayOfTopNumbers.emplace(arrayOfTopNumbers.begin(), 0);
            lengTop++;
        }*/
        //TODO не работает. Сделал костыль
        //this = this * presice;
        MunliplyOnNumber(*this, presice);

        for (int i = lengTop - other.lengTop; i >= 0; i--){
            int num = 0;
            LongNumber copyOfOther = other;
            MunliplyOnNumber(copyOfOther, i);
            while (CompareNumber(*this, copyOfOther) /*|| (lengTop != 1 && arrayOfTopNumbers[0] != 0)*/){
                //TODO не работает вычитание. использую костыль
                *this = *this - copyOfOther;
                num++;
            }
            result.arrayOfTopNumbers.push_back(num);
            result.lengTop++;
        }
        reverse(result.arrayOfTopNumbers.begin(), result.arrayOfTopNumbers.end());

        result.sing = s;
        result.ZipNumber(result.arrayOfTopNumbers, result.lengTop);
        return result;
    }

    LongNumber operator^ (const LongNumber &o) {
        if (o.lengTop == 1 && o.arrayOfTopNumbers[0] == 0){
            cout << "wrong input" << endl;
            return *this;
        }
        if (this->sing < 0 || o.sing < 0){
            cout << "wrong input" << endl;
            return *this;
        }
        LongNumber result;
        LongNumber other = o;
        result.lengTop = 0;
        result.sing = sing * other.sing;
        result.dot = 0;

        MatchDots(*this, other);
        dot = 0;
        other.dot = 0;

        for (int i = lengTop - other.lengTop; i >= 0; i--){
            int num = 0;
            LongNumber copyOfOther = other;
            MunliplyOnNumber(copyOfOther, i);
            while (CompareNumber(*this, copyOfOther) /*|| (lengTop != 1 && arrayOfTopNumbers[0] != 0)*/){
                //TODO не работает вычитание. использую костыль
                *this = *this - copyOfOther;
                num++;
            }
            result.arrayOfTopNumbers.push_back(num);
            result.lengTop++;
        }
        reverse(result.arrayOfTopNumbers.begin(), result.arrayOfTopNumbers.end());

        result.ZipNumber(result.arrayOfTopNumbers, result.lengTop);
        return result;
    }

    LongNumber operator% (const LongNumber &other) {
        if (other.lengTop == 1 && other.arrayOfTopNumbers[0] == 0){
            cout << "wrong input" << endl;
            return *this;
        }
        if (this->sing < 0 || other.sing < 0){
            cout << "wrong input" << endl;
            return *this;
        }
        LongNumber th1, th2;
        th1 = *this;
        th2 = *this;
        LongNumber R1 = th1;
        LongNumber R2 = (th2 ^ other);
        R2 = R2 * other;
        R1 = R1 - R2;
        //R1 = R1 * other;
        return R1;
    }

    void operator= (const LongNumber &other) {
        this->lengTop = other.lengTop;
        this->sing = other.sing;
        this->dot = other.dot;
        this->presice = other.presice;
        this->base = other.base;

        this->arrayOfTopNumbers.clear();

        for (int i = 0; i < this->lengTop; i++){
            arrayOfTopNumbers.push_back(other.arrayOfTopNumbers[i]);
        }

        ZipNumber(arrayOfTopNumbers, lengTop);
    }

    // constructors
    LongNumber() {}

    LongNumber(string str) {
        SetNumber(str);
    }

};

struct LongFruction : LongNumber
{
    int lengLow;
    vector < int > arrayOfLowNumbers;

    // functions of LongFruction class
    void IncreaseDot() {
        while (dot < 0) {
            arrayOfTopNumbers.emplace(arrayOfTopNumbers.begin(), 0);
            lengTop++;
            dot++;
        }
    }

    /*void ZipLastPartOfLowNumber(vector < int > &arrayOfNumbers, int &leng) {
        if (arrayOfNumbers[0] == 0 && dot > 0) {
            arrayOfNumbers.erase(arrayOfNumbers.begin());
            leng--;
            dot++;
            ZipLastPartOfLowNumber(arrayOfNumbers, leng);
        }
    }

    void ZipLowNumber(vector < int > &arrayOfNumbers, int &leng) {
        ZipForvardPartOfNumber(arrayOfNumbers, leng);
        ZipLastPartOfLowNumber(arrayOfNumbers, leng);
    }*/

    void SetLowPartOfNumber(int leng, vector < int > &arrayOfNumbers, string str){
        int k = str.size() - leng;
        for (int i = str.size() - 1; i >= k; i--){
            if (str[i] != '.')
                arrayOfNumbers.push_back(str[i] - 48);
            else {
                lengLow--;
                dot -= str.size() - 1 - i;
            }
        }
        IncreaseDot();
    }

    void SetLowNumber(string str){
        lengLow = str.size();
        SetLowPartOfNumber(lengLow, arrayOfLowNumbers, str);
        if (lengLow == 1 && arrayOfLowNumbers[0] == 0){
            cout << "wrong input";
            exit(0);
        }
        ZipForvardPartOfNumber(arrayOfLowNumbers, lengLow);
    }

    void SetFruction(string str1, string str2) {
        SetNumber(str1);
        SetLowNumber(str2);
    }

    LongNumber FindNSD(LongNumber A1, LongNumber A2){
        if (CompareNumber(A1, A2) && CompareNumber(A2, A1))
            return A1;
        else if (CompareNumber(A1, A2)) {
            A1 = A1 - A2;
            return FindNSD(A1, A2);
        } else {
            A2 = A2 - A1;
            return FindNSD(A1, A2);
        }
    }

    /*LongNumber FindNSK(LongNumber A1, LongNumber A2) {
        LongNumber NSD = FindNSD(A1, A2);
        return (A1 * A2) / NSD;
    }*/

    void MakeShorter() {
        int n = sing;
        this->sing = 1;
        LongFruction th = *this;
        LongNumber top = th;
        th.SwapFruction();
        LongNumber low = th;
        top.sing = 1;
        low.sing = 1;
        LongNumber NSD = FindNSD(top, low);
        top = top / NSD;
        low = low / NSD;
        *this = top;
        *this ^= low;
        this->sing = n;

    }

    void OutputNumber() {
        for (int i = lengLow - 1; i >= 0; i--){
            if (arrayOfLowNumbers[i] < 10)
                cout << arrayOfLowNumbers[i];
            else
                switch (arrayOfLowNumbers[i]) {
                    case 10: cout << "A"; break;
                    case 11: cout << "B"; break;
                    case 12: cout << "C"; break;
                    case 13: cout << "D"; break;
                    case 14: cout << "E"; break;
                    case 15: cout << "F"; break;
                }
        }
    }

    void GetFruction() {
        LongFruction A1 = *this, A2 = *this;
        A2.SwapFruction();
        A1 = A1 - A2;
        if (A1.lengTop == 1 && A1.arrayOfTopNumbers[0] == 0){
            cout << '1';
            return;
        }

        LongFruction copy = *this;
        LongNumber top = copy;
        copy.SwapFruction();
        LongNumber low = copy;

        top.sing = 1;
        low.sing = 1;
        LongNumber core = top ^ low;
        core.sing = sing;

        copy = *this;
        top = copy;
        copy.SwapFruction();
        low = copy;

        top.sing = 1;
        low.sing = 1;
        LongNumber add = top % low;
        add.sing = sing;

        if (!(core.lengTop == 1 && core.arrayOfTopNumbers[0] == 0)) {
            core.GetNumber();
            cout << " ";
        }

        if (add.IsHasNumbers()) {
            add.GetNumber();
            cout << "/";
            OutputNumber();
        }

        /*
        GetNumber();
        if (IsHasNumbers()) {
            cout << "|||";
            OutputNumber();
        }*/
    }

    void SwapFruction() {
        LongFruction n = *this;
        this->arrayOfTopNumbers.clear();
        this->arrayOfLowNumbers.clear();
        for (int i = 0; i < n.lengTop; i++){
            arrayOfLowNumbers.push_back(n.arrayOfTopNumbers[i]);
        }
        for (int i = 0; i < n.lengLow; i++){
            arrayOfTopNumbers.push_back(n.arrayOfLowNumbers[i]);
        }
        this->lengTop = n.lengLow;
        this->lengLow = n.lengTop;
    }

    void ToSameBotton(LongFruction f1, LongFruction f2) {
        LongFruction f1Copy = f1;
        LongFruction f2Copy = f2;
        f1Copy.SwapFruction();
        f2Copy.SwapFruction();
        LongNumber f1C = f1Copy;
        LongNumber f2C = f2Copy;
        f1 = f1 * f2C;
        f2 = f2 * f1C;
    }

    LongFruction operator* (const LongFruction &o) {
        LongFruction th = *this;
        LongFruction other = o;
        th.SwapFruction();
        other.SwapFruction();

        LongFruction result = *this;

        LongNumber thTop = *this;
        LongNumber otherTop = o;
        thTop = thTop * otherTop;
        result = thTop;

        LongNumber thLow = th;
        LongNumber otherLow = other;
        thLow = thLow * otherLow;
        result ^= thLow;

        return result;
    }

    LongFruction operator* (const LongNumber &o) {
        LongFruction th = *this;
        LongNumber otherTop = o;
        th.SwapFruction();

        LongFruction result = *this;

        LongNumber thTop = *this;
        thTop = thTop * otherTop;
        result = thTop;

        LongNumber thLow = th;
        thLow = thLow * otherTop;
        result ^= thLow;

        return result;
    }

    LongFruction operator/ (const LongFruction &o) {
        if (o.lengTop == 1 && o.arrayOfTopNumbers[0] == 0){
            cout << "attemp to divide on zero";
            exit(0);
        }
        LongFruction th = *this;
        LongFruction other = o;
        th.SwapFruction();
        other.SwapFruction();

        LongFruction result = *this;

        LongNumber thTop = *this;
        LongNumber otherTop = other;
        thTop = thTop * otherTop;
        result = thTop;

        LongNumber thLow = th;
        LongNumber otherLow = o;
        thLow = thLow * otherLow;
        result ^= thLow;

        return result;
    }

    LongFruction operator+ (const LongFruction &o) {
        LongFruction other = o;
        LongFruction th= *this;
        ToSameBotton(th, other);

        LongNumber th1 = th;
        LongNumber other1 = other;
        th1 = th1 + other1;

        LongFruction result = th;
        result = th1;

        return result;
    }

    LongFruction operator- (const LongFruction &o) {
        LongFruction other = o;
        other.sing *= -1;
        return *this + other;
    }

    void operator= (const LongFruction &other) {
        this->lengTop = other.lengTop;
        this->sing = other.sing;
        this->dot = other.dot;
        this->presice = other.presice;
        this->base = other.base;

        this->lengLow = other.lengLow;

        this->arrayOfTopNumbers.clear();

        for (int i = 0; i < this->lengTop; i++){
            arrayOfTopNumbers.push_back(other.arrayOfTopNumbers[i]);
        }

        this->arrayOfLowNumbers.clear();

        for (int i = 0; i < this->lengLow; i++){
            arrayOfLowNumbers.push_back(other.arrayOfLowNumbers[i]);
        }

        //ZipNumber(arrayOfTopNumbers, lengTop);
    }

    void operator= (const LongNumber &other) {
        this->lengTop = other.lengTop;
        this->sing = other.sing;
        this->dot = other.dot;
        this->presice = other.presice;
        this->base = other.base;

        this->arrayOfTopNumbers.clear();

        for (int i = 0; i < this->lengTop; i++){
            arrayOfTopNumbers.push_back(other.arrayOfTopNumbers[i]);
        }

        //ZipNumber(arrayOfTopNumbers, lengTop);
    }

    void operator^= (const LongNumber &other) {
        this->lengLow = other.lengTop;

        this->arrayOfLowNumbers.clear();

        for (int i = 0; i < this->lengLow; i++) {
            arrayOfLowNumbers.push_back(other.arrayOfTopNumbers[i]);
        }
    }

    //constructors
    LongFruction(string str1, string str2) {
        SetNumber(str1);
        SetLowNumber(str2);
    }

    LongFruction() {}
};

int main() {
    LongNumber firstNumber, secondNumber;
    string str1, str2, str3, str4;

    char in;
    cin >> in;

    cin >> str1 >> str2;
    firstNumber.SetNumber(str1);
    secondNumber.SetNumber(str2);
    switch (in) {
        case '+': firstNumber = firstNumber + secondNumber; break;
        case '-': firstNumber = firstNumber - secondNumber; break;
        case '*': firstNumber = firstNumber * secondNumber; break;
        case '/': firstNumber = firstNumber / secondNumber; break;
        case '%': firstNumber = firstNumber % secondNumber; break;
        case 'c': int base; cin >> base;
                  firstNumber = firstNumber.ConvertToOtherBase(base); break;
        case 'b': firstNumber = firstNumber.ConvertFromBinarToDecimal(); break;
    }
    firstNumber.GetNumber();

    /*
    cin >> str1 >> str2 >> str3 >> str4;
    LongFruction firstFruction(str1, str2);
    LongFruction secondFruction(str3, str4);
    switch (in) {
        case '+': firstFruction = firstFruction + secondFruction; break;
        case '-': firstFruction = firstFruction - secondFruction;; break;
        case '*': firstFruction = firstFruction * secondFruction; break;
        case '/': firstFruction = firstFruction / secondFruction; break;
    }
    firstNumber.GetNumber();
    firstFruction.MakeShorter();
    firstFruction.GetFruction();
     */
}
