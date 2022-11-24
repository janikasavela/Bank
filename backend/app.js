var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var indexRouter = require('./routes/index');
var usersRouter = require('./routes/users');
var korttiRouter = require('./routes/kortti');
var asiakasRouter = require('./routes/asiakas');
var tiliRouter = require('./routes/tili');
var oikeudetRouter = require('./routes/oikeudet');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/users', usersRouter);
app.use('/kortti', korttiRouter);
app.use('/asiakas', asiakasRouter);
app.use('/tili', tiliRouter);
app.use('/oikeudet', oikeudetRouter);


module.exports = app;
