const express = require('express');
const router = express.Router();
const tili = require('../models/tili_model');

router.get('/',
    function (request, response) {
        tili.getAll(function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                console.log(dbResult);
                response.json(dbResult);
            }
        })
    });

    router.get('/checkTilit/:id?', 
    function(request, response) {
          tili.checkTilit(request.params.id, function(dbError, dbResult) {
            if(dbError){
              response.json(dbError.errno);
            }
            else{
              console.log(dbResult);
              response.json(dbResult);
            }
            }
          );
        }
  );

router.get('/:id?',
    function (request, response) {
        tili.getById(request.params.id, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult[0]);
            }
        })
    });


router.post('/', 
function(request, response) {
  tili.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(request.body);
    }
  });
});


router.delete('/:id', 
function(request, response) {
  tili.delete(request.params.id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});


router.put('/:id', 
function(request, response) {
  tili.update(request.params.id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

module.exports = router;