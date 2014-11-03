{
    "targets": [
        {
            "target_name": "alienfx",
            "sources": [ "sources/alienfx.cc", "sources/contracts.cc" ],
            "include_dirs": [ "dependencies/alienfxsdk/include" ],
            "conditions": [
                [
                    "OS=='win'",
                    {
                        "sources": [ "sources/windows/alienfxApi.cc" ]
                    }
                ]
            ]
        }
    ]
}
