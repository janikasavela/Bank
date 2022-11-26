const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const kortti = require('../models/kortti_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');

router.post('/', 
  function(request, response) {
    if(request.body.id_kortti && request.body.pin_koodi){
      const id_kortti = request.body.id_kortti;
      const pin_koodi = request.body.pin_koodi;
        kortti.checkPin_koodi(id_kortti, function(dbError, dbResult) {
          if(dbError){
            response.json(dbError.errno);
          }
          else{
            if (dbResult.length > 0) {
              bcrypt.compare(pin_koodi,dbResult[0].pin_koodi, function(err,compareResult) {
                if(compareResult) {
                  console.log("succes");
                  //response.send(true);
                  const token = generateAccessToken({username:id_kortti})
                  response.send(token); 
                }
                else {
                    console.log("wrong pin_koodi");
                    response.send(false);
                }			
              }
              );
            }
            else{
              console.log("user does not exists");
              response.send(false);
            }
          }
          }
        );
      }
    else{
      console.log("id_kortti or pin_koodi missing");
      response.send(false);
    }
  }
);

function generateAccessToken(username)
{
    dotenv.config();
    return jwt.sign(username, process.env.TOKEN, { expiresIn: '1800s' });
} 

module.exports=router;