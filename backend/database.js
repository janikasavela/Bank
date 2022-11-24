const mysql = require('mysql');
const connection = mysql.createPool({
  host: 'localhost',
  user: 'group_13',
  password: 'netpass',
  database: 'pankki'
});
module.exports = connection;