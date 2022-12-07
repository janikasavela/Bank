const db = require('../database');

const tili = {
  getById: function(id, callback) {
    return db.query('select * from tili where id_tilinumero=?', [id], callback);
  },
  checkOmistaja: function(id, callback) {
    return db.query('select concat(asiakas.etunimi," ",asiakas.sukunimi) as "tilin omistaja", asiakas.osoite as "osoite", asiakas.puhnum as "puhnum" from asiakas inner join tili on asiakas.id_asiakas=tili.id_asiakas where id_tilinumero=?', [id], callback);
  },
  checkAsiakas: function(id, callback) {
    return db.query('select concat(asiakas.etunimi," ",asiakas.sukunimi) as "kortin omistaja" from asiakas inner join kortti on asiakas.id_asiakas=kortti.id_asiakas where id_kortti=?', [id], callback);
  },
  checkTilit: function(id, callback) {
    return db.query('select tili.id_tilinumero, tili.saldo, tili.luottoraja from tili inner join oikeudet on tili.id_tilinumero=oikeudet.id_tilinumero where id_kortti=?',[id], callback);
  },
  getTiliInfo: function(id, callback){
    return db.query('select CONCAT(asiakas.etunimi," ", asiakas.sukunimi) as nimi, tili.saldo, tili.luottoraja from asiakas inner join tili on asiakas.id_asiakas=tili.id_asiakas where tili.id_tilinumero=?', [id], callback);
  },
  getSaldo: function(id, callback) {
    return db.query('select tili.saldo as "saldo", concat(asiakas.etunimi," ",asiakas.sukunimi) as "tilin omistaja", asiakas.osoite as "osoite", asiakas.puhnum as "puhnum", tilitapahtumat.tapahtuma, date_format(cast(tapahtuma_aika as date),"%d.%m.%Y") as "paiva", (cast(tapahtuma_aika as time)) as "aika", tilitapahtumat.summa as "summa" from tilitapahtumat inner join tili on tilitapahtumat.id_tilinumero=tili.id_tilinumero inner join asiakas on tili.id_asiakas=asiakas.id_asiakas where tilitapahtumat.id_tilinumero=? ORDER BY tilitapahtumat.tapahtuma_aika DESC LIMIT 5', [id], callback);
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
      'CALL nosto(?, ?, ?)',[update_data.id_kortti, update_data.id_tilinumero, update_data.maara],callback);
     },
  siirto: function(siirto_data, callback){
    return db.query(
      'CALL siirto(?, ?, ?, ?)',[siirto_data.id_kortti, siirto_data.id_miinustili, siirto_data.id_plustili, siirto_data.maara],callback);
     }
};
module.exports = tili;