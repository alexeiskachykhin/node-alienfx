{
    "targets": [
        {
            "target_name": "alienfx",
            "sources": ["sources/main.cc"],
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
