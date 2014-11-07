{
    "targets": [
        {
            "target_name": "alienfx",
            "sources": [ "sources/binding/alienfx.cc", "sources/binding/contracts.cc" ],
            "include_dirs": [ "dependencies/alienfxsdk/include" ],
            "conditions": [
                [
                    "OS=='win'",
                    {
                        "sources": [ "sources/api/windows/alienfxApi.cc" ]
                    }
                ]
            ]
        }
    ]
}
