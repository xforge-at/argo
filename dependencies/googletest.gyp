{ 
    'targets': [
	{
	    'target_name': 'googletest',
	    'type': "static_library",
	    'sources': [
		'googletest/googlemock/src/gmock-all.cc',
		'googletest/googletest/src/gtest-all.cc',
		'googletest/googlemock/src/gmock_main.cc',
	    ],
	    'cflags_cc!': [ '-Werror' ],
	    'cflags_cc+': [ '-pthread' ],
	    "include_dirs": [
		'googletest/googletest/',
		'googletest/googlemock/',
		'googletest/googletest/include',
		'googletest/googlemock/include',
	    ],
	    'direct_dependent_settings': {
		'include_dirs': [
		    'googletest/googletest/include/',
		    'googletest/googlemock/include/',
		],
	    },
	},
    ]
}
