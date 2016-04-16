var express = require('express');
var Firebase = require("firebase");
var app = express();

var myFirebaseRef = new Firebase("https://motion-detector.firebaseio.com/");


app.get('/api/:motion', function(req, res) {
  var detection = req.params.motion;
  if (detection == 1) {
    myFirebaseRef.set({
      title: "1"
    });
  } else {
    myFirebaseRef.set({
      title: "0"
    });
  }

  console.log(detection);
  res.send(detection);
})

app.use('/', express.static('public'));

app.listen(3000, function() {
  console.log("Your app is listening in port 3000")
})
