Package.describe({
  name: 'pcarrier:node-murmur3',
  summary: 'Server-side MurmurHash3',
  version: '1.0.4_1',
  documentation: null
});

Npm.depends({
  'node-murmur3': '1.0.4'
});

Package.onUse(function (api) {
  api.export('Murmur3', 'server');
  api.addFiles('wrapper.js', 'server');
});

Package.onTest(function (api) {
  api.use(['tinytest', 'pcarrier:node-murmur3']);
  api.addFiles('wrapper-tests.js', 'server');
});
