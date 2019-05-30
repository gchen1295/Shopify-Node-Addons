const axios = require("axios");
const Fuse = require('fuse.js');
const { performance } = require('perf_hooks')
const utils = require('util')
const botmodules = require('./build/Release/botmodules.node');

async function getProducts(domain) { 
  let r = await axios.get(`https://${domain}/products.json`);
  return(r.data['products']);
}

async function cartProductNode(domain, variant) { 
  let r = await axios.post(`https://${domain}/cart/add.json`,{id: variant, quantity: "1"});
  return(r.data);
}
let GetAllcpp = () =>{
  return new Promise((res,rej)=>{
    res(botmodules.getAllProducts("lapstoneandhammer.com"));
  })
}

let test1 = async () =>{
  let s1 = performance.now();
  for(let i = 0; i < 15 ; i++){
    let t  = await GetAllcpp();
    console.log(t)
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
let test2 = async () =>{
  let s1 = performance.now();
  let t1 = await botmodules.cartProduct("lapstoneandhammer.com","19339429773369");
  let j1 = JSON.parse(t1);
  let e1 = performance.now();
  let s2 = performance.now();
  let t2 = await cartProductNode("deadstock.ca","22337760821333");
  let e2 = performance.now();
  let d1 = e1 - s1;
  let d2 = e2 - s2;
  console.log(`Time of CPP Native: ${d1}`)
  console.log(`Time of Node Only: ${d2}`)

}

//test1()
let kws = [];
kws.push("nike");
let kw = kws.join('\t')
let s1 = performance.now();
let res = [];

let getall = utils.promisify(botmodules.findByTitle);
let getSizes = utils.promisify(botmodules.getSizes);
// botmodules.getSizes("undefeated.com", 2186306486345, t =>{
//   let e1 = performance.now();
//   let d1 = e1 - s1;
//   console.log(`Time of CPP Native: ${d1}`)
//   console.log("No Error Occured.")
//   console.log(t);
// })
getSizes("undefeated.com", "2186306486345").then( t =>{
  let e1 = performance.now();
  let d1 = e1 - s1;
  console.log(`Time of CPP Native: ${d1}`)
  console.log("No Error Occured.")
  let jps = JSON.parse(t);
  console.log(jps[0].variants);
}).catch(err=>{
  console.log(err);
})

//console.log(s);


module.exports = botmodules;