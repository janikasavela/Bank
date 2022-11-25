const db = require('../database');

const bcrypt = require('bcryptjs');

const saltRounds=10;

const kortti = {
  checkPin_koodi: function(id_kortti, callback) {
    return db.query('SELECT pin_koodi FROM kortti WHERE id_kortti = ?',[id_kortti], callback); 
  },
  getById: function(id, callback) {
    return db.query('select * from kortti where id_kortti=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from kortti', callback);
  },
  add: function(add_data, callback) {
    bcrypt.hash(add_data.pin_koodi, saltRounds, function(err, hashedPinKoodi){
    return db.query(
      'insert into kortti (id_kortti,pin_koodi,id_asiakas,credit) values(?,?,?,?)',
      [add_data.id_kortti, hashedPinKoodi, add_data.id_asiakas, add_data.credit],
      callback);
    });
  },
  delete: function(id, callback) {
    return db.query('delete from kortti where id_kortti=?', [id], callback);
  },
  update: function(id, update_data, callback) {
    bcrypt.hash(update_data.pin_koodi, saltRounds, function(err, hashedPinKoodi){
    return db.query(
      'update kortti set pin_koodi=?,id_asiakas=?, credit=? where id_kortti=?',
      [hashedPinKoodi, update_data.id_asiakas, update_data.credit, id],
      callback);
    });
  }
};
module.exports = kortti;