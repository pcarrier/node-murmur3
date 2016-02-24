var rawLib = require('./build/Release/murmur3');

module.exports = {
  hash32: function(data, seed) {
    seed = seed === undefined ? 0 : seed;
    data = Buffer.isBuffer(data) ? data : new Buffer(data == null ? '' : data.toString());
    return rawLib.hash32(data, seed);
  },
  hash128$32: function(data, seed) {
    seed = seed === undefined ? 0 : seed;
    data = Buffer.isBuffer(data) ? data : new Buffer(data == null ? '' : data.toString());
    return rawLib.hash128$32(data, seed);
  },
  hash128$64: function(data, seed) {
    seed = seed === undefined ? 0 : seed;
    data = Buffer.isBuffer(data) ? data : new Buffer(data == null ? '' : data.toString());
    return rawLib.hash128$64(data, seed);
  }
}
