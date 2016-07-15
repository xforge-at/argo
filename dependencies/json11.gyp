{ 'targets': [
    {
      'target_name': 'json11',
      'type': 'static_library',
      'sources': [
        "json11/json11.hpp",
        "json11/json11.cpp",
      ],
      'cflags': [
        '-fno-rtti',
        '-fno-exceptions',
	'-Wno-float-equal',
	'-Wno-error',
      ],
      'cflags_cc': [
        '-fno-rtti',
        '-fno-exceptions',
	'-Wno-float-equal',
	'-Wno-error',
      ],
      #'cflags!': [ '-Werror' ],
      #'cflags_cc!': [ '-Werror' ],
	'xcode_settings': {
	  'OTHER_CFLAGS!' : ['-Werror'],
	  'OTHER_CPLUSPLUSFLAGS!' : ['-Werror'],
	},
      'all_dependent_settings': {
        'include_dirs': [
          '.',
        ]
      },
      'include_dirs': [
        'json11',
      ],
    },
  ]
}
