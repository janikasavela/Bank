const db = require('../database');

const tilitapahtumat = {
  getById: function(id, callback) {
    return db.query('select * from tilitapahtumat where id_tapahtuma=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from tilitapahtumat', callback);
  },
  add: function(add_data, callback) {
    return db.query(
      'insert into tilitapahtumat (id_tilinumero, id_kortti,tapahtuma_aika,tapahtuma,summa) values(?,?,?,?,?)',
      [add_data.id_tilinumero, add_data.id_kortti, add_data.tapahtuma_aika, add_data.tapahtuma, add_data.summa],
      callback);
  }, 
  delete: function(id, callback) {
    return db.query('delete from tilitapahtumat where id_tapahtuma=?', [id], callback);
  },
  update: function(id, update_data, callback) {
    return db.query(
      'update tilitapahtumat set id_tilinumero=?,id_kortti=?,tapahtuma_aika=?,tapahtuma=?,summa=? where id_tapahtuma=?',
      [update_data.id_tilinumero, update_data.id_kortti, update_data.tapahtuma_aika,update_data.tapahtuma,update_data.summa, id],
      callback);
     }
};
module.exports = tilitapahtumat;