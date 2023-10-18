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
vector<bool> GolombEncoder::encode(int num)
{
    int quotient = num / m;
    int remainder = num % m;

    vector<bool> encodedQuotient = unaryCode(quotient);
    vector<bool> encodedRemainder;

    int k = static_cast<int>(ceil(log2(m)));

    for (int i = k - 1; i >= 0; --i)
    {
        encodedRemainder.push_back((remainder >> i) & 1);
    }

    vector<bool> encodedNumber = encodedQuotient;

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
vector<bool> GolombEncoder::unaryCode(int num)
{
    vector<bool> code;

    for (int i = 0; i < num; ++i)
    {
        code.push_back(1);
    }

    code.push_back(0); // Adicionar um 0 no final

    return code;
}
