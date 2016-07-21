{
    'targets': [
	{
	    'target_name': 'libArgo',
		'type': 'static_library',
		'dependencies': [
		    'dependencies/json11.gyp:json11',
		    'dependencies/leveldb.gyp:leveldb'
		],
		'conditions': [ 
		    ['OS=="ios"', 
			{
			    'ldflags' : ['-Idispatch'],
			    'cflags+' : [
				'>@(_error_flags_ios)',
			    ]
			}
		    ],
		    ['OS=="android"', 
			{
			    'include_dirs+' : [ 'dependencies/libdispatch' ],
			    'cflags+' : [ '-DTARGET_OS_ANDROID' ],
			}
		    ],
		],
		'sources': [
		    "<!@(python glob.py src *.cpp *.hpp)",
		],
		'all_dependent_settings' : {
		    'include_dirs' : [ 'src', 'src/generated/'],
		},
		'include_dirs': [
		    'src',
		    'dependencies/gsl/include',
		    'dependencies/ftl/include',
		],
	},
	{
	    'target_name': 'test',
	    'type': 'executable',
	    'dependencies': [
		'libArgo',
		'dependencies/googletest.gyp:googletest',
	    ],
	    'include_dirs': [
		'test',
		'src',
		'src/generated',
	    ],
	    'sources': [
		'<!@(python glob.py test *.cpp *.hpp)',
	    ]
	}
    ],
    'conditions': [
	['OS=="ios"', 
	    {
		'targets': [
		    {
			'target_name': 'libArgo_objc',
			'type': 'static_library',
			'dependencies': [
			    'dependencies/djinni/support-lib/support_lib.gyp:djinni_objc',
			    'libArgo',
			],
			'sources': [
			    '<!@(python glob.py ios/generated *.mm *.h *.m)',
			],
			'cflags+' : [
			    '>@(_error_flags_ios)',
			    '-Wno-old-style-cast',
			    '-Wno-idiomatic-parentheses',
			    '-Wno-unused-exception-parameter',
			],
			'all_dependent_settings' : {
			    'include_dirs' : [ 'ios/generated/' ],
			},
			'include_dirs': [
			    'dependencies/gsl/include',
			    'dependencies/ftl/include',
			],
		    }
		],
	    },
	],
	['OS=="android"', 
	    {
		'targets': [
		    {
			'target_name': 'libArgo_android_static',
			'android_unmangled_name': 1,
			'type': 'static_library',
			'dependencies': [
			    'dependencies/djinni/support-lib/support_lib.gyp:djinni_jni',
			    'dependencies/json11.gyp:json11',
			    'libArgo',
			],
			'cflags+' : [ '-DTARGET_OS_ANDROID=1' ],
			'sources': [
			    '<!@(python glob.py android/generated/jni *.cpp *.hpp)',
			    '<!@(python glob.py android/jni *.cpp *.hpp)',
			],
			'include_dirs': [
			    'src',
			    'dependencies/libdispatch',
			    'dependencies/libdispatch/os',
			    'dependencies/libdispatch/private',
			    'dependencies/libkqueue/include',
			    'dependencies/gsl/include',
			    'dependencies/ftl/include',
			],
		    }
		],
	    },
	],
    ],
}
