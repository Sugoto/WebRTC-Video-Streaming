#ifndef VIDEO_CODEC_H
#define VIDEO_CODEC_H

#include <vector>

// Define a structure to represent a color pixel (RGB)
struct ColorPixel
{
    unsigned char r, g, b;
};

class VideoCodec
{
public:
    VideoCodec() {}

    std::vector<unsigned short> encodeRLE(const std::vector<ColorPixel> &frame);
    std::vector<ColorPixel> decodeRLE(const std::vector<unsigned short> &encodedFrame);

    std::vector<unsigned short> encodeLZW(const std::vector<ColorPixel> &frame);
    std::vector<ColorPixel> decodeLZW(const std::vector<unsigned short> &encodedFrame);

    std::vector<ColorPixel> deltaEncodeFrames(const std::vector<std::vector<ColorPixel>> &frames);
    std::vector<std::vector<ColorPixel>> deltaDecodeFrames(const std::vector<ColorPixel> &encodedFrames, int frameWidth, int frameHeight);
};

#endif // VIDEO_CODEC_H
