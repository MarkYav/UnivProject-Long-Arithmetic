#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

/*struct LongNumber;
struct LongFunction;*/

/*void SumOfLongNumbers(LongNumber& LN1, LongNumber& LN2, LongNumber& Result) {
    Result.LengTop = 0;
    //LengTop = (LN1 > LN2) ? LN1 : LN2;.

    for (int i = Leng -1; i >= 0; i++){

    }
}*/

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
        ZipNumber();
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

    void ZipForvardPartOfNumber() {
        if (arrayOfTopNumbers[lengTop - 1] == 0 && lengTop - 1 - dot > 0) {
            arrayOfTopNumbers.erase(arrayOfTopNumbers.end() - 1);
            lengTop--;
            ZipForvardPartOfNumber();
        }

        /*if (arrayOfTopNumbers[0] == 0) {
            arrayOfTopNumbers.erase(arrayOfTopNumbers.begin());
            lengTop--;
            ZipForvardPartOfNumber();
        }*/
    }

    void ZipLastPartOfNumber() {
        if (arrayOfTopNumbers[0] == 0 && dot > 0) {
            arrayOfTopNumbers.erase(arrayOfTopNumbers.begin());
            lengTop--;
            dot--;
            ZipLastPartOfNumber();
        }

        /*if (dot > 0 && arrayOfTopNumbers[lengTop - 1] == 0) {
            arrayOfTopNumbers.erase(arrayOfTopNumbers.end() - 1);
            lengTop--;
            ZipLastPartOfNumber();
        }*/
    }

    void ZipNumber() {
        ZipForvardPartOfNumber();
        ZipLastPartOfNumber();
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

        result.ZipNumber();
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
            else if (i == Bigger.lengTop){
                Bigger.arrayOfTopNumbers.push_back(1);
                Bigger.lengTop++; //надо снова задать leng
            } else if (i == Bigger.lengTop){
                break;
            }
        }
        lengTop = Bigger.arrayOfTopNumbers.size();

        Bigger.ZipNumber();
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
        result.sing = sing * other.sing;
        result.dot = dot + other.dot;
        result.lengTop = 0;
        for (int i = 0; i < other.lengTop; i++){
            subArray[i].lengTop = 0;
            for (int p = 0; p < i; p++) {
                subArray[i].arrayOfTopNumbers.push_back(0);
                subArray[i].lengTop++;
            }
            int inherter = 0;
            for (int k = 0; k < lengTop; k++){
                if (arrayOfTopNumbers[k]*other.arrayOfTopNumbers[i] < 10) {
                    if (inherter > 0){
                        subArray[i].arrayOfTopNumbers.push_back(arrayOfTopNumbers[k] * other.arrayOfTopNumbers[i] + inherter);
                        inherter = 0;
                        }
                    else
                        subArray[i].arrayOfTopNumbers.push_back(arrayOfTopNumbers[k] * other.arrayOfTopNumbers[i]);
                    subArray[i].lengTop++;
                } else {
                    subArray[i].arrayOfTopNumbers.push_back(arrayOfTopNumbers[k] * other.arrayOfTopNumbers[i] % 10);
                    inherter = (arrayOfTopNumbers[k] * other.arrayOfTopNumbers[i]) / 10;
                    subArray[i].lengTop ++;
                }
            }
            if (inherter > 0) {
                subArray[i].arrayOfTopNumbers.push_back(inherter);
                subArray[i].lengTop += inherter;
                inherter = 0;
            }
            result = result + subArray[i];
        }
        result.lengTop = result.arrayOfTopNumbers.size();

        result.ZipNumber();
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
        LongNumber result;
        LongNumber other = o;
        result.lengTop = 0;
        result.sing = sing * other.sing;
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

        result.ZipNumber();
        return result;
    }

    LongNumber operator^ (const LongNumber &o) {
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

        result.ZipNumber();
        return result;
    }

    LongNumber operator% (const LongNumber &other) {
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

        ZipNumber();
    }

    // constructors
    LongNumber() {}

    LongNumber(string str) {
        SetNumber(str);
    }

};

struct LongFruction
{
    /*LongFruction(string str) {
        LongNumber TopPart(str);
    }*/

    LongNumber TopPart;
    int LengLow;
    vector < int > ArrayOfLowNumbers;
};

int main() {
    LongNumber firstNumber, secondNumber;
    string str1;
    string str2;
    int base;
    cin >> str1;
    cin >> str2;
    //cin >> base;
    firstNumber.SetNumber(str1);
    secondNumber.SetNumber(str2);
    firstNumber = firstNumber + secondNumber;
    //firstNumber = firstNumber - secondNumber;
    //firstNumber = firstNumber * secondNumber;
    //firstNumber = firstNumber / secondNumber;
    //firstNumber = firstNumber ^ secondNumber;
    //firstNumber = firstNumber % secondNumber;
    //firstNumber = firstNumber.ConvertToOtherBase(base);
    //firstNumber = firstNumber.ConvertFromBinarToDecimal();
    firstNumber.GetNumber();
}
