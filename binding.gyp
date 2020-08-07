{
    "targets": [{
        "target_name": "botmodules",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "main.cpp",
            "cppsrc/httptest.cpp",
            "cppsrc/product.cpp",
            "cppsrc/monitor.cpp",
            "cppsrc/asyncMonitor.cpp",
            "cppsrc/shopify.cpp",
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")",
            # Include your linked libraries as well!!!
        ],
        'libraries': [
          # Link libraries here.
          # CPR
          # RapidJSON
          # curl
        ],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")",
        ],c
        "msbuild_settings": {
          "Link": {
            "ImageHasSafeExceptionHandlers": "false",
          }
        },
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }]
}