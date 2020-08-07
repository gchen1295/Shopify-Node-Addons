const axios = require("axios");
const Fuse = require('fuse.js');
const {
  performance
} = require('perf_hooks')
const util = require('util')
const Shopify = require('./build/Release/botmodules.node');

async function monitorProduct(domain, keywords) {
  let start = performance.now()
  let toWatch = [];
  // Log all found items
  let found2 = await findByHandle(domain, keywords);
  //console.log(JSON.parse(found1));
  if (found2 === "[]") {
    console.log("No product found!!");
  } else {
    let pfound2 = JSON.parse(found2);
    //Grab all out of stock sizes and store here
    for (i in pfound2) {
      let outstock = await outstockSizes(domain, pfound2[i].id);
      let par = JSON.parse(outstock);
      for (j in par) {
        toWatch.push(par[i]);
      }
    }
    //console.log(toWatch);
    // Start our monitoring here
    //Check for instock sizes
    for (i in toWatch) {
      let variants = [];
      for (tw in toWatch[i].variants) {
        variants.push(toWatch[i].variants[tw].id);
      }
      let restocked = await checkRestock(domain, toWatch[i].id, variants);
      console.log(restocked);
    }
  }


  let end = performance.now()
  let diff = end - start;
  console.log(`\x1b[35mFinished in ${diff} milliseconds\x1b[0m`);
}
//test1()
let kws = [];
kws.push("nike");
let kw = kws.join('\t')
let s1 = performance.now();
let res = [];

let getProducts = util.promisify(Shopify.getAllProducts)
let findByTitle = util.promisify(Shopify.findByTitle);
let findByHandle = util.promisify(Shopify.findByHandle);
let outstockSizes = util.promisify(Shopify.outstockSizes);
let instockSizes = util.promisify(Shopify.instockSizes);
let checkRestock = util.promisify(Shopify.checkRestock);
let getCleaned = util.promisify(Shopify.getAllClean);
// TESTING   
let searchByTitle = util.promisify(Shopify.searchByTitle);
let searchByHandle = util.promisify(Shopify.searchByHandle);
let searchOutstockSizes = util.promisify(Shopify.searchOutstockSizes);
let searchInstockSizes = util.promisify(Shopify.searchInstockSizes);
let searchSizes = util.promisify(Shopify.searchSizes);

let vr = ["19936345522249", "19936345555017", "19936345686089", "19936345718857", "19936345751625"];
let productID = "2186230267977";

async function test() {
  let kw = [];
  kw.push("nike");
  let domain = "undefeated.com"
  let products = await getProducts(domain);
  let f1 = await searchByTitle(products, kw);
  console.log(JSON.parse(f1));
}

module.exports = Shopify;
