# Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

path=$(PWD)


# Set engine environment variable.
setx SA_ENGINE_PATH $path
echo "set environment variable SA_ENGINE_PATH: $path"


git submodule update --recursive --init


# Setup dependencies.
cd ThirdParty/EngineDeps
./setup.sh
