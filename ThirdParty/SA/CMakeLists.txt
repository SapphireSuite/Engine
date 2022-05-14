# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.



# Entrypoints

### Must be added first.
add_subdirectory(Logger)

set(SA_MATHS_USE_LOGGER_OPT ON CACHE BOOL "Enable Maths Logger link")
add_subdirectory(Maths)

set(SA_EVENT_USE_LOGGER_OPT ON CACHE BOOL "Enable Event Logger link")
add_subdirectory(Event)
