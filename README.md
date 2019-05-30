Bot_Modules

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
findByTitle(domain, keywords)
findByTitleSync(domain, keywords)
findByHandle(domain, keywords)
findByHandleSync(domain, keywords)
getSizes(domain, productID)
outstockSizes(domain, productID)
instockSizes(domain, productID)
```

__API Functions__
```js
createLicense()
authLicense(key, hwid)
```
