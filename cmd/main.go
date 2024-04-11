package main

import (
	"github.com/sugoto/video-streaming-webrtc/internal/server"
	"log"
)

func main() {
	if err := server.Run(); err != nil {
		log.Fatalln(err.Error())
	}
}
