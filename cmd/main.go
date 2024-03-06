package main

import (
	"github.com/sugoto/video-streaming-webrtc/internal/server"
	"log"
)

// Start the server
func main() {
	if err := server.Run(); err != nil {
		log.Fatalln(err.Error())
	}
}
