var express = require('express');
var router = express.Router();
var sendgrid = require('sendgrid')('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');

router.get('/send', function(req, res) {
  var payload = {
    to: ['ahmed.elhanafy95@gmail.com','aya.magdy8@gmail.com'],
    from: 'aya.magdy@motion.com',
    subject: 'Motion Detected',
    text: 'Motion has been detected'
  }

  sendgrid.send(payload, function(err, json) {
  if (err) { console.error(err);
   }
  res.send(json);
});
})
module.exports = router;
