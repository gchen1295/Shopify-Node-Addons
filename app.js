const axios = require("axios");
const Fuse = require('fuse.js');
const { performance } = require('perf_hooks')
const http = require('./build/Release/botmodules.node');
//console.log(http.post(''));
//console.log(http.authLicense("L62PL-DXHFQ-2XQ91-X76RN-2M4AU","Test"));

async function getProducts(domain) { // Add error handling here 
  let r = await axios.get(`https://${domain}/products.json`);
  return(r.data['products']);
}
let GetAllcpp = () =>{
  return new Promise((res,rej)=>{
    res(http.getAllProducts("lapstoneandhammer.com"));
  })
}

let test = async () =>{
  let s1 = performance.now();
  for(let i = 0; i < 15 ; i++){
    await GetAllcpp();
    //console.log(t)
  }
  let e1 = performance.now();
  let s2 = performance.now();
  for(let i = 0; i < 15 ; i++){
    await getProducts("centre214.com");
    //console.log(t);
  }
  let e2 = performance.now();
  let d1 = e1 - s1;
  let d2 = e2 - s2;
  console.log(`Time of CPP Native: ${d1}`)
  console.log(`Time of Node Module: ${d2}`)
}

test();

module.exports = http;