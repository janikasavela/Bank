const db = require('../database');

const tili = {
  getById: function(id, callback) {
    return db.query('select * from tili where id_tilinumero=?', [id], callback);
  },
  checkTilit: function(id, callback) {
    return db.query('select tili.id_tilinumero, tili.saldo, tili.luottoraja from tili inner join oikeudet on tili.id_tilinumero=oikeudet.id_tilinumero where id_kortti=?', [id], callback);
  },
  getTiliInfo: function(id, callback){
    return db.query('select CONCAT(asiakas.etunimi," ", asiakas.sukunimi) as nimi, tili.saldo, tili.luottoraja from asiakas inner join tili on asiakas.id_asiakas=tili.id_asiakas where tili.id_tilinumero=?', [id], callback);
  },
  getSaldo: function(id, callback) {
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
     },  
  nosto: function(update_data, callback) {
    return db.query(
      'update tili set saldo=? where id_tilinumero=?',[update_data.saldo, update_data.id_tilinumero],callback);
     }
};
module.exports = tili;