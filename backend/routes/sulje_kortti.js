const express = require('express');
const router = express.Router();
const oikeudet = require('../models/oikeudet_model');

router.delete('/:id', 
function(request, response) {
  oikeudet.deleteOikeudet(request.params.id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

module.exports = router;