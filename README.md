# 🎥 Realtime Peer-to-Peer Video Streaming

Realtime Peer-to-Peer Video Streaming is a project that leverages WebRTC and Go to achieve millisecond latency for video streaming between peers.

# 🌟 Video Compression Approaches and Wrapper Class

### 1. Run-Length Encoding (RLE)
- RLE is a simple lossless compression technique that encodes consecutive identical data values as a single value followed by a count.

### 2. Lempel-Ziv-Welch (LZW) Compression
- LZW is a dictionary-based lossless compression method that encodes repetitive data patterns efficiently.
  
### 3. Delta Encoding
- Delta encoding focuses on encoding the differences between consecutive video frames to reduce redundancy.

### 🧩 VideoCodec Wrapper Class
- A `VideoCodec` class acts as a wrapper that combines the three compression approaches into a unified interface for video compression and decompression.

## Requirements

- Go 1.16 or higher
- Node.js and npm (for frontend development)
- Modern web browser that supports WebRTC (Chrome, Firefox, Safari, etc.)
- A server with a public IP address (for signaling and relay)
