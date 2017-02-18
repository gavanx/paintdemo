{
  "targets": [
    {
      "target_name": "demo",
      "includes": ["../brush/mypaint/binding/binding.gypi"],
      "sources": [ "../demo_v8.cpp", "../demo.c", "../canvas.c", "../brush/mypaint/binding/paint_brush.cpp" ],
      "include_dirs": [
              "<!(node -e \"require('nan')\")",
              "../../../",
              "/usr/include/json-c",
              "/usr/include/glib-2.0",
              "/usr/lib/x86_64-linux-gnu/glib-2.0/include",
              "/usr/local/lib",
              "/usr/include/cairo"
            ],
      'conditions': [
        ['OS!="win"', {
          'link_settings': {
            'libraries': [
              '/usr/local/lib/libmypaint.so',
              '-ljson-c',
              '-lcairo'
            ]
          }
        }]
      ]
    }
  ]
}