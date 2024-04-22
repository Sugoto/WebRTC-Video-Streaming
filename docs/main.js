let peerConnection = new RTCPeerConnection();
let localStream;
let remoteStream;

let init = async () => {
  localStream = await navigator.mediaDevices.getUserMedia({
    video: true,
    audio: false,
  });
  remoteStream = new MediaStream();
  document.getElementById("user-1").srcObject = localStream;
  document.getElementById("user-2").srcObject = remoteStream;

  localStream.getTracks().forEach((track) => {
    peerConnection.addTrack(track, localStream);
  });

  peerConnection.ontrack = (event) => {
    event.streams[0].getTracks().forEach((track) => {
      remoteStream.addTrack(track);
    });
  };
};

let createOffer = async () => {
  peerConnection.onicecandidate = async (event) => {
    //Event that fires off when a new offer ICE candidate is created
    if (event.candidate) {
      let sdpOffer = JSON.stringify(peerConnection.localDescription);
      navigator.clipboard.writeText(sdpOffer).then(
        function () {
          console.log("Copying to clipboard was successful!");
        },
        function (err) {
          console.error("Could not copy text: ", err);
        }
      );
    }
  };

  const offer = await peerConnection.createOffer();
  await peerConnection.setLocalDescription(offer);
};

let createAnswer = async () => {
  let offer = JSON.parse(document.getElementById("offer-sdp").value);

  peerConnection.onicecandidate = async (event) => {
    //Event that fires off when a new answer ICE candidate is created
    if (event.candidate) {
      let sdpAnswer = JSON.stringify(peerConnection.localDescription);
      navigator.clipboard.writeText(sdpAnswer).then(
        function () {
          console.log("Copying to clipboard was successful!");
        },
        function (err) {
          console.error("Could not copy text: ", err);
        }
      );
    }
  };

  await peerConnection.setRemoteDescription(offer);

  let answer = await peerConnection.createAnswer();
  await peerConnection.setLocalDescription(answer);
};

let addAnswer = async () => {
  console.log("Add answer triggerd");
  let answer = JSON.parse(document.getElementById("answer-sdp").value);
  console.log("answer:", answer);
  if (!peerConnection.currentRemoteDescription) {
    peerConnection.setRemoteDescription(answer);
  }
};

init();

document.getElementById("create-offer").addEventListener("click", createOffer);
document
  .getElementById("create-answer")
  .addEventListener("click", createAnswer);
document.getElementById("add-answer").addEventListener("click", addAnswer);
