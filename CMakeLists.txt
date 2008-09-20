SET( EXTENSION_NAME "Extensions_MusicPlayer")

ADD_LIBRARY( ${EXTENSION_NAME}
  Sound/MusicPlayer.cpp
  Sound/BruteTransitionMode.cpp
)

TARGET_LINK_LIBRARIES( ${EXTENSION_NAME}
  Extensions_OpenALSoundSystem
)
