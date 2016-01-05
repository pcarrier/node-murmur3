Tinytest.add('hash32 is reachable', function (test) {
    test.equal(Murmur3.hash32('0'), 0xd271c07f);
});
