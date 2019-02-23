{
  "targets": [
    {
      "target_name": "callback",
      "include_dirs" : [
          "<!(node -e \"require('nan')\")"
      ],
      "sources": [ 
        "src/callback.cc",
        "src/callback_uv_async.cc",
        "src/callback_uv_queue_work.cc"
        ]
    }
  ]
}