#include <iostream>
#include <vector>
#include <algorithm>

// Define a structure to represent a color pixel (RGB)
struct ColorPixel
{
    unsigned char r, g, b;
};

// Function to calculate the absolute difference between two color pixels
ColorPixel colorDifference(const ColorPixel &a, const ColorPixel &b)
{
    ColorPixel diff;
    diff.r = std::abs(a.r - b.r);
    diff.g = std::abs(a.g - b.g);
    diff.b = std::abs(a.b - b.b);
    return diff;
}

// Function to encode a video frame using Run-Length Encoding (RLE)
std::vector<std::pair<ColorPixel, int>> encodeFrame(const std::vector<ColorPixel> &frame)
{
    std::vector<std::pair<ColorPixel, int>> encodedFrame;
    int count = 1;

    for (int i = 1; i < frame.size(); ++i)
    {
        if (frame[i] == frame[i - 1])
            count++;

        else
            encodedFrame.push_back(std::make_pair(frame[i - 1], count));
        count = 1;
    }

    encodedFrame.push_back(std::make_pair(frame.back(), count));
    return encodedFrame;
}

// Function to decode a video frame encoded using Run-Length Encoding (RLE)
std::vector<ColorPixel> decodeFrame(const std::vector<std::pair<ColorPixel, int>> &encodedFrame)
{
    std::vector<ColorPixel> decodedFrame;

    for (const auto &pair : encodedFrame)
    {
        int count = pair.second;
        for (int i = 0; i < count; ++i)
            decodedFrame.push_back(pair.first);
    }

    return decodedFrame;
}

// Function to encode a sequence of video frames using Delta encoding
std::vector<ColorPixel> deltaEncodeFrames(const std::vector<std::vector<ColorPixel>> &frames)
{
    std::vector<ColorPixel> encodedFrames;
    encodedFrames.reserve(frames.size());

    for (size_t i = 1; i < frames.size(); ++i)
    {
        const std::vector<ColorPixel> &currentFrame = frames[i];
        const std::vector<ColorPixel> &previousFrame = frames[i - 1];
        std::vector<ColorPixel> encodedFrame;

        for (size_t j = 0; j < currentFrame.size(); ++j)
            encodedFrame.push_back(colorDifference(currentFrame[j], previousFrame[j]));

        encodedFrames.insert(encodedFrames.end(), encodedFrame.begin(), encodedFrame.end());
    }

    return encodedFrames;
}

// Function to decode a sequence of video frames encoded using Delta encoding
std::vector<std::vector<ColorPixel>> deltaDecodeFrames(const std::vector<ColorPixel> &encodedFrames, int frameWidth, int frameHeight)
{
    std::vector<std::vector<ColorPixel>> decodedFrames;
    decodedFrames.reserve(encodedFrames.size() / (frameWidth * frameHeight) + 1);

    for (size_t i = 0; i < encodedFrames.size(); i += frameWidth * frameHeight)
    {
        std::vector<ColorPixel> decodedFrame;
        decodedFrame.reserve(frameWidth * frameHeight);

        for (size_t j = i; j < i + frameWidth * frameHeight; ++j)
            decodedFrame.push_back(encodedFrames[j]);

        decodedFrames.push_back(decodedFrame);
    }

    return decodedFrames;
}

int main()
{
    const int frameWidth = 3;
    const int frameHeight = 3;

    std::vector<std::vector<ColorPixel>> originalFrames = {
        {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}},
        {{250, 0, 0}, {5, 255, 0}, {5, 0, 255}},
        {{245, 0, 0}, {10, 255, 0}, {10, 0, 255}},
        {{240, 0, 0}, {15, 255, 0}, {15, 0, 255}},
    };

    // Encode individual frames using RLE
    std::vector<std::vector<std::pair<ColorPixel, int>>> encodedFrames;
    for (const auto &frame : originalFrames)
        encodedFrames.push_back(encodeFrame(frame));

    // Encode the sequence of frames using Delta encoding
    std::vector<ColorPixel> deltaEncodedFrames = deltaEncodeFrames(originalFrames);

    // Decode the sequence of frames
    std::vector<std::vector<ColorPixel>> decodedFrames = deltaDecodeFrames(deltaEncodedFrames, frameWidth, frameHeight);

    // Verify the decoded frames match the original
    bool allFramesMatch = true;
    for (size_t i = 0; i < originalFrames.size(); ++i)
    {
        if (originalFrames[i] != decodedFrames[i])
        {
            allFramesMatch = false;
            break;
        }
    }

    if (allFramesMatch)
        std::cout << "Video frame encoding and decoding successful." << std::endl;

    else
        std::cout << "Video frame encoding and decoding failed." << std::endl;

    return 0;
}
