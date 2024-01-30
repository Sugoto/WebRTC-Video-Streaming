#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

// Define a structure to represent a color pixel (RGB)
struct ColorPixel
{
    unsigned char r, g, b;
};

// Define a structure to represent a quantized color (for simplicity, we use 8 colors)
struct QuantizedColor
{
    unsigned char r, g, b;
};

// Function to quantize a color pixel to a limited set of colors (8 colors in this example)
QuantizedColor quantizeColor(const ColorPixel &pixel)
{
    int quantizationSteps = 8; // Number of quantization levels (adjust as needed)
    int stepSize = 256 / quantizationSteps;

    QuantizedColor quantizedPixel;
    quantizedPixel.r = static_cast<unsigned char>((pixel.r / stepSize) * stepSize);
    quantizedPixel.g = static_cast<unsigned char>((pixel.g / stepSize) * stepSize);
    quantizedPixel.b = static_cast<unsigned char>((pixel.b / stepSize) * stepSize);

    return quantizedPixel;
}

// Function to encode a video frame using Run-Length Encoding (RLE)
std::vector<std::pair<QuantizedColor, int>> encodeFrame(const std::vector<QuantizedColor> &frame)
{
    std::vector<std::pair<QuantizedColor, int>> encodedFrame;
    int count = 1;

    for (int i = 1; i < frame.size(); ++i)
    {
        if (frame[i] == frame[i - 1])
            count++;

        else
        {
            encodedFrame.push_back(std::make_pair(frame[i - 1], count));
            count = 1;
        }
    }

    encodedFrame.push_back(std::make_pair(frame.back(), count));
    return encodedFrame;
}

// Function to decode a video frame encoded using Run-Length Encoding (RLE)
std::vector<QuantizedColor> decodeFrame(const std::vector<std::pair<QuantizedColor, int>> &encodedFrame)
{
    std::vector<QuantizedColor> decodedFrame;

    for (const auto &pair : encodedFrame)
    {
        int count = pair.second;
        for (int i = 0; i < count; ++i)
            decodedFrame.push_back(pair.first);
    }

    return decodedFrame;
}

int main()
{
    std::vector<ColorPixel> originalFrame = {
        {255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 0, 0}, {255, 0, 0}, {0, 0, 255}, {0, 0, 255}, {255, 0, 0}, {0, 255, 0}, {0, 255, 0}};

    // Quantize the original frame
    std::vector<QuantizedColor> quantizedFrame;
    for (const auto &pixel : originalFrame)
        quantizedFrame.push_back(quantizeColor(pixel));

    // Encode the quantized frame
    std::vector<std::pair<QuantizedColor, int>> encodedFrame = encodeFrame(quantizedFrame);

    // Decode the frame
    std::vector<QuantizedColor> decodedFrame = decodeFrame(encodedFrame);

    // Verify the decoded frame matches the quantized original
    if (quantizedFrame == decodedFrame)
        std::cout << "Full-color video frame encoding and decoding successful." << std::endl;

    else
        std::cout << "Full-color video frame encoding and decoding failed." << std::endl;

    return 0;
}
