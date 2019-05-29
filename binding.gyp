{
    "targets": [{
        "target_name": "botmodules",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "main.cpp",
            "cppsrc/httptest.cpp",
            "cppsrc/shopify.cpp",
            "cppsrc/product.cpp"
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")",
            "D:\\Desktop\\vcpkg-master\\installed\\x64-windows\\include**"
        ],
        'libraries': [
          "D:\\Desktop\\vcpkg-master\\installed\\x64-windows\\lib\\**"
        ],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")",
        ],
        "msbuild_settings": {
          "Link": {
            "ImageHasSafeExceptionHandlers": "false",
          }
        },
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }]
}