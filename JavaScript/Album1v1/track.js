let key = "99739c15a5b77a630bd844e973035da3"
let coverurl = []
let trackinfo = []
const track_MAX = 128
let used = new Array(track_MAX).fill(false)

winnertrack = () => {
  for (let i = 0; i < track_MAX; i++){
    if(!used[i]){
      return trackinfo[i]
    }
  }
}

manageMatchups = async (track, cover) => {
  let rCounter = 0
  for (let i = 1; i <= track_MAX / 2; i = i * 2) {
    rCounter++
    let usedThisRound = new Array(track_MAX / i).fill(false)
    for (let mCounter = 1; (mCounter * i) <= track_MAX / 2; mCounter++) {
      document.getElementById("round").innerHTML = "Round " + rCounter + ": Matchup " + mCounter
      await createMatchups(track, cover, usedThisRound)
    }
  }
  document.getElementById("winner").innerHTML += "The winning track is " + winnertrack() + "!"
}

createMatchups = async (track, cover, usedThisRound) => { // function to create the versus
  let num1
  let num2
  do {
    num1 = Math.floor(Math.random() * trackinfo.length)
  } while (used[num1] || usedThisRound[num1])
  usedThisRound[num1] = true
  do {
    num2 = Math.floor(Math.random() * trackinfo.length)
  } while (used[num2] || usedThisRound[num2])
  usedThisRound[num2] = true
  const track1 = document.getElementById("track1")
  track1.innerHTML = track[num1]
  const image1 = document.getElementById("track1-image")
  image1.src = cover[num1]
  const track2 = document.getElementById("track2")
  track2.innerHTML = track[num2]
  const image2 = document.getElementById("track2-image")
  image2.src = cover[num2]

  getClick = () => {  // Function that stops the loop until a click happens
    return new Promise(acc => {
      image1.onclick = () => {
        used[num2] = true
        acc()
      }
      image2.onclick = () => {
        used[num1] = true
        acc()
      }
    })
  } // This should not have been as hard as it was...

  await getClick()
}

fetchtracks = async (user) => { // function to get the top tracks data from lastfm, user as parameter
  try {
    const response = await fetch( // api request
      "https://ws.audioscrobbler.com/2.0/?method=user.gettoptracks&user=" +
      user +
      "&api_key=" +
      key +
      "&format=json&limit=" +
      track_MAX
    )
    const tracks = await response.json()
    tracks.toptracks.track.map((item) => { // map the json data into a usable form
      trackinfo.push(item.artist.name + " - " + item.name) // arrays for artist, track and cover art
      coverurl.push(item.image[2]["#text"])
    })
  } catch (error) {
  }
  manageMatchups(trackinfo, coverurl)
}

const usernameElement = document.getElementById("namefield")
const buttonElement = document.getElementById("submitButton")

buttonElement.onclick = () => { // fetch when username is given
  trackinfo = []
  coverurl = []
  username = usernameElement.value
  fetchtracks(username)
}


