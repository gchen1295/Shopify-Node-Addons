__**Bot_Modules**__

__Usage__
```js
let shopify = require("./Release/botmodules.node")
```
__Monitor Functions__
Most functions have a sychronous and asynchronous version.
Synchronous versions have Sync appended to end of Async version
```js
getAllProductsLocal(domain)
getAllProducts(domain, proxy)
getAllProductsSync(domain)
getAllCleanLocal(domain)
getAllClean(domain, proxy)
findByTitleLocal(domain, keywords)
findByTitle(domain, proxy, keywords)
findByTitleSync(domain, keywords)
findByHandleLocal(domain, keywords)
findByHandle(domain, proxy, keywords)
findByHandleSync(domain, keywords)
getSizes(domain, productID)
getSizes(domain, proxy, productID)
outstockSizesLocal(domain, productID)
outstockSizes(domain, proxy, productID)
instockSizesLocal(domain, productID)
instockSizes(domain, proxy, productID)
checkRestockLocal(domain, productID, variants)
checkRestock(domain, proxy, productID, variants)
searchByTitle(products, keywords)
searchByHandle(products, keywords)
searchSizes(products, productID)
searchOutstockSizes(products, productID)
searchInstockSizes(products, productID)
```

__API Functions__
```js
createLicense()
authLicense(key, hwid)
```
