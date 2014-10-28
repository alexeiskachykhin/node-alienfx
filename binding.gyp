{
    "targets": [
        {
            "target_name": "alienfx",
            "sources": [ "sources/main.cc" ],
            "include_dirs": [ "dependencies/alienfxsdk/include" ],
            "conditions": [
                [
                    "OS=='win'",
                    {
                        "sources": [ "sources/windows/lightfx.cc" ]
                    }
                ]
            ]
        }
    ]
}
