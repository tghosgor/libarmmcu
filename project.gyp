{
  'variables': {
    'BuildDate': '<!(date --rfc-2822 --universal)',
  },
    
  'target_defaults': {
    'include_dirs': [ '.', ],
    'cflags': [ '-std=c++11', '-mcpu=cortex-m4', '-mthumb', ],
    'ldflags': [ '-mcpu=cortex-m4', '-mthumb', ],
    'default_configuration': 'Debug',
    'configurations': {
      'Debug': {
        'cflags': [ '-g2', '-Wall' ],
        'ldflags': [ '-g2', ],
      },

      'Release': {
        'cflags': [ '-O3', ],
        'ldflags': [ '-O3', ],
      },
    },
  },
      
  'targets': [
    {# test image
      'target_name': 'test',
      'type': 'executable',
      'dependencies': [ 'window_system', 'fonts', 'system', 'peripheral_driver', ],
      'sources': [ 'testing/main.cpp', ],
      #'defines': [
      #  'BUILD_DATE=' '"<(BuildDate)"',],
    },

    {# window system
      'target_name': 'window_system',
      'type': 'static_library',
      'dependencies': [ 'peripheral_driver', ],
      'sources': [
        '<!@(find src/window -type f -name *.cpp)',
      ],
    },

    {# fonts
      'target_name': 'fonts',
      'type': 'static_library',
      'sources': [
        '<!@(find src/font -type f -name *.cpp)',
      ],
    },

    {# system
      'target_name': 'system',
      'type': 'static_library',
      'dependencies': [ 'peripheral_driver', ],
      'sources': [
        '<!@(find src/system -type f -name *.cpp)',
      ],
    },

    {# peripheral drivers
      'target_name': 'peripheral_driver',
      'type': 'static_library',
      'sources': [
        '<!@(find src/driver -type f -name *.cpp)',
      ],
    },
  ],
}
