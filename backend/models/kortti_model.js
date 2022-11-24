const db = require('../database');

const kortti = {
  getById: function(id, callback) {
    return db.query('select * from kortti where id_kortti=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from kortti', callback);
  },
  add: function(add_data, callback) {
    return db.query(
      'insert into kortti (id_kortti,pin_koodi,id_asiakas,credit) values(?,?,?,?)',
      [add_data.id_kortti, add_data.pin_koodi, add_data.id_asiakas, add_data.credit],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from kortti where id_kortti=?', [id], callback);
  },
  update: function(id, update_data, callback) {
    return db.query(
      'update kortti set pin_koodi=?,id_asiakas=?, credit=? where id_kortti=?',
      [update_data.pin_koodi, update_data.id_asiakas, update_data.credit, id],
      callback
    );
  }
};
module.exports = kortti;