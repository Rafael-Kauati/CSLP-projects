#include <bitset>
#include "GolombEncoder.hpp"

using namespace std;

GolombEncoder::GolombEncoder(int param) : m(param)
{
    if (m <= 0)
    {
        cerr << "Error: The golomb parameter m should be positive";
    }
}

/**
 * @brief Encodes an integer using the Golomb encoding algorithm.
 *
 * This method takes an integer as input and encodes it using the Golomb encoding algorithm.
 *
 * @param num The integer to be encoded.
 * @return A vector of boolean values representing the encoded bits.
 */
vector<int> GolombEncoder::encode(int num)
{
    int quotient = num / m;
    int remainder = num % m;

    vector<int> encodedQuotient = unaryCode(quotient);
    vector<int> encodedRemainder;

    int k = static_cast<int>(ceil(log2(m)));
    // Array to store binary number
    vector<int> binaryNum;

    // Counter for binary array
    int i = 0;
    while (remainder > 0) {
        binaryNum.push_back(remainder % 2);
        remainder = remainder / 2;
        i++;
    }

    //for (int j = i - 1; j >= 0; j--)
    //    cout << binaryNum[j];
    encodedRemainder = binaryNum;

    vector<int> encodedNumber = encodedQuotient;

    encodedNumber.insert(encodedNumber.end(), encodedRemainder.begin(), encodedRemainder.end());

    return encodedNumber;
}

/**
 * @brief Generates the unary code representation of a non-negative integer.
 *
 * This method takes a non-negative integer as input and generates its unary code representation.
 *
 * @param num The non-negative integer to be encoded.
 * @return A vector of boolean values representing the unary code.
 */
vector<int> GolombEncoder::unaryCode(int num)
{
    vector<int> code;

    for (int i = 0; i < num; ++i)
    {
        code.push_back(1);
    }

    code.push_back(0); // Adicionar um 0 no final
    cout << " Quotient unary " <<  std::endl;
    for (int i : code)
    {
        cout << i;
    }
    cout <<  std::endl;


    return code;
}
