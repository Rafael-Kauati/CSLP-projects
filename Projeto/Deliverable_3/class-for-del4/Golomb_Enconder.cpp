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

    cout << "Remainder : "<< remainder<<"\n";

    vector<int> encodedQuotient = unaryCode(quotient);
    vector<int> encodedRemainder;

    int b = static_cast<int>(floor(log2(m))); // Calculate b as floor(log2(m))

    if (remainder < (1 << (b + 1)) - m)
    {
        // If remainder < 2^(b+1) - m, code remainder using b bits
        for (int i = b - 1; i >= 0; --i)
        {
            encodedRemainder.push_back((remainder >> i) & 1);
        }
    }
    else
    {
        // If remainder >= 2^(b+1) - m, code remainder using b+1 bits
        for (int i = b; i >= 0; --i)
        {
            encodedRemainder.push_back((remainder >> i) & 1);
        }
    }


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
