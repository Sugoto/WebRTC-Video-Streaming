#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

// Define a structure to represent a color pixel (RGB)
struct ColorPixel
{
    unsigned char r, g, b;
};

// Function to encode a video frame using LZW compression
std::vector<unsigned short> encodeFrame(const std::vector<ColorPixel> &frame)
{
    std::unordered_map<std::string, unsigned short> dictionary;
    std::vector<unsigned short> encodedFrame;
    std::string currentCode = "";

    // Initialize the dictionary with single-pixel entries
    for (int i = 0; i < 256; ++i)
        dictionary[std::string(1, static_cast<char>(i))] = i;

    for (const ColorPixel &pixel : frame)
    {
        std::string pixelString = std::to_string(pixel.r) + "," + std::to_string(pixel.g) + "," + std::to_string(pixel.b);

        // Concatenate the current code with the pixel string
        std::string extendedCode = currentCode + pixelString;

        // If the extended code is in the dictionary, continue building the current code
        if (dictionary.find(extendedCode) != dictionary.end())
            currentCode = extendedCode;

        else
        {
            // Add the current code to the encoded frame
            encodedFrame.push_back(dictionary[currentCode]);

            // Add the extended code to the dictionary
            if (dictionary.size() < 65536)
                dictionary[extendedCode] = static_cast<unsigned short>(dictionary.size());

            // Start a new code with the pixel string
            currentCode = pixelString;
        }
    }

    // Add the last code to the encoded frame
    encodedFrame.push_back(dictionary[currentCode]);

    return encodedFrame;
}

// Function to decode a video frame encoded using LZW compression
std::vector<ColorPixel> decodeFrame(const std::vector<unsigned short> &encodedFrame)
{
    std::unordered_map<unsigned short, std::string> dictionary;
    std::vector<ColorPixel> decodedFrame;
    unsigned short currentCode = encodedFrame[0];

    // Initialize the dictionary with single-pixel entries
    for (int i = 0; i < 256; ++i)
        dictionary[i] = std::to_string(i);

    for (size_t i = 1; i < encodedFrame.size(); ++i)
    {
        unsigned short code = encodedFrame[i];

        if (dictionary.find(code) != dictionary.end())
        {
            // If the code is in the dictionary, append it to the current code
            std::string currentString = dictionary[currentCode];
            std::string newString = dictionary[code];
            currentString += newString;

            // Add the new code to the dictionary
            if (dictionary.size() < 65536)
                dictionary[static_cast<unsigned short>(dictionary.size())] = currentString;

            // Add the new pixel to the decoded frame
            for (size_t j = 0; j < newString.length(); j += 11)
            {
                unsigned char r = std::stoi(newString.substr(j, 3));
                unsigned char g = std::stoi(newString.substr(j + 4, 3));
                unsigned char b = std::stoi(newString.substr(j + 8, 3));
                decodedFrame.push_back({r, g, b});
            }

            currentCode = code;
        }
        else
        {
            std::string currentString = dictionary[currentCode];
            std::string newString = currentString + currentString[0]; // Replicate the first character
            dictionary[static_cast<unsigned short>(dictionary.size())] = newString;

            // Add the new pixel to the decoded frame
            for (size_t j = 0; j < newString.length(); j += 11)
            {
                unsigned char r = std::stoi(newString.substr(j, 3));
                unsigned char g = std::stoi(newString.substr(j + 4, 3));
                unsigned char b = std::stoi(newString.substr(j + 8, 3));
                decodedFrame.push_back({r, g, b});
            }

            currentCode = code;
        }
    }

    return decodedFrame;
}

int main()
{
    std::vector<ColorPixel> originalFrame = {
        {255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 0, 0}, {255, 0, 0}, {0, 0, 255}, {0, 0, 255}, {255, 0, 0}, {0, 255, 0}, {0, 255, 0}};

    // Encode the frame using LZW compression
    std::vector<unsigned short> encodedFrame = encodeFrame(originalFrame);

    // Decode the frame
    std::vector<ColorPixel> decodedFrame = decodeFrame(encodedFrame);

    // Verify the decoded frame matches the original
    if (originalFrame == decodedFrame)
        std::cout << "Video frame encoding and decoding successful." << std::endl;

    else
        std::cout << "Video frame encoding and decoding failed." << std::endl;

    return 0;
}
