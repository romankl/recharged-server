{
  "targets": [{
    "target_name": "recharged",
    "type": "executable",
    "dependencies": [
      "deps/uv/uv.gyp:libuv",
    ],
    "include_dirs": [
      "src/",
      "include",
      "<(SHARED_INTERMEDIATE_DIR)",
    ],
    "sources": [
      "src/ast.cc",
      "src/error.cc",
      "src/jsruntime.cc",
      "src/node.cc",
      "src/parser.cc",
      "src/runtime.cc",
      "src/recharged.cc",
      "src/commandtable.cc",
      # Header files
      "src/ast.h",
      "src/error.h",
      "src/jsruntime.h",
      "src/node.h",
      "src/parser.h",
      "src/protocol.h",
      "src/runtime.h",
      "src/server.h",
      "src/commandtable.h",
    ],
    "conditions": [
      ["OS == 'linux'", {
        "defines": [
          "_POSIX_C_SOURCE=200112",
          "_GNU_SOURCE",
        ],
      }],
      ['OS in "freebsd"', {
        'ldflags': [
          '-Wl,--export-dynamic',
        ],
      }],
    ]
  }]
}
