{
    "targets": [{
        "target_name": "testaddon",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "main.cpp",
            "cppsrc/httptest.cpp"
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")",
            "D:\\vcpkg\\installed\\x86-windows\\include\\",
            "D:\\vcpkg\\installed\\x86-windows\\**"
        ],
        'libraries': [
          "D:\\vcpkg\\installed\\x86-windows\\lib\\cpr.lib",
          "D:\\vcpkg\\installed\\x86-windows\\lib\\**"
        ],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        "msbuild_settings": {
          "Link": {
            "ImageHasSafeExceptionHandlers": "false"
          }
        },
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }]
}