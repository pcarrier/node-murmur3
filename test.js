var assert = require('assert'),
    murmur3 = require('./index');

// Types don't matter, goes to new Buffer(toString()) as needed
   assert.equal(murmur3.hash32     (null),             0x00000000);
   assert.equal(murmur3.hash32     ('0'),              0xd271c07f);
   assert.equal(murmur3.hash32     (0),                0xd271c07f);
   assert.equal(murmur3.hash32     (new Buffer('0')),  0xd271c07f);
assert.deepEqual(murmur3.hash128$32(null),            [0x00000000, 0x00000000, 0x00000000, 0x00000000]);
assert.deepEqual(murmur3.hash128$32('0'),             [0x0ab2409e, 0xa5eb34f8, 0xa5eb34f8, 0xa5eb34f8]);
assert.deepEqual(murmur3.hash128$32(0),               [0x0ab2409e, 0xa5eb34f8, 0xa5eb34f8, 0xa5eb34f8]);
assert.deepEqual(murmur3.hash128$32(new Buffer('0')), [0x0ab2409e, 0xa5eb34f8, 0xa5eb34f8, 0xa5eb34f8]);
assert.deepEqual(murmur3.hash128$64(null),            [0x00000000, 0x00000000, 0x00000000, 0x00000000]);
assert.deepEqual(murmur3.hash128$64('0'),             [0xd546a380, 0x2ac9debe, 0x3c875e09, 0x3a8de9e5]);
assert.deepEqual(murmur3.hash128$64(0),               [0xd546a380, 0x2ac9debe, 0x3c875e09, 0x3a8de9e5]);
assert.deepEqual(murmur3.hash128$64(new Buffer('0')), [0xd546a380, 0x2ac9debe, 0x3c875e09, 0x3a8de9e5]);

// Good seeds work
    assert.equal(murmur3.hash32    ('0', 1),           0xb25d47eb);
assert.deepEqual(murmur3.hash128$32('0', 1),          [0x4f5d2aec, 0x233475a7, 0x233475a7, 0x233475a7]);
assert.deepEqual(murmur3.hash128$64('0', 1),          [0xdc0bd1ee, 0x360ba730, 0x4a11bae5, 0x51117ac9]);

// Bad seeds are ignored
    assert.equal(murmur3.hash32    ('0', 'wut'),       0xd271c07f);
    assert.equal(murmur3.hash32    ('0', {foo:-1}),    0xd271c07f);
assert.deepEqual(murmur3.hash128$32('0', 'wut'),      [0x0ab2409e, 0xa5eb34f8, 0xa5eb34f8, 0xa5eb34f8]);
assert.deepEqual(murmur3.hash128$32('0', {foo:-1}),   [0x0ab2409e, 0xa5eb34f8, 0xa5eb34f8, 0xa5eb34f8]);
assert.deepEqual(murmur3.hash128$64('0', 'wut'),      [0xd546a380, 0x2ac9debe, 0x3c875e09, 0x3a8de9e5]);
assert.deepEqual(murmur3.hash128$64('0', {foo:-1}),   [0xd546a380, 0x2ac9debe, 0x3c875e09, 0x3a8de9e5]);

// Except... JavaScript, people.
    assert.equal(murmur3.hash32    ('0', [1]),        0xb25d47eb);
assert.deepEqual(murmur3.hash128$32('0', [1]),       [0x4f5d2aec, 0x233475a7, 0x233475a7, 0x233475a7]);
assert.deepEqual(murmur3.hash128$64('0', [1]),       [0xdc0bd1ee, 0x360ba730, 0x4a11bae5, 0x51117ac9]);


