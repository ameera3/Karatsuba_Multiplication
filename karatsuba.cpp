/*
 * Filename: karatsuba.cpp
 * Usage: ./karatsuba
 * Description: Implements Karatsuba Multiplication
 */

//#define USE_PROFINY
#include "InfInt.h"

#include <string>

using namespace std;

InfInt karatsuba(const string& num1String, InfInt num1, 
                 const string& num2String, InfInt num2) {

	// assume WLOG that the integer with smaller length
	// comes first	
	string StringNum1 = num1String;
	string StringNum2 = num2String;
	if( num1String.size() > num2String.size() ){
		StringNum1 = num2String;
		StringNum2 = num1String;
	}

	// cout << "StringNum1: " << StringNum1 << endl;
	// cout << "StringNum2: " << StringNum2 << endl;

	// under our assumption, the minimum of the 
	// two lengths is that of the first number
	int minLength = StringNum1.size();
	
	// length of first number halved
	int minMid = minLength/2;

	// under our assumption the maximum of the two
	// lengths is that of the second number
	int maxLength = StringNum2.size();

	// difference between length of second number 
	// and length of first number
	int diff = maxLength - minLength;
	
	// length of second number halved
	int maxMid = maxLength/2;	

	// we restrict ourselves to only multiplications
	// of single digit numbers.
	if( maxMid != 0 ){

		// If minMid != 0, write num1 = a * 10^(minLength - minMid) + b
		// If midMid = 0, write num1 = 0 * 10^(maxLength - maxMid) + b
		const string& aString 
			= minMid ? StringNum1.substr(0,minMid) : "0";
		// cout << "aString: " << aString << endl;
		InfInt a = InfInt(aString);	

		// If minMid != 0, write num2 = c * 10^(midLength - minMid) + d
		// If minMid = 0, write num2 = c * 10^(maxLength - maxMid) + d
		const string& cString = minMid ? 
			StringNum2.substr(0, diff + minMid) :
			StringNum2.substr(0, maxMid); 
		// cout << "cString: " << cString << endl;
		InfInt c = InfInt(cString);

		const string& bString 
			= minMid ? StringNum1.substr(minMid) : StringNum1;
		// cout << "bString: " << bString << endl;
		InfInt b = InfInt(bString);

		const string dString = minMid ? 
			StringNum2.substr(diff + minMid) : 
			StringNum2.substr(maxMid);
		// cout << "dString: " << dString << endl;
		InfInt d = InfInt(dString);		

		// To compute ad + bc, we need to compute (a+b)(c+d)
		InfInt aplusb = a+b;
		const string& aplusbString = aplusb.toString();
		// cout << "aplusbString: " << aplusbString << endl;
		
		InfInt cplusd = c+d;
		const string& cplusdString = cplusd.toString();
		// cout << "cplusdString: " << cplusdString << endl;

		// The brilliance of Karatsuba is three recursive
		// calls to compute ac, (a+b)(c+d), and bd
		InfInt z0 = karatsuba(aString, a, cString, c);
		InfInt z1 = karatsuba(aplusbString, aplusb, cplusdString, cplusd);
		InfInt z2 = karatsuba(bString, b, dString, d);
		
		// If num1 = a*10^m + b and num2 = c*10^m + d, we must
		// pad the product of a and c with 2m zeros
		int mid = minMid ? minLength - minMid : maxLength - maxMid;
		string z0String = z0.toString();
		string padz0 = "0";
		for (int i = 0; i < 2*mid - 1; ++i) {
			padz0 += "0";
		}
		const string& z0StringPad = z0String + padz0;
		// cout << "z0StringPad: " << z0StringPad << endl;
		InfInt z0Pad = InfInt(z0StringPad);

		// If num1 = a*10^m + b and num2 = c*10^m + d, we must
		// pad ad+bc with m zeroes.
		InfInt Middle = z1 - z0 - z2;
		string middleString = Middle.toString();
		string padz1 = "0";
		for(int j = 0; j < mid-1; ++j) {
			padz1 += "0";
		} 
		const string& middleStringPad = middleString + padz1;
		// cout << "middleStringPad: " << middleStringPad << endl;
		InfInt middlePad = InfInt(middleStringPad);

		// We sum the padded numbers with z2 to yield the product
		InfInt result = z0Pad + middlePad + z2;
		string resultString = result.toString();
		// cout << "result is: " << resultString << endl;

		return result; 
	}

	// we restrict ourselves to single digit multiplication
	else{ 
		// cout << num1String << " * " << num2String << endl;
		return num1 * num2; 
	}				
}

int main() {

	/* user entered number 1 */
	string stringNum1;

	/* user entered number 2 */
	string stringNum2;

	// scan in the first number and convert it to InfInt
	cout << "Enter the first of two positive numbers to multiply:" << endl;
        std::getline(std::cin, stringNum1);
        const string& myNum1String = stringNum1;
	InfInt num1 = InfInt(myNum1String);

	// scan in the second number and convert it to InfInt
        cout << "Enter the second of two positive numbers to multiply:" << endl;
	std::getline(std::cin, stringNum2);
	const string& myNum2String = stringNum2;
	InfInt num2 = InfInt(myNum2String);
	
	// compute the product using Karatsuba multiplication
	// and output it 
	InfInt result = karatsuba(myNum1String, num1, myNum2String, num2);
	cout << "The product is: " << result.toString() << endl; 
}        
	
	
