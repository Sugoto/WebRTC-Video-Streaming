package main

import (
	"github.com/sugoto/video-streaming-webrtc/internal/server"
	"log"
)

// Main function
func main() {
	if err := server.Run(); err != nil {
		log.Fatalln(err.Error())
	}
}
