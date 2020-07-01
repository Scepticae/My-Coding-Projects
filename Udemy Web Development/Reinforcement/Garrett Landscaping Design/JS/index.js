//Grabs galleries and gallery frame
const imageGalleries = $(".carousel-popup");
const gallery = $(".carousel-container");

//Image Gallery Controls
const closeButton = $(".close-btn");
const nextButton = $(".next-btn");
const prevButton = $(".prev-btn");

//Image Selection Identifiers
var gallerySelection = [];
var currentImage = 0;

//Image Carousels
var lawncareGallery = [
  "Images/Lawncare/lawn-care_1.jpg",
  "Images/Lawncare/lawn-care_2.jpg",
  "Images/Lawncare/lawn-care_3.jpg"
];
var landscapeGallery = [
  "Images/Landscaping/landscape_1.jpg",
  "Images/Landscaping/landscape_2.jpg",
  "Images/Landscaping/landscape_3.jpg"
];
var hardscapeGallery = [
  "Images/Hardscape/hardscape_1.jpg",
  "Images/Hardscape/hardscape_2.jpg",
  "Images/Hardscape/hardscape_3.jpg"
];

//Scrolls page to top on refresh
$(window).on('beforeunload', function(){
  $(window).scrollTop(0);
});

//Hide the image gallery
gallery.hide();

//Show the selected image gallery
function showGallery(){
  gallery.show();
}

//Display the selected carousel-container when image clicked
imageGalleries.click(function(e){
  currentImage = 0;
  if(e.currentTarget.innerText === "Lawn Care"){ gallerySelection = lawncareGallery; }
  else if(e.currentTarget.innerText === "Landscaping"){ gallerySelection = landscapeGallery; }
  else { gallerySelection = hardscapeGallery; }
  $(".carousel-img").attr("src", gallerySelection[currentImage]);
  setTimeout(showGallery, 300);
});

//Close container when close button clicked
closeButton.click(function(){
  gallery.hide();
});

//Move to next image when next button clicked
nextButton.click(function(){
  currentImage++;
  if(currentImage === gallerySelection.length){
    currentImage = 0;
  }
  $(".carousel-img").attr("src", gallerySelection[currentImage]);
});

//Move to previous image when previous button clicked
prevButton.click(function(){
  currentImage--;
  if(currentImage < 0){
    currentImage = gallerySelection.length - 1;
  }
  $(".carousel-img").attr("src", gallerySelection[currentImage]);
});


function toggleMenu(){
  if(navbar.hasClass("responsive")){
    navbar.removeClass("responsive");
  }
  else{
    navbar.addClass("responsive");
  }
}

//Smaller screen navbar handler
var icon = $(".dropdownIcon");
var navbar = $("#dropdownClick");

//Add responsive class to topnav when hamburger menu clicked
icon.on("click", toggleMenu);