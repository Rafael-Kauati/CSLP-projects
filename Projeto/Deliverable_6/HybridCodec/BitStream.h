#ifndef BitStream_HPP
#define BitStream_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * @class BitStream
 * @brief Class for handling bit-level operations on files
 *
 * This class provides methods for reading and writing bits, chars, and strings from/to binary files.
 * It uses a buffer to store bits before writing them to the output file.
 */
class BitStream
{
    //  Private variables
private:
    ifstream inputFile;   ///< Input file stream
    ofstream outputFile;  ///< Output file stream
    int bitBuffer[8];     ///< Buffer to store bits before writing them to the output file
    int bufferLen;        ///< Current length of the buffer
    int currentReadBit;   ///< Current read bit index
    char currentReadChar; ///< Current char being read
    bool FILE_END;

    //  Public methods
public:
    static BitStream makeFromFiles(const string inFile, const string outFile)
    {
        BitStream stream(inFile, outFile);
        return stream;
    }
    /**
     * @brief Constructor for BitStream
     *
     * Opens the input and output files and initializes the buffer length to 0.
     *
     * @param inFile Path to the input file
     * @param outFile Path to the output file
     */

    BitStream(string inFile, string outFile)
    {
        bufferLen = 0;
        currentReadBit = 0;
        currentReadChar = '\0';
        inputFile = ifstream(inFile, ios::binary | ios::in);
        outputFile = ofstream(outFile, ios::binary | ios::out);
        FILE_END = false;
    }

    bool fileEnd() {
        return this->FILE_END;
    }

    /**
     * @brief Reads one bit from the input file
     *
     * @return The bit at the given position
     */
    int readOneFileBit()
    {
        //  Calculate bit position in the current char
        int currBitInByte = currentReadBit % 8;


        //  If the current bit is 0, advence to the next byte
        if (currBitInByte == 0) {
            if (inputFile.peek() == EOF) {
                this->FILE_END = true;
                return 0;
            }

            inputFile.get(currentReadChar);
        }

        //  Get the intended bit
        int tmp = ((currentReadChar >> (7 - currBitInByte)) & 1);

        //  Advance the current read bit index
        currentReadBit++;

        return tmp;
    }

    /**
     * @brief Reads N bits from the input file
     *
     * @param numBits Number of bits to read
     * @return A vector of the read bits
     */
    vector<int> readNFileBit(int numBits)
    {
        vector<int> bitVector;

        //  Call readOneFileBit N times and append the outputs to a vector
        for (int bitPosition = 0; bitPosition < numBits; bitPosition++)
        {
            bitVector.push_back(readOneFileBit());
        }

        return bitVector;
    }

    /**
     * @brief Reads 8 bits from the input file and assembles them as a char
     *
     * @return The assembled char
     */
    char readFileChar()
    {
        //  Get the initial bit vector
        vector<int> charBits = readNFileBit(8);
        char finalChar = '\0';

        //  Add the bits and shift them to the char
        for (int bitIndex = 7; bitIndex >= 0; bitIndex--)
        {
            finalChar |= charBits[7 - bitIndex] << (bitIndex);
        }

        return finalChar;
    }

    /**
     * @brief Reads N chars from the input file and assembles them as a string
     *
     * @param numChars Number of chars to read
     * @return The assembled string
     */
    string readFileString(int numChars)
    {
        string output = "";

        //  Call readFileChar N times and assemble the returned values inside a string
        for (int charIndex = 0; charIndex < numChars; charIndex++)
        {
            output += readFileChar();
        }

        return output;
    }

    /**
     * @brief Writes one bit to the output file
     *
     * If the buffer becomes full, it is flushed to the output file.
     *
     * @param newBit The bit to write
     */
    void writeOneFileBit(int newBit)
    {

        //  First fill the buffer
        if (bufferLen < 7)
        {
            bitBuffer[bufferLen] = newBit;
            bufferLen++;
        }
        //  If the buffer is full, arrange all the bits into a char and flush it to the file
        else
        {
            unsigned char byte = 0;
            bitBuffer[bufferLen] = newBit;

            for (int bitIndex = 0; bitIndex < 8; bitIndex++)
            {
                byte |= bitBuffer[bitIndex] << (7 - bitIndex);
            }

            bufferLen = 0;
            outputFile << byte;
        }
    }

    /**
     * @brief Writes N bits to the output file
     *
     * @param bitVector The bits to write
     */
    void writeNFileBit(vector<int> bitVector)
    {

        //  For every bit in the vector, write it to the filw
        for (int bit : bitVector)
        {
            writeOneFileBit(bit);
        }

        return;
    }

    /**
     * @brief Writes N bits to the output file
     *
     * @param bitVector The bits to write
     */
    void writeFileChar(char newChar)
    {
        //  For every one of the 8 bits in the char
        for (int bitIndex = 7; bitIndex >= 0; bitIndex--)
        {
            //  Get the bit in the current position and write it
            writeOneFileBit(((newChar >> bitIndex) & 1));
        }
        return;
    }

    /**
     * @brief Writes a char to the output file
     *
     * @param newChar The char to write
     */
    void writeFileString(string newString)
    {
        //  For every char in the string
        for (long unsigned int charIndex = 0; charIndex < newString.length(); charIndex++)
        {
            //  Write it to the output file
            writeFileChar(newString[charIndex]);
        }
        return;
    }

    /**
     * @brief Closes the input and output files and flushes the buffer to the output file
     */
    void close()
    {
        unsigned char byte = 0;

        //  If the buffer isn't empty
        if (bufferLen > 0)
        {
            //  Pad the rest of the buffer with zeros (arbitrary)
            for (int bitIndex = bufferLen; bitIndex < 8; bitIndex++)
            {
                bitBuffer[bitIndex] = 0;
            }

            //  Write all the bits in the buffer (that is now padded) into a new char
            for (int bitIndex = 0; bitIndex < 8; bitIndex++)
            {
                byte |= bitBuffer[bitIndex] << (7 - bitIndex);
            }

            //  Write the char to the file
            bufferLen = 0;
            outputFile << byte;
        }

        //  Close the files
        inputFile.close();
        outputFile.close();
    }
};
#endif