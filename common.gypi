{
  'target_defaults': {
    'default_configuration': 'Debug',
    'cflags': [
      # Dunno what that is, but it's good shit
      '-fvisibility=hidden',
    ],
    'error_flags': [
      # All warnings + warnings are errors
      '-Weverything',
      '-Werror',
      # Don't warn about = and <> comparisons of real numbers. 
      '-Wno-float-equal',
      # Turn off useless errors 
      '-Wno-pedantic',
      # Don't warn for gnu language extensions
      '-Wno-gnu',
      # Don't warn about C++98 compatibility
      '-Wno-c++98-compat',
      '-Wno-c++98-compat-pedantic',
      # Don't warn about vtable duplication warnings
      '-Wno-weak-vtables',
      # Don't warn about (type)var style casts
      '-Wno-old-style-cast',
      # Don't warn about paddings
      '-Wno-padded',
    ],
    'error_flags_ios': [
      '<@(_error_flags)',
      # Turn off objc specific errors
      '-Wno-objc-missing-property-synthesis',
      '-Wno-direct-ivar-access',
      # Turn of notes about module builds
      '-Rno-module-build',
    ],
    'cflags_cc': [ 
      '>@(_cflags)', 
      '-std=c++14', 
      '-fexceptions', 
      '-frtti',
    ],
    'conditions' : [
      ['OS=="android"',
        {
        # The compiler on android produces a lot more unecessary error messages, especially in the libraries
        #          'cflags!' : [ '-Werror', '-Weverything' ],
        #          'cflags_cc!' : [ '-Werror', '-Weverything' ],
        #          'cflags+' : [ '-Wno-reserved-id-macro', '-fblocks'],
        #          'cflags_cc+' : [ '-fblocks' ],
        },
      ],
      ['OS=="ios"',
        {
          'xcode_settings': {
            'SDKROOT': 'iphoneos',
            'SUPPORTED_PLATFORMS': 'iphonesimulator iphoneos',
            'IPHONEOS_DEPLOYMENT_TARGET': '9.0'
          },
        },
      ],
    ],
    'xcode_settings': {
      'OTHER_CFLAGS' : ['>@(_cflags)'],
      'OTHER_CPLUSPLUSFLAGS' : ['>@(_cflags_cc)'],
      'CLANG_CXX_LANGUAGE_STANDARD': 'c++14',
      'CLANG_CXX_LIBRARY': 'libc++',
      'CLANG_ENABLE_OBJC_ARC': 'YES',
      'CLANG_ENABLE_CODE_COVERAGE': 'YES',
      'CLANG_ENABLE_MODULES': 'YES',
      'ENABLE_BITCODE': 'NO',
      'ALWAYS_SEARCH_USER_PATHS': 'NO',
    },
    'configurations': {
      'Debug': {
        'defines': [ 'DEBUG', 'SERVER_ENV=alpha'],
        'cflags' : [ '-g', '-O0' ],
        'conditions' : [
          ['OS=="ios"',
            {
# Code coverage on iOS
              'cflags+' : [ '-fprofile-arcs' ],
            }
          ]
        ],
        'xcode_settings' : {
          'GCC_OPTIMIZATION_LEVEL': '0',
          'ONLY_ACTIVE_ARCH': 'YES',
          'ENABLE_TESTABILITY': 'YES',
          'BUNDLE_ID_SUFFIX': '.alpha',
          'ASSETCATALOG_COMPILER_APPICON_NAME': 'AppIconDebug',
        },
      },
      'Beta': {
        'defines': [ 'DEBUG', 'SERVER_ENV=staging'],
        'cflags' : [ '-g', '-O0', ],
        'conditions' : [
          ['OS=="ios"',
            {
# Code coverage on iOS
              'cflags+' : [ '-fprofile-arcs' ],
            }
          ]
        ],
        'xcode_settings' : {
          'ONLY_ACTIVE_ARCH': 'YES',
          'BUNDLE_ID_SUFFIX': '.beta',
          'ASSETCATALOG_COMPILER_APPICON_NAME': 'AppIconBeta',
        },
      },
      'Release': {
        'defines': [ 'NDEBUG', 'SERVER_ENV=production'],
        'cflags': [
          '-Os',
          '-fomit-frame-pointer',
          '-fdata-sections',
          '-ffunction-sections',
        ],
        'xcode_settings': {
          'DEAD_CODE_STRIPPING': 'YES',
          'SWIFT_OPTIMIZATION_LEVEL': ['-O', '-whole-module-optimization'],
          'BUNDLE_ID_SUFFIX': '',
          'SWIFT_DISABLE_SAFETY_CHECKS': 'YES'
        },
      },
    },
  },
}
