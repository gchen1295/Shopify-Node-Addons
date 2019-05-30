__**Bot_Modules**__

__Usage__
```js
let shopify = require("./Release/botmodules.node")
```
__Monitor Functions__
Most functions have a sychronous and asynchronous version.
Synchronous versions have Sync appended to end of Async version
```js
getAllProducts(domain)
getAllProductsSync(domain)
getAllClean(domain)
findByTitle(domain, keywords)
findByTitleSync(domain, keywords)
findByHandle(domain, keywords)
findByHandleSync(domain, keywords)
getSizes(domain, productID)
outstockSizes(domain, productID)
instockSizes(domain, productID)
checkRestock(domain, productID, variants)
```

__API Functions__
```js
createLicense()
authLicense(key, hwid)
```
