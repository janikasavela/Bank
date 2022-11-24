const db = require('../database');

const asiakas = {
  getById: function(id, callback) {
    return db.query('select * from asiakas where id_asiakas=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from asiakas', callback);
  },
  add: function(add_data, callback) {
    return db.query(
      'insert into asiakas (etunimi,sukunimi,osoite,puhnum) values(?,?,?,?)',
      [add_data.etunimi, add_data.sukunimi, add_data.osoite, add_data.puhnum],
      callback);
  }, 
  delete: function(id, callback) {
    return db.query('delete from asiakas where id_asiakas=?', [id], callback);
  },
  update: function(id, update_data, callback) {
    return db.query(
      'update asiakas set etunimi=?,sukunimi=?, osoite=?, puhnum=? where id_asiakas=?',
      [update_data.etunimi, update_data.sukunimi, update_data.osoite, update_data.puhnum, id],
      callback);
     }
};
module.exports = asiakas;