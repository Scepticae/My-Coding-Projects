$("h1").text("Good Luck!");
$("h1").addClass("big-title margin-50");
$("button").html("<em>Enter</em>");
$("a").attr("href", "https://www.yahoo.com");
$("button").on("click", function () {
  $("h1").fadeToggle();
});