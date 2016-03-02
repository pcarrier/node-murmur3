{
  "targets": [
    {
      "target_name": "murmur3",
      "sources": [
        "src/binding.cc",
        "src/MurmurHash3.cpp"
      ],
      "include_dirs": [
        "deps",
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
