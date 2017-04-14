var assert = require('assert'), bench = require('benchmark'), murmur3 = require('./index');

var sink = 0, warmOps = 10*1000*1000, measuredOps = 100*1000*1000;

function run(times) {
	var t = new Date();
	for (var i = 0; i < times; i++) {
		sink += murmur3.$double(0);
	}
	return (new Date() - t) / 1000;
}

run(warmOps);
console.log("Naively measuring " + measuredOps / run(measuredOps) + " ops/sec on noop");

new bench.Suite()
.add("noop", function() {
	sink = murmur3.$double(0);
}).add("hash32", function() {
	sink = murmur3.hash32(null);
}).add("hash128$32", function() {
	sink = murmur3.hash128$32(null);
}).add("hash128$64", function() {
	sink = murmur3.hash128$64(null);
}).on('cycle', function(event) {
	console.log(String(event.target));
}).run({ 'async': true });
