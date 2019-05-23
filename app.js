const http = require('./build/Release/testaddon.node');
console.log(http.post(''));
console.log(http.authLicense("L62PL-DXHFQ-2XQ91-X76RN-2M4AU","Test"));
module.exports = http;