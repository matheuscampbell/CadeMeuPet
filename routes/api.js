var express = require('express');
const fs = require('fs');
var router = express.Router();

/* GET users listing. */
router.get('/setLocation/:lat/:long', function(req, res, next) {
  var data = readJsonData();
  data.actualLocation = {
    "lat": req.params.lat,
    "long": req.params.long,
    "timestamp": Date.now()
  };
  console.log(data.actualLocation);
  writeJsonData(data);
  res.send('ok');
});

router.get('/getActualLocation', function(req, res, next) {
  var data = readJsonData();
  res.send(JSON.stringify(data.actualLocation));
});



function readJsonData(){
  let rawdata = fs.readFileSync('./data/locations.json');
  return JSON.parse(rawdata);
}

function writeJsonData(data){
  data = JSON.stringify(data);
  fs.writeFileSync('./data/locations.json', data);
}



module.exports = router;
