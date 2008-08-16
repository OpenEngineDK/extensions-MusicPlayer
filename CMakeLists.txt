
# Create the extension library
ADD_LIBRARY(Extensions_MusicPlayer
  Sound/MusicPlayer.cpp
  Sound/BruteTransitionMode.cpp
)

TARGET_LINK_LIBRARIES(Extensions_MusicPlayer
  Extensions_OpenALSoundSystem
  ${OPENAL_LIBRARY}
)
