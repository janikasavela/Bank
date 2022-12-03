var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

const jwt = require('jsonwebtoken');

function authenticateToken(req, res, next) {
    const authHeader = req.headers['authorization']
    const token = authHeader && authHeader.split(' ')[1]
  
    console.log("token = "+token);
    if (token == null) return res.sendStatus(401)
  
    jwt.verify(token, process.env.TOKEN, (err, user) => {
      console.log(err)
  
      if (err) return res.sendStatus(403)
  
      req.user = user
  
      next()
    })
  }

var korttiRouter = require('./routes/kortti');
var asiakasRouter = require('./routes/asiakas');
var tiliRouter = require('./routes/tili');
var oikeudetRouter = require('./routes/oikeudet');
var loginRouter = require('./routes/login');
var tilitapahtumatRouter = require('./routes/tilitapahtumat');
var selaa_tilitapahtumiaRouter = require('./routes/selaa_tilitapahtumia');
var hae_saldoRouter = require('./routes/hae_saldo');
var hae_omistajaRouter = require('./routes/hae_omistaja');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/login', loginRouter);
app.use(authenticateToken);
app.use('/kortti', korttiRouter);
app.use('/asiakas', asiakasRouter);
app.use('/tili', tiliRouter);
app.use('/oikeudet', oikeudetRouter);
app.use('/tilitapahtumat', tilitapahtumatRouter);
app.use('/selaa_tilitapahtumia', selaa_tilitapahtumiaRouter);
app.use('/hae_saldo', hae_saldoRouter);
app.use('/hae_omistaja', hae_omistajaRouter);


module.exports = app;
