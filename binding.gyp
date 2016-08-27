{
    "targets": [{
        "target_name": "alienfx",
        "sources": [
            "sources/binding/alienfx.cc",
            "sources/binding/sync/alienfxSync.cc",
            "sources/binding/async/alienfxAsync.cc",
            "sources/binding/objects/alienfxObjects.cc",
            "sources/binding/contracts.cc"
        ],
        "include_dirs": ["dependencies/alienfxsdk/include"],
        "conditions": [
            [
                "OS=='win'",
                {
                    "sources": ["sources/api/windows/alienfxApi.cc"]
                }
            ]
        ]
    }]
}
