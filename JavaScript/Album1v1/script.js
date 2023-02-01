let key = "99739c15a5b77a630bd844e973035da3"
let coverurl = []
let albuminfo = []
const ALBUM_MAX = 256
let used = new Array(ALBUM_MAX).fill(false)

winnerAlbum = () => {
  for (let i = 0; i < ALBUM_MAX; i++){
    if(!used[i]){
      return albuminfo[i]
    }
  }
}

manageMatchups = async (album, cover) => {
  let rCounter = 0
  for (let i = 1; i <= ALBUM_MAX / 2; i = i * 2) {
    rCounter++
    let usedThisRound = new Array(ALBUM_MAX / i).fill(false)
    for (let mCounter = 1; (mCounter * i) <= ALBUM_MAX / 2; mCounter++) {
      document.getElementById("round").innerHTML = "Round " + rCounter + ": Matchup " + mCounter
      await createMatchups(album, cover, usedThisRound)
    }
  }
  document.getElementById("winner").innerHTML += "The winning album is " + winnerAlbum() + "!"
}

createMatchups = async (album, cover, usedThisRound) => { // function to create the versus
  let num1
  let num2
  do {
    num1 = Math.floor(Math.random() * albuminfo.length)
  } while (used[num1] || usedThisRound[num1])
  usedThisRound[num1] = true
  do {
    num2 = Math.floor(Math.random() * albuminfo.length)
  } while (used[num2] || usedThisRound[num2])
  usedThisRound[num2] = true
  console.log(num1)
  console.log(num2)
  console.log(used)
  console.log(usedThisRound)
  console.log(albuminfo)
  const album1 = document.getElementById("album1")
  album1.innerHTML = album[num1]
  const image1 = document.getElementById("album1-image")
  image1.src = cover[num1]
  const album2 = document.getElementById("album2")
  album2.innerHTML = album[num2]
  const image2 = document.getElementById("album2-image")
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

fetchAlbums = async (user) => { // function to get the top albums data from lastfm, user as parameter
  try {
    const response = await fetch( // api request
      "https://ws.audioscrobbler.com/2.0/?method=user.gettopalbums&user=" +
      user +
      "&api_key=" +
      key +
      "&format=json&limit=" +
      ALBUM_MAX
    )
    const albums = await response.json()
    albums.topalbums.album.map((item) => { // map the json data into a usable form
      albuminfo.push(item.artist.name + " - " + item.name) // arrays for artist, album and cover art
      coverurl.push(item.image[3]["#text"])
    })
  } catch (error) {
    console.log(error)
  }
  manageMatchups(albuminfo, coverurl)
}

const usernameElement = document.getElementById("namefield")
const buttonElement = document.getElementById("submitButton")

buttonElement.onclick = () => { // fetch when username is given
  albuminfo = []
  coverurl = []
  username = usernameElement.value
  fetchAlbums(username)
}
