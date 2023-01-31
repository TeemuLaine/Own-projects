let key = "99739c15a5b77a630bd844e973035da3"


createListItem = (album) =>{
    const listItemElement = document.createElement("div")
    listItemElement.className = "list-item-container"

    const albumElement = document.createElement("div")
    albumElement.className = "list-item-album"

    const albumInfo = document.createElement("p")
    albumInfo.innerHTML = album.artist.name + " - " + album.name
    albumElement.append(albumInfo)

    const albumCover = document.createElement("div")
    albumCover.className = "list-item-cover"
    const image = document.createElement("img")
    image.src = album.image[2]["#text"]
    albumCover.append(image)


    listItemElement.append(albumElement)
    listItemElement.append(albumCover)

    return listItemElement
}

fetchAlbums = async () => {
  let user = "SixRock"
  const listContainer = document.getElementById("album-list-container")
  try {
    const response = await fetch(
      "https://ws.audioscrobbler.com/2.0/?method=user.gettopalbums&user=" +
        user +
        "&api_key=" +
        key +
        "&format=json&limit=100"
    );
    const albums = await response.json();
    albums.topalbums.album.map((item) => {
      const listItem = createListItem(item)
      listContainer.append(listItem)
    })
  } catch (error) {
    console.log(error)
  }
}

fetchAlbums()
