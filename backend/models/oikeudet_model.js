const db = require('../database');

const oikeudet = {
  getById: function(id, callback) {
    return db.query('select * from oikeudet where id_kortti=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from oikeudet', callback);
  },
  deleteOikeudet: function(id, callback) {
    return db.query('delete from oikeudet where id_kortti=?', [id], callback);
  },
  add: function(add_data, callback) {
    return db.query(
      'insert into oikeudet (id_kortti, id_tilinumero) values(?,?)',
      [add_data.id_kortti, add_data.id_tilinumero],
      callback);
  }, 
  delete: function(id, callback) {
    return db.query('delete from oikeudet where id_oikeudet=?', [id], callback);
  },
  update: function(id, update_data, callback) {
    return db.query(
      'update oikeudet set id_kortti=?,id_tilinumero=? where id_oikeudet=?',
      [update_data.id_kortti, update_data.id_tilinumero, id],
      callback);
     }
};
module.exports = oikeudet;