const db = require('../database');

const tili = {
  getById: function(id, callback) {
    return db.query('select * from tili where id_tilinumero=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from tili', callback);
  },
  add: function(add_data, callback) {
    return db.query(
      'insert into tili (id_asiakas, saldo, luottoraja) values(?,?,?)',
      [add_data.id_asiakas, add_data.saldo, add_data.luottoraja],
      callback);
  }, 
  delete: function(id, callback) {
    return db.query('delete from tili where id_tilinumero=?', [id], callback);
  },
  update: function(id, update_data, callback) {
    return db.query(
      'update tili set id_asiakas=?,saldo=?, luottoraja=? where id_tilinumero=?',
      [update_data.id_asiakas, update_data.saldo, update_data.luottoraja, id],
      callback);
     }
};
module.exports = tili;