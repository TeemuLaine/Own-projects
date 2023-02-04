let key = "99739c15a5b77a630bd844e973035da3"
let artistpics = []
let artistnames = []
let ARTIST_MAX = 256
let used
let period

winnerArtist = () => {
  for (let i = 0; i < ARTIST_MAX; i++) {
    if (!used[i]) {
      return artistnames[i]
    }
  }
}

manageMatchups = async (artist, pic) => {
  let rCounter = 0
  for (let i = 1; i <= ARTIST_MAX / 2; i = i * 2) {
    rCounter++
    let usedThisRound = new Array(ARTIST_MAX / i).fill(false)
    for (let mCounter = 1; (mCounter * i) <= ARTIST_MAX / 2; mCounter++) {
      document.getElementById("round").innerHTML = "Round " + rCounter + ": Matchup " + mCounter
      await createMatchups(artist, pic, usedThisRound)
    }
  }
  document.getElementById("winner").innerHTML = "The winning artist is " + winnerArtist() + "!"
}

createMatchups = async (artist, pic, usedThisRound) => { // function to create the versus
  let num1
  let num2
  do {
    num1 = Math.floor(Math.random() * artistnames.length)
  } while (used[num1] || usedThisRound[num1])
  usedThisRound[num1] = true
  do {
    num2 = Math.floor(Math.random() * artistnames.length)
  } while (used[num2] || usedThisRound[num2])
  usedThisRound[num2] = true
  const artist1 = document.getElementById("artist1")
  artist1.innerHTML = artist[num1]
  const image1 = document.getElementById("artist1-image")
  image1.src = pic[num1]
  const artist2 = document.getElementById("artist2")
  artist2.innerHTML = artist[num2]
  const image2 = document.getElementById("artist2-image")
  image2.src = pic[num2]

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

fetchArtists = async (user) => { // function to get the top artists data from lastfm, user as
  used = new Array(ARTIST_MAX).fill(false)
  try {
    const response = await fetch( // api request
      "http://ws.audioscrobbler.com/2.0/?method=user.gettopartists&user=" +
      user +
      "&api_key=" +
      key +
      "&format=json&limit=" +
      ARTIST_MAX +
      "&period=" +
      period
    )
    const artists = await response.json()
    artists.topartists.artist.map((item) => { // map the json data into a usable form
      artistnames.push(item.name) // arrays for artist, artist and cover artist
      artistpics.push(item.image[3]["#text"])
    })
  } catch (error) {
  }
  manageMatchups(artistnames, artistpics)
}

const usernameElement = document.getElementById("namefield")
const buttonElement = document.getElementById("submitButton")

buttonElement.onclick = () => { // fetch when username is given
  artistnames = []
  artistpics = []
  username = usernameElement.value
  if (username) {
    fetchArtists(username)
  }
}

const amountElement = document.getElementById("amount");
amountElement.addEventListener("change", (event) => {
  ARTIST_MAX = amountElement.value
})

const periodElement = document.getElementById("period");
periodElement.addEventListener("change", (event) => {
  period = periodElement.value
})